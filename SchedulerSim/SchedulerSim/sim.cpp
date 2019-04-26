/** ---------------------------------------------
*
* @file		sim.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-260-02 - Assignment 4
* Main function that kicks off the simulation
*
* -------------------------------------------- */

#include "SchedulerSim.h"

int main(int argc, char* argv[]) {

	std::cout << "Author: Nick McCollum\n\n";

	SchedulerSim mySim;
	if (mySim.loadProcessesFromFile(argc, argv)) {
		mySim.runSimulation();
	}
	

	// Priority Queue test code
	/*
	PriorityQueue<int> myQueue;
	myQueue.enqueue(1);
	myQueue.enqueue(2, 3);
	myQueue.enqueue(3, 2);
	myQueue.enqueue(4, 1);
	myQueue.enqueue(5, 0);
	myQueue.enqueue(6, 0);
	myQueue.enqueue(7, 4);

	int num;
	while (myQueue.dequeue(num)) {
		std::cout << num << ' ';
	}
	// Should output 5 6 4 3 2 1 7
	*/

	return 0;
}