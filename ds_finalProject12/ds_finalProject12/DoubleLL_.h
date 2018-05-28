#include "DoubleLL.h"



// Class cnostructor & Class destructor & Class copy constructor //////////////////
template <class _ItemType>
DoubleLL<_ItemType>::DoubleLL()
{
	currentPos = NULL;
	headerPtr = NULL;
	trailerPtr = NULL;

	headerPtr = new DoubleLLNode<_ItemType>;
	trailerPtr = new DoubleLLNode<_ItemType>;
	 
	headerPtr->info; //= "This is header.";		//이 쌍따옴표 넣으려면 왜 오류 나지?
	headerPtr->topPtr = NULL;
	headerPtr->bottomPtr = trailerPtr;

	trailerPtr->info; //= "This is trailer.";	//이 쌍따옴표 넣으려면 왜 오류 나지?
	trailerPtr->topPtr = headerPtr;
	trailerPtr->bottomPtr = NULL;

	currentPos = headerPtr;
}

//template <class _ItemType>
//DoubleLL<_ItemType>::DoubleLL(DoubleLL<_ItemType>& copiedDoubleLL)
//{
//
//}

//template <class _ItemType>
//DoubleLL<_ItemType>::~DoubleLL()
//{
//
//}
///////////////////////////////////////////////////////////////////////////////



// IsEmpty & IsFull //////////////////////////////////////////////////
template<class _ItemType>
bool DoubleLL<_ItemType>::IsEmpty() const
// Returns true if there are no elements on the queue; false otherwise.
{
	return (headerPtr->bottomPtr == trailerPtr);
}

template<class _ItemType>
bool DoubleLL<_ItemType>::IsFull() const
// Returns true if there is no room for another ItemType 
//  on the free store; false otherwise.
{
	DoubleLLNode<_ItemType>* location;
	try
	{
		location = new DoubleLLNode<_ItemType>;
		delete location;
		return false;
	}
	catch (std::bad_alloc)
	{
		return true;
	}
}
////////////////////////



// GoTo~ & ChangeCurrentPos & IsCurrentPos~ & WhatIs~ //////////////////////////////////////////////////////////
template <class _ItemType>
void DoubleLL<_ItemType>::GoToTop()
{
	currentPos = headerPtr;
}

template <class _ItemType>
void DoubleLL<_ItemType>::GoToBottom()
{
	currentPos = trailerPtr->topPtr;
}

template <class _ItemType>
void DoubleLL<_ItemType>::GoToBeforePos()
{
	if (currentPos == headerPtr) {	//currentPos == headerPtr이면 더이상 currentPos가 움직이지 않도록 하기.
		return;
	}

	currentPos = currentPos->topPtr;
}

template <class _ItemType>
void DoubleLL<_ItemType>::GoToNextPos()
{
	DoubleLLNode<_ItemType>* tempPtr = currentPos;

	currentPos = currentPos->bottomPtr;

	if (currentPos == trailerPtr) { //원소가 없으면 currentPos = headerptr;로 다시 초기화.
		currentPos = headerPtr;		// 이경우는, 다음의 코딩과 경우가 같다. currentPos = trailerPtr->topPtr;
	}

	//if (currentPos == trailerPtr) {
	//	currentPos = tempPtr;		
	//}
}

template <class _ItemType>
bool DoubleLL<_ItemType>::IsCurrPosHeader()
{
	if (currentPos == headerPtr) {
		return true;
	}
	else {
		return false;
	}
}

template <class _ItemType>
bool DoubleLL<_ItemType>::IsCurrPosTrailer()
{
	if (currentPos == trailerPtr) {
		return true;
	}
	else {
		return false;
	}
}


template <class _ItemType>
bool DoubleLL<_ItemType>::IsBeforePosHeader()
{
	if (currentPos->topPtr == headerPtr) { 
		return true;
	}
	else {
		return false;
	}
}

template <class _ItemType>
bool DoubleLL<_ItemType>::IsNextPosTrailer()
{
	if (currentPos->bottomPtr == trailerPtr) {
		return true;
	}
	else {
		return false;
	}
}

template <class _ItemType>
DoubleLLNode<_ItemType>*  DoubleLL<_ItemType>::WhatIsCurrentPos()
{
	return currentPos;
}

template <class _ItemType>
_ItemType  DoubleLL<_ItemType>::WhatIsCurrentInfo()
{
	return (currentPos->info);
}

template <class _ItemType>
void  DoubleLL<_ItemType>::ChangeHeaderToNext()
//changed가 가리키는 노드가 이 객체 Double Linked List에 삽입되어 있어야 한다.
{
	if (currentPos->bottomPtr == trailerPtr) {
		return;
	}
	else {
		headerPtr = headerPtr->bottomPtr;
		return;
	}
}
/////////////////////////////////////////////////////////////////////////////////



// InsertLine & DeleteLine ///////////////////////////////////////////////
template <class _ItemType>
void DoubleLL<_ItemType>::InsertLine(_ItemType newline)
//처음에 currentPos가 가리키는 노드의 다음 위치에 newline이 insert되도록 한다.
{
	DoubleLLNode<_ItemType>* newLinePtr;
	newLinePtr = new DoubleLLNode<_ItemType>;
	newLinePtr->info = newline;

	newLinePtr->bottomPtr = currentPos->bottomPtr;
	newLinePtr->topPtr = currentPos->bottomPtr->topPtr;
	currentPos->bottomPtr = newLinePtr;
	newLinePtr->bottomPtr->topPtr = newLinePtr;
	currentPos = newLinePtr;	

	return;
}

template <class _ItemType>
void DoubleLL<_ItemType>::DeleteLine()
//DeleteLine() 함수 자체에 삭제후, 그 삭제된 노드의 바로 전 노드로 위치를 옮기는 과정 포함됨.
{
	DoubleLLNode<_ItemType>* tempLine;
	tempLine = currentPos;

	currentPos->topPtr->bottomPtr = currentPos->bottomPtr;
	currentPos->bottomPtr->topPtr = currentPos->topPtr;

	currentPos = currentPos->topPtr;
	delete tempLine;
}

template <class _ItemType>
void DoubleLL<_ItemType>::Insert_with_Deleting_nextPos(_ItemType newline)
{
	if (IsNextPosTrailer()) {
		InsertLine(newline);
	}
	else {		// 뒤로 갔다가 다시 검색해서 myCurrDb를 형성한 경우.
		GoToNextPos();
		DeleteLine();		//DeleteLine() 함수 자체에 삭제후, 그 삭제된 노드의 바로 전 노드로 위치를 옮기는 과정 포함됨.
										//현재위치 이후의 모든 myDbHistory를 삭제한 후 새 myDb를 history에 삽입하도록 한다.
		Insert_with_Deleting_nextPos(newline);	//이를 recursive 형태로 구현.
	}
}
/////////////////////////////////////////////////////////////////////



// FindItem & GetItem ///////////////////////////////////////////////
template<class _ItemType>
void DoubleLL<_ItemType>::FindItem(_ItemType item, bool& found)
//Pre:	ItemType is a type for which the operators "<" and 
//		"==" are defined.
//		List is not empty.
//Post:	If there is an element someItem whose key matches item's key, then found = true; otherwise, found = false. 
//      If found, location contains the address of someItem; 
//      otherwise, location contains the address of the logical successor of item.
//		header 위치(currentPos)의 다음 위치부터 검색 시작.
{
	//DoubleLLNode<_ItemType>* temp = currentPos;

	//GoToTop();
	//currentPos = current->bottom;

	bool moreToSearch = true;

	location = listData;
	found = false;
	while (moreToSearch && !found)
	{
		if (item < location->info)
			moreToSearch = false;
		else if (item == location->info)
			found = true;
		else
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}
	}

	//currentPos = temp;
}

template <class _ItemType>
_ItemType DoubleLL<_ItemType>::GetItem()
{
	return currentPos->info;
}
//////////////////////////////////////////////////////////////////////////



// Print /////////////////////////////////////////////////////////////////
template <class _ItemType>
void DoubleLL<_ItemType>::Print()
//처음위치부터 프린트 하거나, currentPos 위치의 다음 위치부터 프린트함.
{
	DoubleLLNode<_ItemType>* temp = currentPos;
	GoToTop();	// 이걸 써서 맨처음부터 프린트하고 싶으면, 이걸 main함수에 쓰는 게 좋음.

	currentPos = currentPos->bottomPtr;

	while (currentPos != trailerPtr) {
		cout << currentPos->info << endl;
		currentPos = currentPos->bottomPtr;
	}

	//if ((currentPos == trailerPtr)) { //원소가 없으면 currentPos = headerptr;로 다시 초기화.
		currentPos = headerPtr;
	//}

	currentPos = temp;
}

template <class _ItemType>
void DoubleLL<_ItemType>::Print_NextOne(DoubleLLNode<_ItemType>*& tempPtr)
//처음위치부터 프린트 하거나, currentPos 위치의 다음 위치부터 프린트함.
{
	//if (currentPos != headerPtr) {
		if (tempPtr == NULL) {
			tempPtr = headerPtr;
			tempPtr = tempPtr->bottomPtr;
		}

		cout << tempPtr->info;	// << " ";
		tempPtr = tempPtr->bottomPtr;

		if (tempPtr == currentPos->bottomPtr) {		// (tempPtr == currentPos->bottomPtr) || (tempPtr == trailer)
			tempPtr = NULL;
		}
	//}
	
}
////////////////////////////////////////////////////////////////////////////