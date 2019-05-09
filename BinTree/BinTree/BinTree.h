/** ---------------------------------------------
*
* @file		BinTree.h
* @author	Nick McCollum
* @version	2.0
*
* CS-260-02 - Assignment 6
* Interface and implementation for Binary Search Tree class template
*
* -------------------------------------------- */

#pragma once

template <typename Type>
struct Node {
	Type data;
	Node<Type>* left;
	Node<Type>* right;
};

template <typename Type>
class BinTree
{
public:
	/**
		Default constructor
	*/
	BinTree();

	/**
		Destructor
	*/
	~BinTree();

	/**
		Inserts a value into the tree

		@param	data	The value to insert
	*/
	void insert(Type data);

	/**
		Removes a value from the tree

		@param	data	The value to remove
		@return			True if value was removed successfully,
						false if not
	*/
	bool remove(Type data);

	/**
		Copies the binary tree

		@param		destinationTree		Pointer to the empty destination tree
		@return							True if the copy was possible,
										false if not
	*/
	bool copy(BinTree<Type>* destinationTree);

	/**
		Removes all nodes in the tree
	*/
	void removeAll();

	/**
		Processes provided function in order

		@param	function	Pointer to function
	
	*/
	void processInOrder(void(*function)(Type data, int level));

	/**
		Processes provided function post order

		@param	function	Pointer to function

	*/
	void processPostOrder(void(*function)(Type data, int level));

	/**
		Processes provided function pre order

		@param	function	Pointer to function

	*/
	void processPreOrder(void(*function)(Type data, int level));

private:
	Node<Type>* root;

	/**
		Deletes all nodes in the tree

		@param	nodePtr		Root of tree to be destroyed
	*/
	void destroy(Node<Type>* &nodePtr);

	/**
		Recursively deep copies the tree

		@param	sourceTree		Root node pointer of tree to be copied
		@param	destinationTree	Root node pointer of the destination tree
	*/
	void copy(Node<Type>* sourceTree, Node<Type>* &destinationTree);

	/**
		Removes the given node from the tree

		@param	nodePtr		The node to be removed
	*/
	void removeNode(Node<Type>* &nodePtr);

	/**
		Processes the node values in order

		@param	function	Pointer to function
		@param	nodePtr		Node of the tree to be processed
		@param	level		Used to track the level of each node
							Provide the value for root (e.g. 0)
	*/
	void processNodeInOrder(void(*function)(Type data, int level), Node<Type>* &nodePtr, int level);

	/**
		Processes the node values post order

		@param	function	Pointer to function
		@param	nodePtr		Node of the tree to be processed
		@param	level		Used to track the level of each node
							Provide the value for root (e.g. 0)
	*/
	void processNodePostOrder(void(*function)(Type data, int level), Node<Type>* &nodePtr, int level);

	/**
		Processes the node values pre order

		@param	function	Pointer to function
		@param	nodePtr		Node of the tree to be processed
		@param	level		Used to track the level of each node
							Provide the value for root (e.g. 0)
	*/
	void processNodePreOrder(void(*function)(Type data, int level), Node<Type>* &nodePtr, int level);
};

// ----------------------------------------------
template <typename Type>
BinTree<Type>::BinTree() {
	root = nullptr;
}

// ----------------------------------------------
template <typename Type>
BinTree<Type>::~BinTree() {
	destroy(root);
}

// ----------------------------------------------
template <typename Type>
void BinTree<Type>::destroy(Node<Type>* &nodePtr) {
	if (nodePtr != nullptr) {
		destroy(nodePtr->left);
		destroy(nodePtr->right);
		delete nodePtr;
		nodePtr = nullptr;
	}
}

// ----------------------------------------------
template <typename Type>
void BinTree<Type>::insert(Type data) {
	Node<Type>* newNode = new Node<Type>;
	newNode->data = data;
	newNode->left = nullptr;
	newNode->right = nullptr;

	if (root == nullptr) {
		root = newNode;
		return;
	}

	Node<Type>* current = root;
	bool done = false;
	while (!done) {
		if (data < current->data) {
			if (current->left != nullptr) {
				current = current->left;
			}
			else {
				current->left = newNode;
				done = true;
			}
		}
		else {
			if (current->right != nullptr) {
				current = current->right;
			}
			else {
				current->right = newNode;
				done = true;
			}
		}
	}
	return;
}

// ----------------------------------------------
template <typename Type>
bool BinTree<Type>::remove(Type data) {
	Node<Type>* current = root;
	Node<Type>* parent = nullptr;
	bool found = false;

	while (current != nullptr && !found) {
		if (data == current->data) {
			found = true;
		}
		else {
			parent = current;
			if (data < current->data) {
				current = current->left;
			}
			else {
				current = current->right;
			}
		}
	}

	if (found) {
		if (current == root) {
			removeNode(root);
		}
		else if (data < parent->data) {
			removeNode(parent->left);
		}
		else {
			removeNode(parent->right);
		}
		return true;
	}
	else {
		return false;
	}
}

// ----------------------------------------------
template <typename Type>
bool BinTree<Type>::copy(BinTree<Type>* destinationTree) {
	if (destinationTree->root == nullptr) {
		copy(this->root, destinationTree->root);
		return true;
	}
	return false;
}

// ----------------------------------------------
template <typename Type>
void BinTree<Type>::copy(Node<Type>* sourceTree, Node<Type>* &destinationTree) {
	if (sourceTree == nullptr) {
		destinationTree = nullptr;
	}
	else {
		destinationTree = new Node<Type>;
		destinationTree->data = sourceTree->data;
		copy(sourceTree->left, destinationTree->left);
		copy(sourceTree->right, destinationTree->right);
	}
}

// ----------------------------------------------
template <typename Type>
void BinTree<Type>::removeNode(Node<Type>* &nodePtr) {
	if (nodePtr->left == nullptr && nodePtr->right == nullptr) {
		Node<Type>* temp = nodePtr;
		nodePtr = nullptr;
		delete temp;
	}
	else if (nodePtr->right == nullptr) {
		Node<Type>* temp = nodePtr;
		nodePtr = nodePtr->left;
		delete temp;
	}
	else if (nodePtr->left == nullptr) {
		Node<Type>* temp = nodePtr;
		nodePtr = nodePtr->right;
		delete temp;
	}
	else {
		Node<Type>* current = nodePtr->left;
		Node<Type>* parent = nullptr;
		while (current->right != nullptr) {
			parent = current;
			current = current->right;
		}

		nodePtr->data = current->data;
		if (parent == nullptr) {
			nodePtr->left = current->left;
		}
		else {
			parent->right = current->left;
		}
		delete current;
	}
}

// ----------------------------------------------
template <typename Type>
void BinTree<Type>::removeAll() {
	destroy(root);
}

// ----------------------------------------------
template <typename Type>
void BinTree<Type>::processInOrder(void(*function)(Type data, int level)) {
	processNodeInOrder(function, root, 0);
}

// ----------------------------------------------
template <typename Type>
void BinTree<Type>::processPostOrder(void(*function)(Type data, int level)) {
	processNodePostOrder(function, root, 0);
}

// ----------------------------------------------
template <typename Type>
void BinTree<Type>::processPreOrder(void(*function)(Type data, int level)) {
	processNodePreOrder(function, root, 0);
}

// ----------------------------------------------
template <typename Type>
void BinTree<Type>::processNodeInOrder(void(*function)(Type data, int level), Node<Type>* &current, int level) {
	if (current != nullptr) {
		processNodeInOrder(function, current->left, level + 1);
		function(current->data, level);
		processNodeInOrder(function, current->right, level + 1);
	}
}

// ----------------------------------------------
template <typename Type>
void BinTree<Type>::processNodePostOrder(void(*function)(Type data, int level), Node<Type>* &current, int level) {
	if (current != nullptr) {
		processNodePostOrder(function, current->left, level + 1);
		processNodePostOrder(function, current->right, level + 1);
		function(current->data, level);
	}
}

// ----------------------------------------------
template <typename Type>
void BinTree<Type>::processNodePreOrder(void(*function)(Type data, int level), Node<Type>* &current, int level) {
	if (current != nullptr) {
		function(current->data, level);
		processNodePreOrder(function, current->left, level + 1);
		processNodePreOrder(function, current->right, level + 1);
	}
}