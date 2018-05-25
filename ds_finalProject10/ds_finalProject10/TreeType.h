//#include <string>		// <string>은 "QueType_.h" include한 것에 포함되어 있음.
#include <fstream>
#include "QueType_.h"



template<class _ItemType>
struct TreeNode
{
	TreeNode<_ItemType>* leftPtr;
	_ItemType info;
	TreeNode<_ItemType>* rightPtr;
};
enum OrderType { PRE_ORDER, IN_ORDER, POST_ORDER };

template<class _ItemType>
class Tree
{
public:
	Tree();		// constructor
	~Tree();	// destructor
	Tree(const Tree<_ItemType>& originalTree);
	void operator=(const Tree<_ItemType>& originalTree);	// copy constructor
	void Merge(Tree<_ItemType>& operand);
	void Extract(Tree<_ItemType>& operand);
	void MakeEmpty();
	bool IsEmpty() const;
	bool IsFull() const;
	int LengthIs() const;
	TreeNode<_ItemType>* RootIs() const;
	void InsertItem(_ItemType item);
	void DeleteItem(_ItemType item);
	void RetrieveItem(_ItemType& item, bool& found);
	void ResetTree(OrderType order);
	void GetNextItem(_ItemType& item, OrderType order,
		bool& finished);
	void Print(std::ofstream& outFile) const;
	void Print_Reverse(std::ofstream& outFile) const;
	
protected:
	TreeNode<_ItemType>* root;
	Que<_ItemType> preQue;
	Que<_ItemType> inQue;
	Que<_ItemType> postQue;
	int length;
};