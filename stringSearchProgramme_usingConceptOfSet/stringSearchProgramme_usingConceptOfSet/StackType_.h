#include "StackType.h"



template<class _ItemType>
Stack<_ItemType>::Stack()	
{
	topPtr = NULL;
}

template<class _ItemType>
Stack<_ItemType>::~Stack()
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
{
	return (topPtr == NULL);
}

template<class _ItemType>
bool Stack<_ItemType>::IsFull() const
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



template<class _ItemType>
void Stack<_ItemType>::Push(_ItemType newItem)
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
void Stack<_ItemType>::Top(_ItemType& item)
{
	if (IsEmpty())
		throw EmptyStack();
	else
		item = (topPtr->info);
}

template<class _ItemType>
_ItemType* Stack<_ItemType>::Top()
{
	if (IsEmpty())
		throw EmptyStack();
	else
		return (topPtr->info);
}






