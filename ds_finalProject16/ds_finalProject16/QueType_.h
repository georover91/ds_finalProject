#include "QueType.h"




template<class _ItemType>
Que<_ItemType>::Que()          
{
	firstPtr = NULL;
	lastPtr = NULL;
}

template<class _ItemType>
void Que<_ItemType>::MakeEmpty()
{
	QueNode<_ItemType>* tempPtr;

	while (firstPtr != NULL)
	{
		tempPtr = firstPtr;
		firstPtr = firstPtr->nextPtr;
		delete tempPtr;
	}
	lastPtr = NULL;
}

template<class _ItemType>
Que<_ItemType>::~Que()
{
	MakeEmpty();
}

/*
template<class _ItemType>
Que<_ItemType>::Que(const Que& anotherQue)
{
	QueNode<_ItemType>* ptr1;
	QueNode<_ItemType>* ptr2;

	if (anotherQue.firstPtr == NULL)
		firstPtr = NULL;
	else
	{
		firstPtr = new QueNode<_ItemType>;
		firstPtr->info = (anotherQue.firstPtr)->info;
		ptr1 = anotherQue.firstPtr->nextPtr;
		ptr2 = firstPtr;
		while (ptr1 != NULL)
		{
			ptr2->nextPtr = new QueNode<_ItemType>;
			ptr2 = ptr2->nextPtr;
			ptr2->info = ptr1->info;
			ptr1 = ptr1->nextPtr;
		}
		ptr2->nextPtr = NULL;
		lastPtr = ptr2;
	}
}
*/


template<class _ItemType>
bool Que<_ItemType>::IsEmpty() const
{
	return (firstPtr == NULL);
}

template<class _ItemType>
bool Que<_ItemType>::IsFull() const
{
	QueNode<_ItemType>* location;
	try
	{
		location = new QueNode<_ItemType>;
		delete location;
		return false;
	}
	catch (std::bad_alloc)
	{
		return true;
	}
}



template<class _ItemType>
void Que<_ItemType>::Enqueue(_ItemType newItem)
{
	if (IsFull())
		throw FullQueue();
	else
	{
		QueNode<_ItemType>* newNode;

		newNode = new QueNode<_ItemType>;
		newNode->info = newItem;
		newNode->nextPtr = NULL;
		if (lastPtr == NULL)
			firstPtr = newNode;
		else
			lastPtr->nextPtr = newNode;
		lastPtr = newNode;
	}
}

template<class _ItemType>
void Que<_ItemType>::Dequeue(_ItemType& item)
{
	if (IsEmpty())
		throw EmptyQueue();
	else
	{
		QueNode<_ItemType>* tempPtr;

		tempPtr = firstPtr;
		item = firstPtr->info;
		firstPtr = firstPtr->nextPtr;
		if (firstPtr == NULL)
			lastPtr = NULL;
		delete tempPtr;
	}
}


