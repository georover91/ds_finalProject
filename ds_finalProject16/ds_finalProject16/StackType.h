//#include <cstddef>
//#include <new>
#include "string_.h"



template<class _ItemType>
struct StackNode
{
	_ItemType info;
	StackNode<_ItemType>* nextPtr;
};

class FullStack
{};

class EmptyStack
{};



template<class _ItemType>
class Stack
{
public:
	Stack();
	~Stack();
	void MakeEmpty();
	bool IsEmpty() const;
	bool IsFull() const;
	void Push(_ItemType item);
	void Pop();
	void Top(_ItemType& item);
	_ItemType* Top();
private:
	StackNode<_ItemType>* topPtr;
};


