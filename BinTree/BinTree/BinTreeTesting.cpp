/** ---------------------------------------------
*
* @file		BinTreeTesting.cpp
* @author	Nick McCollum
* @version	2.0
*
* CS-260-02 - Assignment 6
* BinTree class test code
*
* -------------------------------------------- */

#include <string>
#include <iostream>
#include "BinTree.h"

template <typename Type>
void print(Type data, int level);

int main() {
	std::cout << "CS260, A6-Binary Trees\n";
	std::cout << "Nick McCollum\n\n";

	// Create a binary search tree of strings
	BinTree<std::string> myTree;

	// Insert names
	myTree.insert("Jynx");
	myTree.insert("Charmander");
	myTree.insert("Snorlax");
	myTree.insert("Diglett");
	myTree.insert("Kakuna");
	myTree.insert("Meowth");
	myTree.insert("Pikachu");
	myTree.insert("Blastoise");
	myTree.insert("Squirtle");
	myTree.insert("Ivysaur");
	myTree.insert("Bulbasaur");
	myTree.insert("Abra");

	// Print the tree
	myTree.processInOrder(print);

	// Make a deep copy of the tree
	BinTree<std::string>* newTree = new BinTree<std::string>;
	myTree.copy(newTree);

	// Delete Squirtle and print tree
	myTree.remove("Squirtle");
	std::cout << "\n\nDeleted Squirtle:\n";
	myTree.processInOrder(print);

	// Delete Meowth and print tree
	myTree.remove("Meowth");
	std::cout << "\n\nDeleted Meowth:\n";
	myTree.processInOrder(print);

	// Delete Blastoise and print tree
	myTree.remove("Blastoise");
	std::cout << "\n\nDeleted Blastoise:\n";
	myTree.processInOrder(print);

	// Delete Jynx and print tree
	myTree.remove("Jynx");
	std::cout << "\n\nDeleted Jynx:\n";
	myTree.processInOrder(print);

	// Print copy of the tree inOrder
	std::cout << "\n\nPrint copy inOrder:\n";
	newTree->processInOrder(print);

	// Print copy of the tree postOrder
	std::cout << "\n\nPrint copy postOrder:\n";
	newTree->processPostOrder(print);

	// Print copy of the tree preOrder
	std::cout << "\n\nPrint copy preOrder:\n";
	newTree->processPreOrder(print);

	// Remove all nodes in the copy
	newTree->removeAll();

	// Reprint the copy (should print nothing)
	std::cout << "\n\nPrint copy after removing all nodes:\n";
	newTree->processPreOrder(print);

	return 0;
}

template <typename Type>
void print(Type data, int level) {
	std::cout << data << "(" << level << ") ";
}