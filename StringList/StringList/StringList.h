/**
@file		StringList.h
@author		Nick McCollum
@version	1.0

CS-260-02 - Assignment 2 Doubly Linked Lists and recursion
Interface for StringList class
*/

#pragma once

#include <string>

struct Node {
	std::string data;
	Node* next;
	Node* previous;
};

class StringList
{
public:
	StringList();
	~StringList();

	/**
	Inserts the given string in alphabetical order in the list
	@param string Value to insert
	@return none
	*/
	void insert(std::string value);

	/**
	Removes all occurrences of the given string from the list
	@param string Value to remove
	@return int Number of items removed
	*/
	int remove(std::string value);

	/**
	Returns a count of the number of items in the list
	@param none
	@return int Number of items in list
	*/
	int totalItems();

	/**
	Removes all items from the list
	@param none
	@return none
	*/
	void removeAll();

	/**
	Prints the list of strings
	@param none
	@return none
	*/
	void printForward();

	/**
	Prints the list of strings in reverse
	@param none
	@return none
	*/
	void printReverse();

	/**
	Counts how many times the given string occurs in the list 
	@param string Value to find
	@return int Number of times found
	*/
	int find(std::string value);

	/**
	Counts how many times the given letter occurs in the list
	@param char Character to find
	@return int Number of times found
	*/
	int findLetter(char character);

private:
	Node* head;
	Node* tail;

	int find(std::string value, Node* node);
	int findLetter(char character, Node* node);
};

