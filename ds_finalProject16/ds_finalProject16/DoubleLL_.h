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
	else {		// �ڷ� ���ٰ� �ٽ� �˻��ؼ� myCurrDb�� ������ ���.
		GoToNextPos();
		DeleteLine();		//DeleteLine() �Լ� ��ü�� ������, �� ������ ����� �ٷ� �� ���� ��ġ�� �ű�� ���� ���Ե�.
							//������ġ(�� ���ÿ��������� tempPtr) ������ ��� myDbHistory�� ������ �� �� myDb�� history�� �����ϵ��� �Ѵ�.
		Insert_with_Deleting_nextPos(newline);	//�̸� recursive ���·� ����.
	}
}



