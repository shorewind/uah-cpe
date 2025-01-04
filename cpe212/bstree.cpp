//
// bstree.cpp  2023 Spring CPE 212 - Project05 - Binary Search Tree
//
#include <iostream>
#include <new>
#include "bstree.h"

// Private helper functions
template <typename SomeType>
void BSTree<SomeType>::Delete(BSTreeNode<SomeType>*& treePtr, SomeType& item)
{
  // Recursive function that traverses the tree starting at treePtr to locate the data value to be removed
  // Once located, DeleteNode is invoked to remove the value from the tree
  // If tree is not empty and item is NOT present, throw NotFoundBSTree	
	if (treePtr == NULL)
	{
		throw NotFoundBSTree();
	}
	
	if (item < treePtr->data)
	{
		Delete(treePtr->leftPtr, item);
	}
	else if (item > treePtr->data)
	{
		Delete(treePtr->rightPtr, item);
	}
	else
	{
		item = treePtr->data;
		DeleteNode(treePtr);
	}
}

template <typename SomeType>
void BSTree<SomeType>::DeleteNode(BSTreeNode<SomeType>*& treePtr)
{
  // Removes the node pointed to by treePtr from the tree
  // Calls GetPredecessor and Delete
	SomeType item;
	BSTreeNode<SomeType>* tempPtr;
	
	tempPtr = treePtr;
	if (treePtr->leftPtr == NULL)
	{
		treePtr = treePtr->rightPtr;
		delete tempPtr;
	}
	else if (treePtr->rightPtr == NULL)
	{
		treePtr = treePtr->leftPtr;
		delete tempPtr;
	}
	else
	{
		item = GetPredecessor(treePtr->leftPtr);
		treePtr->data = item;
		Delete(treePtr->leftPtr, item);
	}
}

template <typename SomeType>
void BSTree<SomeType>::Insert(BSTreeNode<SomeType>*& ptr, SomeType item)
{
  // Recursive function that finds the correct position of item and adds it to the tree
  // Throws FoundInBSTree if item is already in the tree	
	if (ptr == NULL)
	{
		ptr = new BSTreeNode<SomeType>;
		ptr->data = item;
		ptr->leftPtr = NULL;
		ptr->rightPtr = NULL;
	}
	else if (item < ptr-> data)
	{
		Insert(ptr->leftPtr, item);	
	}
	else if (item > ptr-> data)
	{
		Insert(ptr->rightPtr, item);
	}
	else
	{
		throw FoundInBSTree();
	}
}

template <typename SomeType>
void BSTree<SomeType>::Destroy(BSTreeNode<SomeType>*& ptr)
{
  // Recursively deallocates every node in the tree pointed to by ptr
	if (ptr != NULL)
	{
		Destroy(ptr->leftPtr);
		Destroy(ptr->rightPtr);
		delete ptr;
	}
}

template <typename SomeType>
void BSTree<SomeType>::CopyTree(BSTreeNode<SomeType>*& copy, const BSTreeNode<SomeType>* originalTree)
{
  // Recursively copies all data from original tree into copy
	if (originalTree == NULL)
	{
		copy = NULL;
	}
	else
	{
		copy = new BSTreeNode<SomeType>;
		copy->data = originalTree->data;
		CopyTree(copy->leftPtr, originalTree->leftPtr);
		CopyTree(copy->rightPtr, originalTree->rightPtr);
	}
}

template <typename SomeType>
SomeType BSTree<SomeType>::GetPredecessor(BSTreeNode<SomeType>* treePtr) const
{
  // Finds the largest data value in the tree pointed to by treePtr and returns that data value as the functions return value
	while (treePtr->rightPtr != NULL)
	{
		treePtr = treePtr->rightPtr;
	}
	return (treePtr->data);
}

template <typename SomeType>
int BSTree<SomeType>::CountNodes(BSTreeNode<SomeType>* treePtr) const
{
  // Recursive function that counts every node in the tree pointed to by treePtr and returns the count as the function return value
	if (treePtr == NULL)
	{
		return 0;
	}
	else
	{
		return (1 + CountNodes(treePtr->leftPtr) + CountNodes(treePtr->rightPtr));
	}
}

template <typename SomeType>
int BSTree<SomeType>::LevelCount(BSTreeNode<SomeType>* treePtr) const
{
  // Recursive function that traverses the entire tree to determine the total number of levels in the tree
	if (treePtr == NULL)
	{
		return 0;
	}
	else
	{
		int leftLevels = LevelCount(treePtr->leftPtr);
		int rightLevels = LevelCount(treePtr->rightPtr);

		if (leftLevels > rightLevels)
		{
			return (1 + leftLevels);
		}
		else
		{
			return (1 + rightLevels);
		}	
	}
}

template <typename SomeType>
int BSTree<SomeType>::FindLevel(BSTreeNode<SomeType>* treePtr, SomeType item) const
{
  // Recursive function that traverses the tree looking for item and returns the level where item was found
	if (!treePtr)
	{
		throw NotFoundBSTree();
	}
	
	if (item < treePtr->data)
	{
		return (FindLevel(treePtr->leftPtr, item) + 1);
	}
	else if (item > treePtr->data)
	{
		return (FindLevel(treePtr->rightPtr, item) + 1);
	}
	else
	{
		return 0;
	}
}

// Public interface functions
template <typename SomeType>
BSTree<SomeType>::BSTree()
{
  // Default constructor initializes root pointer to NULL
	rootPtr = NULL;
}

template <typename SomeType>
BSTree<SomeType>::BSTree(const BSTree<SomeType>& someTree)
{
  // Copy constructor for BSTree
  // Calls CopyTree
	CopyTree(rootPtr, someTree.rootPtr);
}

template <typename SomeType>
void BSTree<SomeType>::operator=(const BSTree<SomeType>& originalTree)
{
  // Overloaded assignment operator for BSTree
  // Calls CopyTree
	if (&originalTree == this)
	{
		return;
	}
	
	Destroy(rootPtr);
	CopyTree(rootPtr, originalTree.rootPtr);
}

template <typename SomeType>
BSTree<SomeType>::~BSTree()
{
  // Destructor deallocates all tree nodes
  // Calls the private helper function Destroy
	Destroy(rootPtr);
}

template <typename SomeType>
void BSTree<SomeType>::InsertItem(SomeType item)
{
  // Inserts item into BSTree;  if tree already full, throws FullBSTree exception
  // If item is already in BSTree, throw FoundInBSTree exception
  // Calls the private helper function Insert
	if (IsFull())
	{
		throw FullBSTree();
	}
	Insert(rootPtr, item);
}

template <typename SomeType>
SomeType BSTree<SomeType>::DeleteItem(SomeType item)
{
  // Deletes item from BSTree if item is present AND returns object via function return value
  // If tree is empty, throw the EmptyBSTree exception
  // If tree is not empty and item is NOT present, throw NotFoundBSTree
  // Calls the private helper function Delete
	if (IsEmpty())
	{
		throw EmptyBSTree();
	}
	Delete(rootPtr, item);
	return item;
}

template <typename SomeType>
void BSTree<SomeType>::MakeEmpty()
{
  // Deallocates all BSTree nodes and sets root pointer to NULL
  // Calls the private helper function Destroy
	Destroy(rootPtr);
	rootPtr = NULL;
}

template <typename SomeType>
int BSTree<SomeType>::Size() const
{
  // Returns total number of data values stored in tree
	return CountNodes(rootPtr);
}

template <typename SomeType>
bool BSTree<SomeType>::IsFull() const
{
  // Returns true if BSTree is full; returns false otherwise
	BSTreeNode<SomeType>* item;
	try
	{
		item = new BSTreeNode<SomeType>;
		delete item;
		return false;
	}
	catch (bad_alloc)
	{
		return true;
	}
}

template <typename SomeType>
bool BSTree<SomeType>::IsEmpty() const
{
  // Returns true if BSTree is empty; returns false otherwise
	return (rootPtr == NULL);
}

template <typename SomeType>
SomeType BSTree<SomeType>::Min() const
{
  // Returns minimum value in tree; throws EmptyBSTree if tree is empty
	if (IsEmpty())
	{
		throw EmptyBSTree();
	}
	
	BSTreeNode<SomeType>* current = rootPtr;
	
	while (current->leftPtr != NULL)
	{
		current = current->leftPtr;
	}
	return (current->data);
}

template <typename SomeType>
SomeType BSTree<SomeType>::Max() const
{
  // Returns maximum value in tree; throws EmptyBSTree if tree is empty
	if (IsEmpty())
	{
		throw EmptyBSTree();
	}
	
	BSTreeNode<SomeType>* current = rootPtr;
	
	while (current->rightPtr != NULL)
	{
		current = current->rightPtr;
	}
	return (current->data);
}

template <typename SomeType>
int BSTree<SomeType>::TotalLevels() const
{
  // Returns the maximum level value for current tree contents
  // Levels are numbered 0, 1, ..., N-1.  This function returns N
  // Throws EmptyBSTree if empty
  // Calls the private helper function LevelCount
	if (IsEmpty())
	{
		throw EmptyBSTree();
	}
	
	return LevelCount(rootPtr);
}

template <typename SomeType>
int BSTree<SomeType>::Level(SomeType item) const
{
  // Returns the level within the BSTree at which the value item is found
  // If tree is empty, throws EmptyBSTree
  // If tree is not empty and item is not found, throws NotFoundBSTree
  // Calls the private helper funtion FindLevel
	if (IsEmpty())
	{
		throw EmptyBSTree();
	}

	return FindLevel(rootPtr, item);
}
