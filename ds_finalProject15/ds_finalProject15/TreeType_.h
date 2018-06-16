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
///
//////////////////////////////////////////////////////////////////////////////////



// CopyTree & Operator=Overloading /////////////////////////////////////////
void CopyTree(TreeNode<ItemType>*& copy, const TreeNode<ItemType>* originalTree);

template<class _ItemType>
Tree<_ItemType>::Tree(const Tree<_ItemType>& originalTree)
// Calls recursive function CopyTree to copy originalTree 
//  into root.
{
	CopyTree(root, originalTree.root);
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
void Tree<_ItemType>::Merge(Tree<_ItemType>& operand)
{
	_ItemType tempItem;
	bool finished = false;

	operand.ResetTree(IN_ORDER);
	while (!finished) {
		operand.GetNextItem(tempItem, IN_ORDER, finished);
		InsertItem(tempItem);
	}
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
void Tree<_ItemType>::Extract(Tree<_ItemType>& operand)
{
	_ItemType tempItem;
	bool finished = false;
	bool found = true;

	operand.ResetTree(IN_ORDER);
	while (!finished) {
		operand.GetNextItem(tempItem, IN_ORDER, finished);
		RetrieveItem(tempItem, found);
		if (found) {
			DeleteItem(tempItem);
		}
		else {}
	}
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

/*		// 이렇게 함수 안에서 포이트 선언하고, 그 포인터에 객체를 동적할당 하고, 그 포인터가 가리키는 객체를 반환하는 것으로 하면, 그 함수내에서 동적할당된 객체가 함수 밖으로 제대로 전달 안된다. 그 동적할당된 객체의 포인터를 반환하는 것은 제대로 리턴 될듯. 
template<class _ItemType>
Tree<_ItemType> Tree<_ItemType>::operator*(Tree<_ItemType>& operand)
{
	Tree<_ItemType>* tempTreePtr;
	tempTreePtr = new Tree<_ItemType>;

	string getString1;
	string getString2;
	bool finished1 = false;
	bool finished2 = false;

	MakeInQueEmpty();
	ResetTree(IN_ORDER);
	while (!finished1) {
		GetNextItem(getString1, IN_ORDER, finished1);

		operand.MakeInQueEmpty();
		operand.ResetTree(IN_ORDER);
		while (!finished2) {
			operand.GetNextItem(getString2, IN_ORDER, finished2);

			if (getString1 == getString2) {
				InsertItem(getString1);
				break;		// 이 Tree class에서는 같은 key값을 중복삽입할 수 없으므로, 동일한 것을 찾으면 다시 동일한 것을 또 찾는데 시간 쏟을 것이 아니라, 바로 다음 원소를 찾도록 한다.
			}
		}
	}

	//MakeInQueEmpty();
	//operand.MakeInQueEmpty();

	return *tempTreePtr;
}
*/
///////////////////////////////////////////////////////////////////////////



// IsEmpty & IsFull & EleNumIs & Rootis /////////////////////////////////////////////////
template<class _ItemType>
bool Tree<_ItemType>::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
	return root == NULL;
}

template<class _ItemType>
bool Tree<_ItemType>::IsFull() const
// Returns true if there is no room for another item 
//  on the free store; false otherwise.
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
// Calls recursive function CountNodes to count the 
// nodes in the tree.
{
	return CountNodes(root);
}

int CountNodes(TreeNode<ItemType>* tree)
// Post: returns the number of nodes in the tree.
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


///////////////////////////////////////////////////////////////////////////////



// InsertItme & DeleteItem & RetrieveItem /////////////////////////////////
/// InsertItme ///
void Insert(TreeNode<ItemType>*& tree, ItemType item);

template<class _ItemType>
void Tree<_ItemType>::InsertItem(_ItemType item)
// Calls recursive function Insert to insert item into tree.
{
	//bool found;
	//Retrieve(root, item, found);
	
	//if (!found) {
		Insert(root, item);
		eleNum++;
		
		if (item.length() > maxLength) {
			maxLength = item.length();
		}
	//}
}


void Insert(TreeNode<ItemType>*& tree, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
	if (tree == NULL)
	{// Insertion place found.
		tree = new TreeNode<ItemType>;
		tree->rightPtr = NULL;
		tree->leftPtr = NULL;
		tree->info = item;
	}
	else if (item < tree->info)
		Insert(tree->leftPtr, item);    // Insert in leftPtr subtree.
	else
		Insert(tree->rightPtr, item);   // Insert in rightPtr subtree.
}
///

/// DeleteItem ///
void Delete(TreeNode<ItemType>*& tree, ItemType item);
void DeleteNode(TreeNode<ItemType>*& tree);
void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data);

template<class _ItemType>
void Tree<_ItemType>::DeleteItem(_ItemType item)
// Calls recursive function Delete to delete item from tree.
{
	Delete(root, item);
	eleNum--;
}

void Delete(TreeNode<ItemType>*& tree, ItemType item)
// Deletes item from tree.
// Post:  item is not in tree.
{
	if (item < tree->info)
		Delete(tree->leftPtr, item);   // Look in leftPtr subtree.
	else if (item > tree->info)
		Delete(tree->rightPtr, item);  // Look in rightPtr subtree.
	else
		DeleteNode(tree);           // Node found; call DeleteNode.
}

void DeleteNode(TreeNode<ItemType>*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no 
//       longer in the tree.  If tree is a leaf node or has only 
//       non-NULL child pointer the node pointed to by tree is 
//       deleted; otherwise, the user's data is replaced by its 
//       logical predecessor and the predecessor's node is deleted.
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
///

/// RetrieveItem ///
void Retrieve(TreeNode<ItemType>* tree, ItemType& item, bool& found);

template<class _ItemType>
void Tree<_ItemType>::RetrieveItem(_ItemType& item, bool& found)
// Calls recursive function Retrieve to search the tree for item.
{
	Retrieve(root, item, found);
}

void Retrieve(TreeNode<ItemType>* tree, ItemType& item, bool& found)
	// Recursively searches tree for item.
	// Post: If there is an element someItem whose key matches item's,
	//       found is true and item is set to a copy of someItem; 
	//       otherwise found is false and item is unchanged.
{
	if (tree == NULL)
		found = false;                     // item is not found.
	else if (item < tree->info)
		Retrieve(tree->leftPtr, item, found); // Search leftPtr subtree.
	else if (item > tree->info)
		Retrieve(tree->rightPtr, item, found);// Search rightPtr subtree.
	else		// item == tree->info 인 경우.
	{
		item = tree->info;                 // item is found.
		found = true;
	}
}
///
///////////////////////////////////////////////////////////////////////////



// Print & Print_Reverse ////////////////////////////////////////////////////////////
/// Print ///
void PrintTree(TreeNode<ItemType>* tree);

template<class _ItemType>
void Tree<_ItemType>::Print() const
// Calls recursive function Print to print items in the tree.
{
	PrintTree(root);
}

void PrintTree(TreeNode<ItemType>* tree)
// Prints info member of items in tree in sorted order on outFile.
{
	if (tree != NULL)
	{
		PrintTree(tree->leftPtr);   // Print leftPtr subtree.
		cout << tree->info << endl;
		//outFile << tree->info << endl;
		PrintTree(tree->rightPtr);  // Print rightPtr subtree.
	}
}

void PrintTree(TreeNode<ItemType>* tree, std::ofstream& outFile);

template<class _ItemType>
void Tree<_ItemType>::Print(std::ofstream& outFile) const
// Calls recursive function Print to print items in the tree.
{
	PrintTree(root, outFile);
}

void PrintTree(TreeNode<ItemType>* tree, std::ofstream& outFile)
// Prints info member of items in tree in sorted order on outFile.
{
	if (tree != NULL)
	{
		PrintTree(tree->leftPtr, outFile);   // Print leftPtr subtree.
		cout << tree->info << endl;
		outFile << tree->info << endl;
		PrintTree(tree->rightPtr, outFile);  // Print rightPtr subtree.
	}
}


void PrintTree_with_Num(TreeNode<ItemType>* tree, int& i);

template<class _ItemType>
void Tree<_ItemType>::Print_with_Num() const
// Calls recursive function Print to print items in the tree.
{
	int i = 0;
	PrintTree_with_Num(root, i);
}

void PrintTree_with_Num(TreeNode<ItemType>* tree, int& i)
// Prints info member of items in tree in sorted order on outFile.
{
	if (tree != NULL)
	{
		PrintTree_with_Num(tree->leftPtr, i);   // Print leftPtr subtree.
		i++;
		cout << i << ".   ";
		cout << tree->info << endl;
		//outFile << tree->info << endl;
		PrintTree_with_Num(tree->rightPtr, i);  // Print rightPtr subtree.
	}
}

void PrintTree_with_Num(TreeNode<ItemType>* tree, int& i, std::ofstream& outFile);

template<class _ItemType>
void Tree<_ItemType>::Print_with_Num(std::ofstream& outFile) const
// Calls recursive function Print to print items in the tree.
{
	int i = 0;
	PrintTree_with_Num(root, i, outFile);
}

void PrintTree_with_Num(TreeNode<ItemType>* tree, int& i, std::ofstream& outFile)
// Prints info member of items in tree in sorted order on outFile.
{
	if (tree != NULL)
	{
		PrintTree_with_Num(tree->leftPtr, i, outFile);   // Print leftPtr subtree.
		i++;
		//cout << i << ".   ";
		outFile << i << ".   ";
		//cout << tree->info << endl;
		outFile << tree->info << endl;
		PrintTree_with_Num(tree->rightPtr, i, outFile);  // Print rightPtr subtree.
	}
}
///


/// Print_Reverse ///
void PrintTree_Reverse(TreeNode<ItemType>* tree);

template<class _ItemType>
void Tree<_ItemType>::Print_Reverse() const
// Calls recursive function Print to print items in the tree.
{
	PrintTree_Reverse(root);
}

void PrintTree_Reverse(TreeNode<ItemType>* tree)
// Prints info member of items in tree in sorted order on outFile.
{
	if (tree != NULL)
	{
		PrintTree_Reverse(tree->rightPtr);   // Print leftPtr subtree.
		cout << tree->info << endl;
		//outFile << tree->info << endl;
		PrintTree_Reverse(tree->leftPtr);  // Print rightPtr subtree.
	}
}

void PrintTree_Reverse(TreeNode<ItemType>* tree, std::ofstream& outFile);

template<class _ItemType>
void Tree<_ItemType>::Print_Reverse(std::ofstream& outFile) const
// Calls recursive function Print to print items in the tree.
{
	PrintTree_Reverse(root, outFile);
}

void PrintTree_Reverse(TreeNode<ItemType>* tree, std::ofstream& outFile)
// Prints info member of items in tree in sorted order on outFile.
{
	if (tree != NULL)
	{
		PrintTree_Reverse(tree->rightPtr, outFile);   // Print leftPtr subtree.
		//cout << tree->info << endl;
		outFile << tree->info << endl;
		PrintTree_Reverse(tree->leftPtr, outFile);  // Print rightPtr subtree.
	}
}


void PrintTree_Reverse_with_Num(TreeNode<ItemType>* tree, int& i);

template<class _ItemType>
void Tree<_ItemType>::Print_Reverse_with_Num() const
// Calls recursive function Print to print items in the tree.
{
	int i = 0;
	PrintTree_Reverse_with_Num(root, i);
}

void PrintTree_Reverse_with_Num(TreeNode<ItemType>* tree, int& i)
// Prints info member of items in tree in sorted order on outFile.
{
	if (tree != NULL)
	{
		PrintTree_Reverse_with_Num(tree->rightPtr, i);   // Print leftPtr subtree.
		i++;
		cout << i << ".   ";
		cout << tree->info << endl;
		//outFile << tree->info << endl;
		PrintTree_Reverse_with_Num(tree->leftPtr, i);  // Print rightPtr subtree.
	}
}

void PrintTree_Reverse_with_Num(TreeNode<ItemType>* tree, int& i, std::ofstream& outFile);

template<class _ItemType>
void Tree<_ItemType>::Print_Reverse_with_Num(std::ofstream& outFile) const
// Calls recursive function Print to print items in the tree.
{
	int i = 0;
	PrintTree_Reverse_with_Num(root, i, outFile);
}

void PrintTree_Reverse_with_Num(TreeNode<ItemType>* tree, int& i, std::ofstream& outFile)
// Prints info member of items in tree in sorted order on outFile.
{
	if (tree != NULL)
	{
		PrintTree_Reverse_with_Num(tree->rightPtr, i, outFile);   // Print leftPtr subtree.
		i++;
		//cout << i << ".   ";
		outFile << i << ".   ";
		//cout << tree->info << endl;
		outFile << tree->info << endl;
		PrintTree_Reverse_with_Num(tree->leftPtr, i, outFile);  // Print rightPtr subtree.
	}
}
///
///////////////////////////////////////////////////////////////////////




// Reset in Pre, In, Post orders & GetNextItem //////////////////////////////////////////////
void PreOrder(TreeNode<ItemType>*, Que<ItemType>&);		// Enqueues tree items in preorder.
void InOrder(TreeNode<ItemType>*, Que<ItemType>&);		// Enqueues tree items in inorder.
void PostOrder(TreeNode<ItemType>*, Que<ItemType>&);	// Enqueues tree items in postorder.

template<class _ItemType>
void Tree<_ItemType>::ResetTree(OrderType order)
// Calls function to create a queue of the tree elements in 
// the desired order.
{
	switch (order)
	{
	case PRE_ORDER: PreOrder(root, preQue);
		break;
	case IN_ORDER: InOrder(root, inQue);
		break;
	case POST_ORDER: PostOrder(root, postQue);
		break;
	}
}

void PreOrder(TreeNode<ItemType>* tree, Que<ItemType>& preQue)
	// Post: preQue contains the tree items in preorder.
{
	if (tree != NULL)
	{
		preQue.Enqueue(tree->info);
		PreOrder(tree->leftPtr, preQue);
		PreOrder(tree->rightPtr, preQue);
	}
}

void InOrder(TreeNode<ItemType>* tree, Que<ItemType>& inQue)
	// Post: inQue contains the tree items in inorder.
{
	if (tree != NULL)
	{
		InOrder(tree->leftPtr, inQue);
		inQue.Enqueue(tree->info);
		InOrder(tree->rightPtr, inQue);
	}
}

void PostOrder(TreeNode<ItemType>* tree, Que<ItemType>& postQue)
	// Post: postQue contains the tree items in postorder.
{
	if (tree != NULL)
	{
		PostOrder(tree->leftPtr, postQue);
		PostOrder(tree->rightPtr, postQue);
		postQue.Enqueue(tree->info);
	}
}

template<class _ItemType>
void Tree<_ItemType>::GetNextItem(_ItemType& item, OrderType order, bool& finished)
// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
//       If item is the last one in the queue, finished is true; 
//       otherwise finished is false.
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
	}
}
//////////////////////////////////////////////////////////////////////////
