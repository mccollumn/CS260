/** ---------------------------------------------
*
* @file		BinTreeTesting.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-260-02 - Assignment 5
* BinTree class test code
*
* -------------------------------------------- */

#include <string>
#include <iostream>
#include "BinTree.h"

int main() {
	std::cout << "CS260, A5-Binary Trees\n";
	std::cout << "Nick McCollum\n\n";

	BinTree<std::string> myTree;
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
	myTree.print();

	myTree.remove("Squirtle");
	std::cout << "\n\nDeleted Squirtle:\n";
	myTree.print();

	myTree.remove("Meowth");
	std::cout << "\n\nDeleted Meowth:\n";
	myTree.print();

	myTree.remove("Blastoise");
	std::cout << "\n\nDeleted Blastoise:\n";
	myTree.print();

	myTree.remove("Jynx");
	std::cout << "\n\nDeleted Jynx:\n";
	myTree.print();

	std::cout << std::endl;

	return 0;
}