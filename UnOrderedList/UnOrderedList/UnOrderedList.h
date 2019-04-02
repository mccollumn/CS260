/*
@Filename:		UnOrderedList.h
@Author:		Nick McCollum
@Date:			4/2/2019
@Version:		1.0

CS-260-02 Assignment 1
Interface and implementation for UnOrderedList class
*/

#pragma once

#include <iostream>

struct Node {
	int data;
	Node* next;
};

class UnOrderedList
{
public:
	UnOrderedList();
	~UnOrderedList();

	/*
	prepend: Inserts the given int at the beginning of the list.
	@param: int - value to insert
	@return: bool - true if value inserted successfully
	*/
	bool prepend(int value);

	/*
	append: Inserts the given int at the end of the list.
	@param: int - value to insert
	@return: bool - true if value inserted successfully
	*/
	bool append(int value);

	/*
	remove: Removes the given int from the list.
	@param: int - value to remove
	@return: bool - true if value removed successfully
	*/
	bool remove(int value);

	/*
	print: Prints the items in the list
	@param: none
	@return: none
	*/
	void print() const;

	/*
	count: Returns a count of the number of items in the list.
	@param: none
	@return: int - number of list items
	*/
	int count() const;

	/*
	find: Returns the given int’s position in the list.  Returns 0 if the int is not in the list.
	@param: int - value to search for
	@return: int - position of value in the list
	*/
	int find(int value) const;

	/*
	removeAll: Removes all items from the list
	@param: none
	@return: none
	*/
	void removeAll();
private:
	Node* head;
};

UnOrderedList::UnOrderedList() {
	head = nullptr;
}

UnOrderedList::~UnOrderedList() {
	removeAll();
}

bool UnOrderedList::prepend(int value) {
	if (!find(value)) {
		Node* newNode = new Node;
		newNode->data = value;
		newNode->next = nullptr;

		if (head == nullptr) {
			head = newNode;
		}
		else {
			newNode->next = head;
			head = newNode;
		}
		return true;
	}
	return false;
}

bool UnOrderedList::append(int value) {
	if (!find(value)) {
		Node* newNode = new Node;
		newNode->data = value;
		newNode->next = nullptr;

		if (head == nullptr) {
			head = newNode;
		}
		else {
			Node* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = newNode;
		}
		return true;
	}
	return false;
}

bool UnOrderedList::remove(int value) {
	if (head == nullptr) {
		return false;
	}
	else {
		Node* current = head;
		Node* previous = nullptr;
		while (current != nullptr) {
			if (current->data == value) {
				if (head == current) {
					head = head->next;
					delete current;
				}
				else {
					previous->next = current->next;
					delete current;
				}
				return true;
			}
			else {
				previous = current;
				current = current->next;
			}
		}
		return false;
	}
}

void UnOrderedList::print() const {
	Node* current = head;

	std::cout << "The list contains the following " << count() << " elements:" << std::endl;
	while (current != nullptr) {
		std::cout << current->data;
		if (current->next != nullptr) {
			std::cout << ", ";
		}
		else {
			std::cout << std::endl;
		}
		current = current->next;
	}
}

int UnOrderedList::count() const {
	Node* current = head;

	if (current == nullptr) {
		return 0;
	}
	else {
		int count = 0;
		while (current != nullptr) {
			current = current->next;
			count++;
		}
		return count;
	}
}

int UnOrderedList::find(int value) const {
	Node* current = head;
	int position = 0;

	while (current != nullptr) {
		position++;
		if (current->data == value) {
			return position;
		}
		else {
			current = current->next;
		}
	}
	return 0;
}

void UnOrderedList::removeAll() {
	Node* current;

	while (head != nullptr) {
		current = head;
		head = head->next;
		delete current;
	}
}