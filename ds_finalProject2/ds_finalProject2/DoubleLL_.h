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

	if (currentPos == trailerPtr) { //원소가 없으면 currentPos = headerptr;로 다시 초기화.
		currentPos = headerPtr;		// 이경우는, 다음의 코딩과 경우가 같다. currentPos = trailerPtr->topPtr;
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
//		header 위치(currentPos)의 다음 위치부터 검색 시작.
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
//currentPos 위치의 다음 위치부터 프린트함.
{
	//NodeType<_ItemType>* temp = currentPos;
	//GoToFront();	// 이걸 써서 맨처음부터 프린트하고 싶으면, 이걸 main함수에 쓰는 게 좋음.

	currentPos = currentPos->bottomPtr;

	while (currentPos != trailerPtr) {
		cout << currentPos->info << endl;
		currentPos = currentPos->bottomPtr;
	}

	if ((currentPos == trailerPtr)) { //원소가 없으면 currentPos = headerptr;로 다시 초기화.
		currentPos = headerPtr;
	}

	//currentPos = temp;
}