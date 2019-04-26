/** ---------------------------------------------
*
* @file		PriorityQueue.h
* @author	Nick McCollum
* @version	1.0
*
* CS-260-02 - Assignment 4
* PriorityQueue class template
* Creates a queue in which items are removed based on priority
*
* -------------------------------------------- */

#pragma once

#include <queue>

const int PRIORITY_LEVELS = 5;	// 0 (high) - 4 (low)

template <typename Type>
class PriorityQueue
{
public:
	/**
		Enqueues an item at the provided priority

		@param		item		The item to add to the queue
		@param		priority	The priority of the item
								Lowest priority if not specified
		@return					True if the item was enqueued successfully,
								false if not
	*/
	bool enqueue(Type item, int priority = PRIORITY_LEVELS - 1);

	/**
		Returns and removes the highest priority item in the queue

		@param		item		The item that was dequeued
		@return					True if the item was dequeued successfully,
								false if not
	*/
	bool dequeue(Type& item);

private:
	std::queue<Type> queues[PRIORITY_LEVELS];

	/**
		Determines if a queue contains any items

		@param		priority	The queue to check
		@return					True if the specified queue is empty,
								false if not
	*/
	bool isEmpty(int priority);

	/**
		Determines if a queue is already full

		@param		priority	The queue to check
		@return					True if the specified queue is full,
								false if not
	*/
	bool isFull(int priority);
};

// ----------------------------------------------
template <typename Type>
bool PriorityQueue<Type>::enqueue(Type item, int priority) {
	if (!isFull(priority)) {
		queues[priority].push(item);
		return true;
	}
	return false;
}

// ----------------------------------------------
template <typename Type>
bool PriorityQueue<Type>::dequeue(Type& item) {
	for (int q = 0; q < PRIORITY_LEVELS; q++) {
		if (!isEmpty(q)) {
			item = queues[q].front();
			queues[q].pop();
			return true;
		}
	}
	return false;
}

// ----------------------------------------------
template <typename Type>
bool PriorityQueue<Type>::isEmpty(int priority) {
	return queues[priority].empty();
}

// ----------------------------------------------
template <typename Type>
bool PriorityQueue<Type>::isFull(int priority) {
	// Queues cannot be full with current implementation
	return false;
}