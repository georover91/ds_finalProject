#include "string_.h"
typedef string ItemType;



template <class _ItemType>
struct NodeType {
	NodeType<_ItemType>* topPtr;
	_ItemType info;
	NodeType<_ItemType>* bottomPtr;
};

template <class _ItemType>
class DoubleLL {
public:
	DoubleLL();
	//DoubleLL(DoubleLL& copiedDoubleLL);
	//~DoubleLL();
	void GoToTop();
	void GoToBottom();
	void GoToNextPos();
	void FindItem(_ItemType item, bool& found);
	void InsertLine(const char newline[]);
	void Print();

private:
	NodeType<_ItemType>* headerPtr;
	NodeType<_ItemType>* trailerPtr;
	NodeType<_ItemType>* currentPos;
	//int eleNum;
};


