#include "DoubleLL.h"



template <class _ItemType>
DoubleLL<_ItemType>::DoubleLL()
{
	headerPtr = new NodeType<_ItemType>;
	headerPtr->info = "This is header.";

	trailerPtr = new NodeType<_ItemType>;
	trailerPtr->info = "This is trailer.";

	headerPtr->topPtr = NULL;
	headerPtr->bottomPtr = trailerPtr;

	trailerPtr->topPtr = headerPtr;
	trailerPtr->bottomPtr = NULL;

	currentPos = headerPtr;
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
void DoubleLL<_ItemType>::GoToNextPos()
{
	currentPos = currentPos->bottomPtr;

	if (currentPos == trailerPtr) { //���Ұ� ������ currentPos = headerptr;�� �ٽ� �ʱ�ȭ.
		currentPos = headerPtr;		// �̰���, ������ �ڵ��� ��찡 ����. currentPos = trailerPtr->topPtr;
	}
}

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
	GoToTop();
	currentPos = current->bottom;

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
}

template <class _ItemType>
void DoubleLL<_ItemType>::InsertLine(const char newline[])
{
	NodeType<_ItemType>* newLinePtr;
	newLinePtr = new NodeType<_ItemType>;
	newLinePtr->info = newline;

	newLinePtr->bottomPtr = currentPos->bottomPtr;
	newLinePtr->topPtr = currentPos->bottomPtr->topPtr;
	currentPos->bottomPtr = newLinePtr;
	newLinePtr->bottomPtr->topPtr = newLinePtr;
	currentPos = newLinePtr;	

	return;
}

template <class _ItemType>
void DoubleLL<_ItemType>::Print()
//currentPos ��ġ�� ���� ��ġ���� ����Ʈ��.
{
	//NodeType<_ItemType>* temp = currentPos;
	//GoToFront();	// �̰� �Ἥ ��ó������ ����Ʈ�ϰ� ������, �̰� main�Լ��� ���� �� ����.

	currentPos = currentPos->bottomPtr;

	while (currentPos != trailerPtr) {
		cout << currentPos->info << endl;
		currentPos = currentPos->bottomPtr;
	}

	if ((currentPos == trailerPtr)) { //���Ұ� ������ currentPos = headerptr;�� �ٽ� �ʱ�ȭ.
		currentPos = headerPtr;
	}

	//currentPos = temp;
}