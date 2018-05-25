//#include <new>
//#include <cstddef>
#include "string_.h"
typedef string ItemType;



template<class _ItemType>
struct QueNode
{
	_ItemType info;
	QueNode<_ItemType>* nextPtr;
};

class FullQueue
{};

class EmptyQueue
{};

template<class _ItemType>
class Que
{
public:
	Que();
	// Class constructor.
	// Because there is a default constructor, the precondition 
	// that the queue has been initialized is omitted.
	void MakeEmpty();
	// Function: Initializes the queue to an empty state.
	// Post: Queue is empty.
	~Que();
	// Class destructor.
	Que(const Que& anotherQue);
	// Copy constructor
	bool IsEmpty() const;
	// Function: Determines whether the queue is empty.
	// Post: Function value = (queue is empty)
	bool IsFull() const;
	// Function: Determines whether the queue is full.
	// Post: Function value = (queue is full)
	void Enqueue(_ItemType newItem);
	// Function: Adds newItem to the rear of the queue.
	// Post: If (queue is full) FullQueue exception is thrown
	//       else newItem is at rear of queue.
	void Dequeue(_ItemType& item);
	// Function: Removes front item from the queue and returns it in item.
	// Post: If (queue is empty) EmptyQueue exception is thrown
	//       and item is undefined
	//       else front element has been removed from queue and
	//       item is a copy of removed element.

private:
	QueNode<_ItemType>* firstPtr;
	QueNode<_ItemType>* lastPtr;
};
