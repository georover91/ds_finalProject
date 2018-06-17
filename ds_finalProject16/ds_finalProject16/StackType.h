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
// Exception class thrown by Push when stack is full.
{};

class EmptyStack
// Exception class thrown by Pop and Top when stack is emtpy.
{};

template<class _ItemType>
class Stack
{
public:
	Stack();
	// Class constructor.
	~Stack();
	void MakeEmpty();
	bool IsEmpty() const;
	// Function: Determines whether the stack is empty.
	// Pre:		 Stack has been initialized.
	// Post:	 Function value = (stack is empty)
	bool IsFull() const;
	// Function: Determines whether the stack is full.
	// Pre:		 Stack has been initialized.
	// Post:	 Function value = (stack is full)
	void Push(_ItemType item);
	// Function: Adds newItem to the top of the stack.
	// Pre:		 Stack has been initialized.
	// Post:	 If (stack is full), FullStack exception is thrown;
	//			otherwise, newItem is at the top of the stack.
	void Pop();
	// Function: Removes top item from the stack.
	// Pre:		 Stack has been initialized.
	// Post:	 If (stack is empty), EmptyStack exception is thrown;
	//			otherwise, top element has been removed from stack.
	_ItemType* Top();
	// Function: Returns a copy of top item on the stack.
	// Pre:		 Stack has been initialized.
	// Post:	 If (stack is empty), EmptyStack exception is thrown;
	//			otherwise, top element has been removed from stack.
	void Top(_ItemType& item);
private:
  StackNode<_ItemType>* topPtr;
};


