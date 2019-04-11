/**
@file		StringList.cpp
@author		Nick McCollum
@version	1.0

CS-260-02 - Assignment 2 Doubly Linked Lists and recursion
Implementation for StringList class
*/

#include <iostream>
#include "StringList.h"

// ----------------------------------------------
StringList::StringList() {
	head = nullptr;
	tail = nullptr;
}

// ----------------------------------------------
StringList::~StringList() {
	removeAll();
}

// ----------------------------------------------
void StringList::insert(std::string value) {
	Node* newNode = new Node;
	newNode->data = value;
	newNode->next = nullptr;
	newNode->previous = nullptr;

	// Empty list
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
		return;
	}

	// Insert at beginning
	if (newNode->data <= head->data) {
		head->previous = newNode;
		newNode->next = head;
		head = newNode;
		return;
	}
	// Insert at end
	if (newNode->data >= tail->data) {
		newNode->previous = tail;
		tail->next = newNode;
		tail = newNode;
		return;
	}

	// Insert in the middle
	Node* current = head;
	while (newNode->data > current->data) {
		current = current->next;
	}
	newNode->next = current;
	newNode->previous = current->previous;
	newNode->next->previous = newNode;
	newNode->previous->next = newNode;
}

// ----------------------------------------------
int StringList::remove(std::string value) {
	// Empty list
	if (head == nullptr) {
		return 0;
	}

	int count = 0;
	Node* current = head;
	while (current != nullptr) {
		if (current->data == value) {
			// Remove from beginning
			if (current == head) {
				Node* temp = head;
				head = head->next;
				head->previous = nullptr;
				current = current->next;
				delete temp;
				count++;
			}
			// Remove from end
			else if (current == tail) {
				Node* temp = tail;
				tail = tail->previous;
				tail->next = nullptr;
				current = current->next;
				delete temp;
				count++;
			}
			// Remove from the middle
			else {
				Node* temp = current;
				current->next->previous = current->previous;
				current->previous->next = current->next;
				current = current->next;
				delete temp;
				count++;
			}
		}
		else {
			current = current->next;
		}		
	}
	return count;
}

// ----------------------------------------------
int StringList::totalItems() {
	int total = 0;
	Node* current = head;

	while (current != nullptr) {
		total++;
		current = current->next;
	}
	return total;
}

// ----------------------------------------------
void StringList::removeAll() {
	Node* current;
	while (head != nullptr) {
		current = head;
		head = head->next;
		delete current;
	}
	tail = nullptr;
}

// ----------------------------------------------
void StringList::printForward() {
	Node* current = head;
	while (current != nullptr) {
		std::cout << current->data;
		if (current->next == nullptr) {
			std::cout << std::endl;
		}
		else {
			std::cout << ", ";
		}
		current = current->next;
	}
}

// ----------------------------------------------
void StringList::printReverse() {
	Node* current = tail;
	while (current != nullptr) {
		std::cout << current->data;
		if (current->previous == nullptr) {
			std::cout << std::endl;
		}
		else {
			std::cout << ", ";
		}
		current = current->previous;
	}
}

// ----------------------------------------------
int StringList::find(std::string value) {
	return find(value, head);
}

// ----------------------------------------------
int StringList::find(std::string value, Node* node) {
	Node* current = node;
	if (current == nullptr) {
		return 0;
	}
	if (current->data == value) {
		return 1 + find(value, node->next);
	}
	else {
		return find(value, node->next);
	}
}

// ----------------------------------------------
int StringList::findLetter(char character) {
	return findLetter(character, head);
}

// ----------------------------------------------
int StringList::findLetter(char character, Node* node) {
	Node* current = node;
	if (current == nullptr) {
		return 0;
	}
	int matches = 0;
	for (int x = 0; x < current->data.length(); x++) {
		if (tolower(current->data[x]) == tolower(character)) {
			matches++;
		}
	}
	return matches + findLetter(character, current->next);
}
