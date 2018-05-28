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
	 
	headerPtr->info; //= "This is header.";		//�� �ֵ���ǥ �������� �� ���� ����?
	headerPtr->topPtr = NULL;
	headerPtr->bottomPtr = trailerPtr;

	trailerPtr->info; //= "This is trailer.";	//�� �ֵ���ǥ �������� �� ���� ����?
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
	if (currentPos == headerPtr) {	//currentPos == headerPtr�̸� ���̻� currentPos�� �������� �ʵ��� �ϱ�.
		return;
	}

	currentPos = currentPos->topPtr;
}

template <class _ItemType>
void DoubleLL<_ItemType>::GoToNextPos()
{
	DoubleLLNode<_ItemType>* tempPtr = currentPos;

	currentPos = currentPos->bottomPtr;

	if (currentPos == trailerPtr) { //���Ұ� ������ currentPos = headerptr;�� �ٽ� �ʱ�ȭ.
		currentPos = headerPtr;		// �̰���, ������ �ڵ��� ��찡 ����. currentPos = trailerPtr->topPtr;
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
//changed�� ����Ű�� ��尡 �� ��ü Double Linked List�� ���ԵǾ� �־�� �Ѵ�.
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
//ó���� currentPos�� ����Ű�� ����� ���� ��ġ�� newline�� insert�ǵ��� �Ѵ�.
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
//DeleteLine() �Լ� ��ü�� ������, �� ������ ����� �ٷ� �� ���� ��ġ�� �ű�� ���� ���Ե�.
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
	else {		// �ڷ� ���ٰ� �ٽ� �˻��ؼ� myCurrDb�� ������ ���.
		GoToNextPos();
		DeleteLine();		//DeleteLine() �Լ� ��ü�� ������, �� ������ ����� �ٷ� �� ���� ��ġ�� �ű�� ���� ���Ե�.
										//������ġ ������ ��� myDbHistory�� ������ �� �� myDb�� history�� �����ϵ��� �Ѵ�.
		Insert_with_Deleting_nextPos(newline);	//�̸� recursive ���·� ����.
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
//		header ��ġ(currentPos)�� ���� ��ġ���� �˻� ����.
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
//ó����ġ���� ����Ʈ �ϰų�, currentPos ��ġ�� ���� ��ġ���� ����Ʈ��.
{
	DoubleLLNode<_ItemType>* temp = currentPos;
	GoToTop();	// �̰� �Ἥ ��ó������ ����Ʈ�ϰ� ������, �̰� main�Լ��� ���� �� ����.

	currentPos = currentPos->bottomPtr;

	while (currentPos != trailerPtr) {
		cout << currentPos->info << endl;
		currentPos = currentPos->bottomPtr;
	}

	//if ((currentPos == trailerPtr)) { //���Ұ� ������ currentPos = headerptr;�� �ٽ� �ʱ�ȭ.
		currentPos = headerPtr;
	//}

	currentPos = temp;
}

template <class _ItemType>
void DoubleLL<_ItemType>::Print_NextOne(DoubleLLNode<_ItemType>*& tempPtr)
//ó����ġ���� ����Ʈ �ϰų�, currentPos ��ġ�� ���� ��ġ���� ����Ʈ��.
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