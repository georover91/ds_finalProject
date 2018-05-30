// Implementation file for StackType.h
#include "StackType.h"



// Class constructor & Class destructor //////////////////////////////
template<class _ItemType>
Stack<_ItemType>::Stack()	// Class constructor.
{
	topPtr = NULL;
}

template<class _ItemType>
Stack<_ItemType>::~Stack()
// Post: stack is empty; all items have been deallocated.
{
	StackNode<_ItemType>* tempPtr;

	while (topPtr != NULL)
	{
		tempPtr = topPtr;
		topPtr = topPtr->nextPtr;
		delete tempPtr;
	}
}
///////////////////////////////////////////////////////////////////



// IsEmpty & IsFull /////////////////////////////////////////////////
template<class _ItemType>
void Stack<_ItemType>::MakeEmpty()
{
	StackNode<_ItemType>* tempPtr;

	while (topPtr != NULL)
	{
		tempPtr = topPtr;
		topPtr = topPtr->nextPtr;
		delete tempPtr;
	}
}

template<class _ItemType>
bool Stack<_ItemType>::IsEmpty() const
// Returns true if there are no elements on the stack; false otherwise.
{
	return (topPtr == NULL);
}

template<class _ItemType>
bool Stack<_ItemType>::IsFull() const
// Returns true if there is no room for another ItemType 
//  on the free store; false otherwise.
{
	StackNode<_ItemType>* location;
	try
	{
		location = new StackNode<_ItemType>;
		delete location;
		return false;
	}
	catch (std::bad_alloc)
	{
		return true;
	}
}
////////////////////////////////////////////////////////////////////



// Push & Pop & Top ///////////////////////////////////////////////
template<class _ItemType>
void Stack<_ItemType>::Push(_ItemType newItem)
// Adds newItem to the top of the stack.
// Pre:  Stack has been initialized.
// Post: If stack is full, FullStack exception is thrown;
//       else newItem is at the top of the stack.
{
	if (IsFull())
		throw FullStack();
	else
	{
		StackNode<_ItemType>* location;
		location = new StackNode<_ItemType>;
		location->info = newItem;
		location->nextPtr = topPtr;
		topPtr = location;
	}
}

template<class _ItemType>
void Stack<_ItemType>::Pop()
// Removes top item from Stack and returns it in item.
// Pre:  Stack has been initialized.
// Post: If stack is empty, EmptyStack exception is thrown;
//       else top element has been removed.
{
	if (IsEmpty())
		throw EmptyStack();
	else
	{
		StackNode<_ItemType>* tempPtr;
		tempPtr = topPtr;
		topPtr = topPtr->nextPtr;
		delete tempPtr;
	}
}

template<class _ItemType>
_ItemType* Stack<_ItemType>::Top()
// Returns a copy of the top item in the stack.
// Pre:  Stack has been initialized.
// Post: If stack is empty, EmptyStack exception is thrown;
//       else a copy of the top element is returned.
{
	if (IsEmpty())
		throw EmptyStack();
	else
		return (topPtr->info);
}

template<class _ItemType>
void Stack<_ItemType>::Top(_ItemType& item)
// Returns a copy of the top item in the stack.
// Pre:  Stack has been initialized.
// Post: If stack is empty, EmptyStack exception is thrown;
//       else a copy of the top element is returned.
{
	if (IsEmpty())
		throw EmptyStack();
	else
		item = (topPtr->info);
}
///////////////////////////////////////////////////////////////////////////






