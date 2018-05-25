#include "TreeType.h"



// Class constructor & Class Destructor & MakeEmpty /////////////////////////////////
// Class constructor // 
template<class _ItemType>
Tree<_ItemType>::Tree()
{
	root = NULL;
}
//

// Class Destructor //
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
//

// MakeEmpty //
template<class _ItemType>
void Tree<_ItemType>::MakeEmpty()
{
	Destroy(root);
	root = NULL;
}
//
//////////////////////////////////////////////////////////////////////////////////


// IsEmpty & IsFull & LengthIs /////////////////////////////////////////////////
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
int Tree<_ItemType>::LengthIs() const
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
///////////////////////////////////////////////////////////////////////////////



// InsertItme & DeleteItem & RetrieveItem /////////////////////////////////
// InsertItme //
void Insert(TreeNode<ItemType>*& tree, ItemType item);

template<class _ItemType>
void Tree<_ItemType>::InsertItem(_ItemType item)
// Calls recursive function Insert to insert item into tree.
{
	Insert(root, item);
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

// DeleteItem //
void Delete(TreeNode<ItemType>*& tree, ItemType item);
void DeleteNode(TreeNode<ItemType>*& tree);
void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data);

template<class _ItemType>
void Tree<_ItemType>::DeleteItem(_ItemType item)
// Calls recursive function Delete to delete item from tree.
{
	Delete(root, item);
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
{
	while (tree->rightPtr != NULL)
		tree = tree->rightPtr;
	data = tree->info;
}
//

// RetrieveItem //
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
	else
	{
		item = tree->info;                 // item is found.
		found = true;
	}
}
//
///////////////////////////////////////////////////////////////////////////



// Print & Print_Reverse ////////////////////////////////////////////////////////////
// Print //
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
//

// Print_Reverse //
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
		cout << tree->info << endl;
		outFile << tree->info << endl;
		PrintTree_Reverse(tree->leftPtr, outFile);  // Print rightPtr subtree.
	}
}
//
///////////////////////////////////////////////////////////////////////






















void CopyTree(TreeNode<ItemType>*& copy,
	const TreeNode<ItemType>* originalTree);

template<class _ItemType>
Tree<_ItemType>::Tree(const Tree<_ItemType>& originalTree)
// Calls recursive function CopyTree to copy originalTree 
//  into root.
{
	CopyTree(root, originalTree.root);
}

template<class _ItemType>
void Tree<_ItemType>::operator=
(const Tree<_ItemType>& originalTree)
// Calls recursive function CopyTree to copy originalTree 
// into root.
{
	{
		if (&originalTree == this)
			return;             // Ignore assigning self to self
		Destroy(root);      // Deallocate existing tree nodes
		CopyTree(root, originalTree.root);
	}

}
void CopyTree(TreeNode<ItemType>*& copy,
	const TreeNode<ItemType>* originalTree)
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
}
// Function prototypes for auxiliary functions.

void PreOrder(TreeNode<ItemType>*, Que<ItemType>&);
// Enqueues tree items in preorder.


void InOrder(TreeNode<ItemType>*, Que<ItemType>&);
// Enqueues tree items in inorder.


void PostOrder(TreeNode<ItemType>*, Que<ItemType>&);
// Enqueues tree items in postorder.

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


void PreOrder(TreeNode<ItemType>* tree,
	Que<ItemType>& preQue)
	// Post: preQue contains the tree items in preorder.
{
	if (tree != NULL)
	{
		preQue.Enqueue(tree->info);
		PreOrder(tree->leftPtr, preQue);
		PreOrder(tree->rightPtr, preQue);
	}
}


void InOrder(TreeNode<ItemType>* tree,
	Que<ItemType>& inQue)
	// Post: inQue contains the tree items in inorder.
{
	if (tree != NULL)
	{
		InOrder(tree->leftPtr, inQue);
		inQue.Enqueue(tree->info);
		InOrder(tree->rightPtr, inQue);
	}
}


void PostOrder(TreeNode<ItemType>* tree,
	Que<ItemType>& postQue)
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
void Tree<_ItemType>::GetNextItem(_ItemType& item,
	OrderType order, bool& finished)
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

