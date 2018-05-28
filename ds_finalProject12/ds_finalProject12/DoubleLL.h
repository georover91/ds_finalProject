#include "string_.h"



template <class _ItemType>
struct DoubleLLNode {
	DoubleLLNode<_ItemType>* topPtr;
	_ItemType info;
	DoubleLLNode<_ItemType>* bottomPtr;
};

template <class _ItemType>
class DoubleLL {
public:
	DoubleLL();
	//DoubleLL(DoubleLL& copiedDoubleLL);
	//~DoubleLL();
	bool IsEmpty() const;
	bool IsFull() const;
	void GoToTop();
	void GoToBottom();
	void GoToBeforePos();
	void GoToNextPos();
	bool IsCurrPosHeader();
	bool IsCurrPosTrailer();
	bool IsBeforePosHeader();
	bool IsNextPosTrailer();
	DoubleLLNode<_ItemType>* WhatIsCurrentPos();
	_ItemType WhatIsCurrentInfo();
	void ChangeHeaderToNext();
	void InsertLine(_ItemType newline);
	void DeleteLine();		//currentPos의 Line을 삭제한다.
	void Insert_with_Deleting_nextPos(_ItemType newline);
	void FindItem(_ItemType item, bool& found);
	_ItemType GetItem();
	void Print();
	void Print_NextOne(DoubleLLNode<_ItemType>*& tempPtr);

private:
	DoubleLLNode<_ItemType>* headerPtr;
	DoubleLLNode<_ItemType>* trailerPtr;
	DoubleLLNode<_ItemType>* currentPos;
	//int eleNum;
};


























