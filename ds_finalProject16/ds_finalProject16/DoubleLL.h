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
	void MakeEmpty();
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
	DoubleLLNode<_ItemType>* WhatIsHeaderPtr();
	DoubleLLNode<_ItemType>* WhatIsTrailerPtr();
	_ItemType WhatIsCurrentInfo();
	void ChangeHeaderToNext();
	void InsertLine(_ItemType newline);
	void DeleteLine();		//currentPos�� Line�� �����Ѵ�.
	void Insert_with_Deleting_nextPos(_ItemType newline);
	void FindItem(_ItemType item, bool& found);
	_ItemType GetItem();
	void Print();
	void Print_operKey_history();

private:
	DoubleLLNode<_ItemType>* headerPtr;
	DoubleLLNode<_ItemType>* trailerPtr;
	DoubleLLNode<_ItemType>* currentPos;
	//int eleNum;
};


























