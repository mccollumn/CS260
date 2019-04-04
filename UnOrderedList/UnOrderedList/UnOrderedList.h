/*
@Filename:		UnOrderedList.h
@Author:		Nick McCollum
@Date:			4/4/2019
@Version:		2.0

CS-260-02 Assignment 1
Interface and implementation for UnOrderedList class
*/

#pragma once

#include <iostream>

template <typename Type>
struct Node {
	Type data;
	Node* next;
};

template <typename Type>
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
	bool prepend(Type value);

	/*
	append: Inserts the given int at the end of the list.
	@param: int - value to insert
	@return: bool - true if value inserted successfully
	*/
	bool append(Type value);

	/*
	remove: Removes the given int from the list.
	@param: int - value to remove
	@return: bool - true if value removed successfully
	*/
	bool remove(Type value);

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
	int find(Type value) const;

	/*
	removeAll: Removes all items from the list
	@param: none
	@return: none
	*/
	void removeAll();
private:
	Node<Type>* head;
};

template <typename Type>
UnOrderedList<Type>::UnOrderedList() {
	head = nullptr;
}

template <typename Type>
UnOrderedList<Type>::~UnOrderedList() {
	removeAll();
}

template <typename Type>
bool UnOrderedList<Type>::prepend(Type value) {
	if (!find(value)) {
		Node<Type>* newNode = new Node<Type>;
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

template <typename Type>
bool UnOrderedList<Type>::append(Type value) {
	if (!find(value)) {
		Node<Type>* newNode = new Node<Type>;
		newNode->data = value;
		newNode->next = nullptr;

		if (head == nullptr) {
			head = newNode;
		}
		else {
			Node<Type>* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = newNode;
		}
		return true;
	}
	return false;
}

template <typename Type>
bool UnOrderedList<Type>::remove(Type value) {
	if (head == nullptr) {
		return false;
	}
	else {
		Node<Type>* current = head;
		Node<Type>* previous = nullptr;
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

template <typename Type>
void UnOrderedList<Type>::print() const {
	Node<Type>* current = head;

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

template <typename Type>
int UnOrderedList<Type>::count() const {
	Node<Type>* current = head;

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

template <typename Type>
int UnOrderedList<Type>::find(Type value) const {
	Node<Type>* current = head;
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

template <typename Type>
void UnOrderedList<Type>::removeAll() {
	Node<Type>* current;

	while (head != nullptr) {
		current = head;
		head = head->next;
		delete current;
	}
}