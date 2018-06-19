#include "TreeType.h"

// 1.	Test t1;		=> 기본 생성자
//		Test t2(t1);	=> 복사 생성자
//		Test t3 = t1;	=> 복사 생성자
//		t1 = t2;		=> 복사 대입 연산자
//
//		cout << isEmpty(t1) << endl; = > Call - by - Value는 복사 생성자	// 즉, IsEmpty함수에 인수로 t1이 전달될 때에는, 함수 내에서 Test t(t1)시의 복사생성자가 작용하는 것과 같다.
//
//		bool isEmpty(Test t) {
//			if (t.getMember() == 0)
//				return true;
//			return false;
//		}
//
// 2.	'대입연산자'와 '할당연산자'는 같은 말이다. 즉 둘 모두 'operator='를 의미.
// 3.	객체에는 기본적으로 컴파일러가 제공하는 '디폴트 대입연산자'가 있다.
//		이 '디폴트 대입연산자'는 엄연히 '디폴트 생성자'와는 다르다.
//		'대입연산자'와 '생성자'는 다른 것이므로 위도 서로 다른 것은 당연한 사실일 것이다.
/////////////////////////////


// Class constructor & Class Destructor & MakeEmpty /////////////////////////////////
/// Class constructor /// 
template<class _ItemType>
Tree<_ItemType>::Tree()
{
	root = NULL;
	eleNum = 0;
	maxLength = 0;
}
///

/// Class Destructor ///
void Destroy(TreeNode<ItemType>*& tree);

template<class _ItemType>
Tree<_ItemType>::~Tree()
// Calls recursive function Destroy to destroy the tree.
{
	Destroy(root);
}

void Destroy(TreeNode<ItemType>*& tree)
// Post: tree is empty; nodes have been deallocated.
{
	if (tree != NULL)
	{
		Destroy(tree->leftPtr);
		Destroy(tree->rightPtr);
		delete tree;
	}
}
///

/// MakeEmpty ///
template<class _ItemType>
void Tree<_ItemType>::MakeEmpty()
{
	Destroy(root);
	root = NULL;
	eleNum = 0;
	maxLength = 0;
}

template<class _ItemType>
void Tree<_ItemType>::MakeInQueEmpty()
{
	inQue.MakeEmpty();
}

template<class _ItemType>
void Tree<_ItemType>::MakeReverseQueEmpty()
{
	reverseQue.MakeEmpty();
}
///
//////////////////////////////////////////////////////////////////////////////////



// CopyTree & Operator=Overloading /////////////////////////////////////////
void CopyTree(TreeNode<ItemType>*& copy, const TreeNode<ItemType>* originalTree);

template<class _ItemType>
Tree<_ItemType>::Tree(const Tree<_ItemType>& originalTree)
// Calls recursive function CopyTree to copy originalTree 
//  into root.
{
	CopyTree(root, originalTree.RootIs());
	eleNum = originalTree.eleNum;
	maxLength = originalTree.maxLength;
}

void CopyTree(TreeNode<ItemType>*& copy, const TreeNode<ItemType>* originalTree)
// Post: copy is the root of a tree that is a duplicate 
//       of originalTree.
{
	if (originalTree == NULL)
		copy = NULL;
	else
	{
		copy = new TreeNode<ItemType>;
		copy->info = originalTree->info;
		CopyTree(copy->leftPtr, originalTree->leftPtr);
		CopyTree(copy->rightPtr, originalTree->rightPtr);
	}
} // Function prototypes for auxiliary functions.

template<class _ItemType>
void Tree<_ItemType>::operator=(const Tree<_ItemType>& originalTree)
// Calls recursive function CopyTree to copy originalTree 
// into root.
{
	{
		if (&originalTree == this)
			return;             // Ignore assigning self to self
		Destroy(root);      // Deallocate existing tree nodes
		CopyTree(root, originalTree.RootIs());
	}

	eleNum = originalTree.eleNum;
	maxLength = originalTree.maxLength;
}

template<class _ItemType>
bool Tree<_ItemType>::operator==(const Tree<_ItemType>& anotherTree)
{
	if (this == &anotherTree) {
		return true;
	}
	else {
		TreeNode<_ItemType>* anotherRoot = anotherTree.RootIs();
		return compareTrees(root, anotherRoot);
	}
}

template<class _ItemType>
bool Tree<_ItemType>::operator!=(const Tree<_ItemType>& anotherTree)
{
	if (this == &anotherTree) {
		return false;
	}
	else {
		TreeNode<_ItemType>* anotherRoot = anotherTree.RootIs();
		return (!compareTrees(root, anotherRoot));
	}
}

template<class _ItemType>
bool Tree<_ItemType>::compareTrees(TreeNode<_ItemType>* thisRoot, TreeNode<_ItemType>* anotherRoot)
{
	if ((thisRoot == NULL) && (anotherRoot == NULL)) {
		return true;
	}
	else if ((thisRoot != NULL) && (anotherRoot == NULL)) {
		return false;
	}
	else if ((thisRoot == NULL) && (anotherRoot != NULL)) {
		return false;
	}
	// root->info != anotherRoot->info
	// compareTrees(thisRoot->leftPtr, anotherRoot->leftPtr);
	//compareTrees(thisRoot->rightPtr, anotherRoot->rightPtr);
	if ((thisRoot->info) != (anotherRoot->info)) {
		return false;
	}
	else if (compareTrees(thisRoot->leftPtr, anotherRoot->leftPtr) == false) {
		return false;
	}
	else if (compareTrees(thisRoot->rightPtr, anotherRoot->rightPtr) == false) {
		return false;
	}
	else {
		return true;
	}
}
//////////////////////////////////////////////////////



// operator+(Merge) & operator-(Extract) & operator* //////////////////////////////
template<class _ItemType>
Tree<_ItemType> Tree<_ItemType>::operator+(Tree<_ItemType>& operand)
{
	Tree<_ItemType> tempTree;
	tempTree = *this;

	if (!operand.IsEmpty()) {
		_ItemType tempItem;
		bool finished = false;
		bool found = true;		//RetrieveItem 함수 안에서 false로 초기화 됨.

		operand.ResetTree(IN_ORDER);
		while (!finished) {
			operand.GetNextItem(tempItem, IN_ORDER, finished);
			tempTree.RetrieveItem(tempItem, found);
			if (!found) {
				tempTree.InsertItem(tempItem);
			}
			//else {}
		}
	}

	return tempTree;
}

template<class _ItemType>
Tree<_ItemType> Tree<_ItemType>::operator-(Tree<_ItemType>& operand)
{
	Tree<_ItemType> tempTree;
	tempTree = *this;

	if (!operand.IsEmpty()) {
		_ItemType tempItem;
		bool finished = false;
		bool found = true;

		if (!operand.IsEmpty()) {		//operand.IsEmpty() == true이면, *this를 반환하도록 하기 위함.
			operand.ResetTree(IN_ORDER);
			while (!finished) {
				operand.GetNextItem(tempItem, IN_ORDER, finished);		//operand 트리에 원소가 하나도 없으면, operand의 inQue에서 Dequeue할 때, 할당하지 않은 메모리 참조 오류남.
				tempTree.RetrieveItem(tempItem, found);
				if (found) {
					tempTree.DeleteItem(tempItem);
				}
			}
		}
	}

	return tempTree;
}

template<class _ItemType>
Tree<_ItemType> Tree<_ItemType>::operator*(Tree<_ItemType>& operand)
{
	Tree<_ItemType> tempTree;

	_ItemType getString1;
	_ItemType getString2;
	bool finished1 = false;
	bool finished2 = false;

	//makeInQueEmpty();		//이거 할 필요없음. 어짜피 inQue가 다 비어서 finished가 true값이 되어야 while문을 빠져나올 수 있으므로. 
	finished1 = false;
	ResetTree(IN_ORDER);
	while (!(finished1)) {
		GetNextItem(getString1, IN_ORDER, finished1);

		if (!operand.IsEmpty()) {
			finished2 = false;
			operand.ResetTree(IN_ORDER);
			while (!(finished2)) {
				operand.GetNextItem(getString2, IN_ORDER, finished2);

				//cout << getString1 << endl;		// test code
				//cout << getString2 << endl;		// test code

				if (getString1 == getString2) {
					tempTree.InsertItem(getString1);
					break;		// 이 Tree class에서는 같은 key값을 중복삽입할 수 없으므로, 동일한 것을 찾으면 다시 동일한 것을 또 찾는데 시간 쏟을 것이 아니라, 바로 다음 원소를 찾도록 한다.
				}
			}
		}
	}

	return tempTree;
}



template<class _ItemType>
bool Tree<_ItemType>::IsEmpty() const
{
	return root == NULL;
}

template<class _ItemType>
bool Tree<_ItemType>::IsFull() const
{
	TreeNode<_ItemType>* location;
	try
	{
		location = new TreeNode<_ItemType>;
		delete location;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}

int CountNodes(TreeNode<ItemType>* tree);

template<class _ItemType>
int Tree<_ItemType>::EleNumIs() const
{
	return CountNodes(root);
}

int CountNodes(TreeNode<ItemType>* tree)
{
	if (tree == NULL)
		return 0;
	else
		return CountNodes(tree->leftPtr) + CountNodes(tree->rightPtr) + 1;
}

template<class _ItemType>
int Tree<_ItemType>::MaxLengthIs() const
{
	return maxLength;
}

template<class _ItemType>
TreeNode<_ItemType>* Tree<_ItemType>::RootIs() const
{
	return root;
}



void Insert(TreeNode<ItemType>*& tree, ItemType item);

template<class _ItemType>
void Tree<_ItemType>::InsertItem(_ItemType item)
{
	
	Insert(root, item);
	eleNum++;
		
	if (item.length() > maxLength) {
		maxLength = item.length();
	}
}

void Insert(TreeNode<ItemType>*& tree, ItemType item)
{
	if (tree == NULL)
	{
		tree = new TreeNode<ItemType>;
		tree->rightPtr = NULL;
		tree->leftPtr = NULL;
		tree->info = item;
	}
	else if (item < tree->info)
		Insert(tree->leftPtr, item);    
	else
		Insert(tree->rightPtr, item);   
}



void Delete(TreeNode<ItemType>*& tree, ItemType item);
void DeleteNode(TreeNode<ItemType>*& tree);
void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data);

template<class _ItemType>
void Tree<_ItemType>::DeleteItem(_ItemType item)
{
	Delete(root, item);
	eleNum--;
}

void Delete(TreeNode<ItemType>*& tree, ItemType item)
{
	if (item < tree->info)
		Delete(tree->leftPtr, item);  
	else if (item > tree->info)
		Delete(tree->rightPtr, item);  
	else
		DeleteNode(tree);          
}

void DeleteNode(TreeNode<ItemType>*& tree)
{
	ItemType data;
	TreeNode<ItemType>* tempPtr;

	tempPtr = tree;
	if (tree->leftPtr == NULL)
	{
		tree = tree->rightPtr;
		delete tempPtr;
	}
	else if (tree->rightPtr == NULL)
	{
		tree = tree->leftPtr;
		delete tempPtr;
	}
	else
	{
		GetPredecessor(tree->leftPtr, data);
		tree->info = data;
		Delete(tree->leftPtr, data);  // Delete predecessor node.
	}
}

void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data)
// Sets data to the info member of the rightPtr-most node in tree.
// 해당 노드보다 바로 앞순서 노드를 찾는 함수.
{
	while (tree->rightPtr != NULL)
		tree = tree->rightPtr;
	data = tree->info;
}



void Retrieve(TreeNode<ItemType>* tree, ItemType& item, bool& found);

template<class _ItemType>
void Tree<_ItemType>::RetrieveItem(_ItemType& item, bool& found)
{
	Retrieve(root, item, found);
}

void Retrieve(TreeNode<ItemType>* tree, ItemType& item, bool& found)
{
	if (tree == NULL)
		found = false;                 
	else if (item < tree->info)
		Retrieve(tree->leftPtr, item, found);
	else if (item > tree->info)
		Retrieve(tree->rightPtr, item, found);
	else	
	{
		item = tree->info;             
		found = true;
	}
}



void PreOrder(TreeNode<ItemType>*, Que<ItemType>&);			
void InOrder(TreeNode<ItemType>*, Que<ItemType>&);			
void PostOrder(TreeNode<ItemType>*, Que<ItemType>&);		
void ReverseOrder(TreeNode<ItemType>*, Que<ItemType>&);		

template<class _ItemType>
void Tree<_ItemType>::ResetTree(OrderType order)
{
	switch (order)
	{
	case PRE_ORDER: PreOrder(root, preQue);
		break;
	case IN_ORDER: InOrder(root, inQue);
		break;
	case POST_ORDER: PostOrder(root, postQue);
		break;
	case REVERSE_ORDER: ReverseOrder(root, reverseQue);
		break;
	}
}

void PreOrder(TreeNode<ItemType>* tree, Que<ItemType>& preQue)
{
	if (tree != NULL)
	{
		preQue.Enqueue(tree->info);
		PreOrder(tree->leftPtr, preQue);
		PreOrder(tree->rightPtr, preQue);
	}
}

void InOrder(TreeNode<ItemType>* tree, Que<ItemType>& inQue)
{
	if (tree != NULL)
	{
		InOrder(tree->leftPtr, inQue);
		inQue.Enqueue(tree->info);
		InOrder(tree->rightPtr, inQue);
	}
}

void PostOrder(TreeNode<ItemType>* tree, Que<ItemType>& postQue)
{
	if (tree != NULL)
	{
		PostOrder(tree->leftPtr, postQue);
		PostOrder(tree->rightPtr, postQue);
		postQue.Enqueue(tree->info);
	}
}

void ReverseOrder(TreeNode<ItemType>* tree, Que<ItemType>& reverseQue)
{
	if (tree != NULL)
	{
		ReverseOrder(tree->rightPtr, reverseQue);
		reverseQue.Enqueue(tree->info);
		ReverseOrder(tree->leftPtr, reverseQue);
	}
}


template<class _ItemType>
void Tree<_ItemType>::GetNextItem(_ItemType& item, OrderType order, bool& finished)
{
	finished = false;
	switch (order)
	{
	case PRE_ORDER: preQue.Dequeue(item);
		if (preQue.IsEmpty())
			finished = true;
		break;
	case IN_ORDER: inQue.Dequeue(item);
		if (inQue.IsEmpty())
			finished = true;
		break;
	case  POST_ORDER: postQue.Dequeue(item);
		if (postQue.IsEmpty())
			finished = true;
		break;
	case  REVERSE_ORDER: reverseQue.Dequeue(item);
		if (reverseQue.IsEmpty())
			finished = true;
		break;
	}
}



void PrintTree(TreeNode<ItemType>* tree);

template<class _ItemType>
void Tree<_ItemType>::Print() const
{
	PrintTree(root);
}

void PrintTree(TreeNode<ItemType>* tree)
{
	if (tree != NULL)
	{
		PrintTree(tree->leftPtr);
		cout << tree->info << endl;
		PrintTree(tree->rightPtr);
	}
}

void PrintTree(TreeNode<ItemType>* tree, std::ofstream& outFile);

template<class _ItemType>
void Tree<_ItemType>::Print(std::ofstream& outFile) const
{
	PrintTree(root, outFile);
}

void PrintTree(TreeNode<ItemType>* tree, std::ofstream& outFile)
{
	if (tree != NULL)
	{
		PrintTree(tree->leftPtr, outFile);
		cout << tree->info << endl;
		outFile << tree->info << endl;
		PrintTree(tree->rightPtr, outFile);
	}
}


void PrintTree_with_Num(TreeNode<ItemType>* tree, int& i);

template<class _ItemType>
void Tree<_ItemType>::Print_with_Num() const
{
	int i = 0;
	PrintTree_with_Num(root, i);
}

void PrintTree_with_Num(TreeNode<ItemType>* tree, int& i)
{
	if (tree != NULL)
	{
		PrintTree_with_Num(tree->leftPtr, i);
		i++;
		cout << i << ".   ";
		cout << tree->info << endl;
		PrintTree_with_Num(tree->rightPtr, i);
	}
}

void PrintTree_with_Num(TreeNode<ItemType>* tree, int& i, std::ofstream& outFile);

template<class _ItemType>
void Tree<_ItemType>::Print_with_Num(std::ofstream& outFile) const
{
	int i = 0;
	PrintTree_with_Num(root, i, outFile);
}

void PrintTree_with_Num(TreeNode<ItemType>* tree, int& i, std::ofstream& outFile)
{
	if (tree != NULL)
	{
		PrintTree_with_Num(tree->leftPtr, i, outFile);
		i++;
		outFile << i << ".   ";
		outFile << tree->info << endl;
		PrintTree_with_Num(tree->rightPtr, i, outFile);
	}
}



void PrintTree_Reverse(TreeNode<ItemType>* tree);

template<class _ItemType>
void Tree<_ItemType>::Print_Reverse() const
{
	PrintTree_Reverse(root);
}

void PrintTree_Reverse(TreeNode<ItemType>* tree)
{
	if (tree != NULL)
	{
		PrintTree_Reverse(tree->rightPtr);
		cout << tree->info << endl;
		PrintTree_Reverse(tree->leftPtr);
	}
}

void PrintTree_Reverse(TreeNode<ItemType>* tree, std::ofstream& outFile);

template<class _ItemType>
void Tree<_ItemType>::Print_Reverse(std::ofstream& outFile) const
{
	PrintTree_Reverse(root, outFile);
}

void PrintTree_Reverse(TreeNode<ItemType>* tree, std::ofstream& outFile)
{
	if (tree != NULL)
	{
		PrintTree_Reverse(tree->rightPtr, outFile);
		outFile << tree->info << endl;
		PrintTree_Reverse(tree->leftPtr, outFile);
	}
}

void PrintTree_Reverse_with_Num(TreeNode<ItemType>* tree, int& i);

template<class _ItemType>
void Tree<_ItemType>::Print_Reverse_with_Num() const
{
	int i = 0;
	PrintTree_Reverse_with_Num(root, i);
}

void PrintTree_Reverse_with_Num(TreeNode<ItemType>* tree, int& i)
{
	if (tree != NULL)
	{
		PrintTree_Reverse_with_Num(tree->rightPtr, i);
		i++;
		cout << i << ".   ";
		cout << tree->info << endl;
		PrintTree_Reverse_with_Num(tree->leftPtr, i);
	}
}

void PrintTree_Reverse_with_Num(TreeNode<ItemType>* tree, int& i, std::ofstream& outFile);

template<class _ItemType>
void Tree<_ItemType>::Print_Reverse_with_Num(std::ofstream& outFile) const
{
	int i = 0;
	PrintTree_Reverse_with_Num(root, i, outFile);
}

void PrintTree_Reverse_with_Num(TreeNode<ItemType>* tree, int& i, std::ofstream& outFile)
{
	if (tree != NULL)
	{
		PrintTree_Reverse_with_Num(tree->rightPtr, i, outFile);
		i++;
		outFile << i << ".   ";
		outFile << tree->info << endl;
		PrintTree_Reverse_with_Num(tree->leftPtr, i, outFile);
	}
}