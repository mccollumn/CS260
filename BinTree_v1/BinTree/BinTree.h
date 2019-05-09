/** ---------------------------------------------
*
* @file		BinTree.h
* @author	Nick McCollum
* @version	1.0
*
* CS-260-02 - Assignment 5
* Interface and implementation for Binary Search Tree class template
*
* -------------------------------------------- */

#pragma once

#include <iostream>

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
		Copies the binary tree

		@param	sourceTree		The tree to be copied
		@param	destinationTree	The copied tree
	*/
	void copy(Node<Type>* &sourceTree, Node<Type>* destinationTree);

	/**
		Inserts a value into the tree

		@param	data	The value to insert
	*/
	void insert(Type data);

	/**
		Removes an value from the tree

		@param	data	The value to remove
		@return			True if value was removed successfully,
						false if not
	*/
	bool remove(Type data);

	/**
		Prints the values in order
	*/
	void print();
private:
	Node<Type>* root;

	/**
		Removes the given node from the tree

		@param	nodePtr		The node to be removed
	*/
	void removeNode(Node<Type>* &nodePtr);

	/**
		Deletes all nodes in the tree

		@param	nodePtr		Root of tree to be destroyed
	*/
	void destroy(Node<Type>* &nodePtr);

	/**
		Prints the node values and their level in order

		@param	nodePtr		Root of the tree to be printed
		@param	level		Used to track the level of each node
							Provide the value for root (e.g. 0)
	*/
	void inorder(Node<Type>* &nodePtr, int level) const;
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
void BinTree<Type>::copy(Node<Type>* &sourceTree, Node<Type>* destinationTree) {
	return false;
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
void BinTree<Type>::print() {
	int level = 0;
	inorder(root, level);
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
void BinTree<Type>::inorder(Node<Type>* &nodePtr, int level) const {
	if (nodePtr != nullptr) {
		inorder(nodePtr->left, level + 1);
		std::cout << nodePtr->data << "(" << level << ") ";
		inorder(nodePtr->right, level + 1);
	}
}