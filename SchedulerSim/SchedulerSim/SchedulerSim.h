/** ---------------------------------------------
*
* @file		SchdulerSim.h
* @author	Nick McCollum
* @version	1.0
*
* CS-260-02 - Assignment 4
* SchedulerSim class definition
* Simulates a process queue based on process priority and run time
*
* -------------------------------------------- */

#pragma once

#include "PriorityQueue.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

const int TIMESLICE = 20;

struct Process {
	int pid;
	int initialPriority;
	int currentPriority;
	int totalTime;
	int startTime;
	int remainingTime;
	int endTime;
};

class SchedulerSim
{
public:
	SchedulerSim();

	/**
		Starts the simulation.
		Simulated processes must already be instantiated.

		@return		True if the simulation completed successfully,
					false otherwise
	*/
	bool runSimulation();

	/**
		Creates processes from data in the specified file

		@param		argc		The number of command line arguments passed to main()
		@param		argv		Array of command line arguments passed to main()
		@return					True if the processes were created successfully,
								false otherwise
	*/
	bool loadProcessesFromFile(int argc, char* argv[]);

	/**
		Prints the current status of all processes

		@param		process		Process to print
	*/
	void printStatus(const Process& process);

private:
	unsigned int clock;
	PriorityQueue<Process> queue;

	/**
		Increments the clock by the specified amount

		@param		time	Number of units to add to clock
	*/
	void incrementClock(int time);

	/**
		Initializes a process' starting values

		@param		pid			PID value to assign to the process
		@param		priority	The initial priority
		@param		time		The total time needed for the process to complete
		@return					Process pointer
	*/
	Process* initProcess(int pid, int priority, int time);

	/**
		Prints the output table heading
	*/
	void printTable();

	/**
		Gets the filename provided as a command line argument

		@param		argc		The number of command line arguments passed to main()
		@param		argv		Array of command line arguments passed to main()
		@return					The specified filename,
								or a default filename if one wasn't provided
	*/
	std::string getFilename(int argc, char* argv[]);
};
