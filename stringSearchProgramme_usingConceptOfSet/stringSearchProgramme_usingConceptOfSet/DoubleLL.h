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
	void MakeEmpty();
	bool IsEmpty() const;
	bool IsFull() const;
	void GoToTop();
	void GoToBottom();
	void GoToBeforePos();
	void GoToNextPos();
	DoubleLLNode<_ItemType>* WhatIsCurrentPos();
	DoubleLLNode<_ItemType>* WhatIsHeaderPtr();
	DoubleLLNode<_ItemType>* WhatIsTrailerPtr();
	void InsertLine(_ItemType newline);
	void DeleteLine();		
	void Insert_with_Deleting_nextPos(_ItemType newline);

private:
	DoubleLLNode<_ItemType>* headerPtr;
	DoubleLLNode<_ItemType>* trailerPtr;
	DoubleLLNode<_ItemType>* currentPos;
};



