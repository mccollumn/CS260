/**
@file		StringListTest.cpp
@author		Nick McCollum
@version	1.0

CS-260-02 - Assignment 2 Doubly Linked Lists and recursion
Test code for StringList class
*/

#include <iostream>
#include "StringList.h"

int main() {
	std::cout << "Author: Nick McCollum\n\n";

	StringList myList;

	std::cout << "Insert Bob, David, Alice, Edward, Claire\n";
	myList.insert("Bob");
	myList.insert("David");
	myList.insert("Alice");
	myList.insert("Edward");
	myList.insert("Claire");

	std::cout << std::endl;
	std::cout << "List contains:\n";
	myList.printForward();
	myList.printReverse();

	std::cout << "\nInsert Bob, Edward, Claire, Claire\n";
	myList.insert("Bob");
	myList.insert("Edward");
	myList.insert("Claire");
	myList.insert("Claire");

	std::cout << std::endl;
	std::cout << "Find Alice: " << myList.find("Alice") << std::endl;
	std::cout << "Find Bob: " << myList.find("Bob") << std::endl;
	std::cout << "Find Claire: " << myList.find("Claire") << std::endl;
	std::cout << "Find Edward: " << myList.find("Edward") << std::endl;

	std::cout << std::endl;
	std::cout << "Find e: " << myList.findLetter('e') << std::endl;

	std::cout << std::endl;
	std::cout << "Removed David (" << myList.remove("David") << " items)\n";
	std::cout << "Removed Alice (" << myList.remove("Alice") << " items)\n";
	std::cout << "Removed Edward (" << myList.remove("Edward") << " items)\n";

	std::cout << std::endl;
	std::cout << "List contains:\n";
	myList.printForward();
	myList.printReverse();

	std::cout << std::endl;
	std::cout << "Remove everything and print\n";
	myList.removeAll();

	myList.printForward();
	myList.printReverse();


	//myList.printForward();
	//std::cout << "Total items: " << myList.totalItems() << std::endl;

	//std::cout << "Bob: " << myList.find("Bob") << std::endl;
	//std::cout << "Claire: " << myList.find("Claire") << std::endl;
	//std::cout << "Nobody: " << myList.find("Nobody") << std::endl;

	//std::cout << "e: " << myList.findLetter('e') << std::endl;
	//std::cout << "E: " << myList.findLetter('E') << std::endl;
	//std::cout << "c: " << myList.findLetter('c') << std::endl;

	return 0;
}