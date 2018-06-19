#include "DoubleLL.h"



template <class _ItemType>
DoubleLL<_ItemType>::DoubleLL()
{
	currentPos = NULL;
	headerPtr = NULL;
	trailerPtr = NULL;

	headerPtr = new DoubleLLNode<_ItemType>;
	trailerPtr = new DoubleLLNode<_ItemType>;

	headerPtr->info = "all data";		
	headerPtr->topPtr = NULL;
	headerPtr->bottomPtr = trailerPtr;

	trailerPtr->info = "This is trailer.";	
	trailerPtr->topPtr = headerPtr;
	trailerPtr->bottomPtr = NULL;

	currentPos = headerPtr;
}

template <class _ItemType>
void DoubleLL<_ItemType>::MakeEmpty()
{
	currentPos = headerPtr;
	GoToNextPos();

	while (currentPos != headerPtr) {
		DeleteLine();
		GoToNextPos();
	}
}



template<class _ItemType>
bool DoubleLL<_ItemType>::IsEmpty() const
{
	return (headerPtr->bottomPtr == trailerPtr);
}

template<class _ItemType>
bool DoubleLL<_ItemType>::IsFull() const
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
		currentPos = headerPtr;		
	}
}





template <class _ItemType>
DoubleLLNode<_ItemType>*  DoubleLL<_ItemType>::WhatIsCurrentPos()
{
	return currentPos;
}

template <class _ItemType>
DoubleLLNode<_ItemType>* DoubleLL<_ItemType>::WhatIsHeaderPtr()
{
	return headerPtr;
}

template <class _ItemType>
DoubleLLNode<_ItemType>* DoubleLL<_ItemType>::WhatIsTrailerPtr()
{
	return trailerPtr;
}



template <class _ItemType>
void DoubleLL<_ItemType>::InsertLine(_ItemType newline)
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
	DoubleLLNode<_ItemType>* tempPtr;
	tempPtr = currentPos;
	tempPtr = tempPtr->bottomPtr;

	if (tempPtr == trailerPtr) {
		InsertLine(newline);
	}
	else {		// 뒤로 갔다가 다시 검색해서 myCurrDb를 형성한 경우.
		GoToNextPos();
		DeleteLine();		//DeleteLine() 함수 자체에 삭제후, 그 삭제된 노드의 바로 전 노드로 위치를 옮기는 과정 포함됨.
							//현재위치(이 로컬영역에서의 tempPtr) 이후의 모든 myDbHistory를 삭제한 후 새 myDb를 history에 삽입하도록 한다.
		Insert_with_Deleting_nextPos(newline);	//이를 recursive 형태로 구현.
	}
}



