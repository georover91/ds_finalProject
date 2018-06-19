#include "string_.h"



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
	void MakeEmpty();
	~Que();
	//Que(const Que& anotherQue);
	bool IsEmpty() const;
	bool IsFull() const;
	void Enqueue(_ItemType newItem);
	void Dequeue(_ItemType& item);

private:
	QueNode<_ItemType>* firstPtr;
	QueNode<_ItemType>* lastPtr;
};
