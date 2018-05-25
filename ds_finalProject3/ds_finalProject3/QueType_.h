#include "QueType.h"



// Class constructor ////////////////////////////////////////////////
template<class _ItemType>
Que<_ItemType>::Que()          
// Post:  firstPtr and lastPtr are set to NULL.
{
	firstPtr = NULL;
	lastPtr = NULL;
}



// Class Destructor & MakeEmpty //////////////////////////////////////////////////
template<class _ItemType>
void Que<_ItemType>::MakeEmpty()
// Post: Queue is empty; all elements have been deallocated.
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



// Class copy constructor //////////////////////////////////////////////////////
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



// IsFull & IsEmpty ///////////////////////////////////////////
template<class _ItemType>
bool Que<_ItemType>::IsEmpty() const
// Returns true if there are no elements on the queue; false otherwise.
{
	return (firstPtr == NULL);
}

template<class _ItemType>
bool Que<_ItemType>::IsFull() const
// Returns true if there is no room for another ItemType 
//  on the free store; false otherwise.
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



// Enqueue & Dequeue //////////////////////////////////////////////////////
template<class _ItemType>
void Que<_ItemType>::Enqueue(_ItemType newItem)
// Adds newItem to the lastPtr of the queue.
// Pre:  Queue has been initialized.
// Post: If (queue is not full) newItem is at the lastPtr of the queue;
//       otherwise a FullQueue exception is thrown.  

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
// Removes firstPtr item from the queue and returns it in item.
// Pre:  Queue has been initialized and is not empty.
// Post: If (queue is not empty) the firstPtr of the queue has been 
//       removed and a copy returned in item; 
//       othersiwe a EmptyQueue exception has been thrown.
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


