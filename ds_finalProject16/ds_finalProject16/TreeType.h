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

enum OrderType { PRE_ORDER, IN_ORDER, POST_ORDER, REVERSE_ORDER };



template<class _ItemType>
class Tree
{
public:
	Tree();		
	~Tree();	
	Tree(const Tree<_ItemType>& originalTree);
	void operator=(const Tree<_ItemType>& originalTree);	// copy constructor
	bool operator==(const Tree<_ItemType>& anotherTree);
	bool operator!=(const Tree<_ItemType>& anotherTree);
	bool compareTrees(TreeNode<_ItemType>* thisRoot, TreeNode<_ItemType>* anotherRoot);
	Tree<_ItemType> operator+(Tree<_ItemType>& operand);
	Tree<_ItemType> operator-(Tree<_ItemType>& operand);
	Tree<_ItemType> operator*(Tree<_ItemType>& operand);
	void MakeEmpty();
	void MakeInQueEmpty();
	void MakeReverseQueEmpty();
	bool IsEmpty() const;
	bool IsFull() const;
	int EleNumIs() const;
	int MaxLengthIs() const;
	TreeNode<_ItemType>* RootIs() const;
	void InsertItem(_ItemType item);
	void DeleteItem(_ItemType item);
	void RetrieveItem(_ItemType& item, bool& found);
	void ResetTree(OrderType order);
	void GetNextItem(_ItemType& item, OrderType order, bool& finished);
	void Print() const;
	void Print(std::ofstream& outFile) const;
	void Print_with_Num() const;
	void Print_with_Num(std::ofstream& outFile) const;
	void Print_Reverse() const;
	void Print_Reverse(std::ofstream& outFile) const;
	void Print_Reverse_with_Num() const;
	void Print_Reverse_with_Num(std::ofstream& outFile) const;
	
private:
	TreeNode<_ItemType>* root;
	Que<_ItemType> preQue;
	Que<_ItemType> inQue;
	Que<_ItemType> postQue;
	Que<_ItemType> reverseQue;
	unsigned int eleNum;
	unsigned int maxLength;		// Tree의 원소인 문자열 중 가장 긴 문자열 길이를 가진 문자열의 문자열 길이.
};