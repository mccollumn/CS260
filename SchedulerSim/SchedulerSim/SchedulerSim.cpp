/** ---------------------------------------------
*
* @file		SchdulerSim.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-260-02 - Assignment 4
* SchedulerSim class implementation
* Simulates a process queue based on process priority and run time
*
* -------------------------------------------- */

#include "SchedulerSim.h"

// ----------------------------------------------
SchedulerSim::SchedulerSim() {
	clock = 0;
}

// ----------------------------------------------
bool SchedulerSim::runSimulation() {
	Process* process = new Process;;
	printTable();
	while (queue.dequeue(*process)) {
		if (process->remainingTime > TIMESLICE) {
			process->remainingTime -= TIMESLICE;
			incrementClock(TIMESLICE);
			if (process->currentPriority < PRIORITY_LEVELS - 1) {
				process->currentPriority++;
			}
			queue.enqueue(*process, process->currentPriority);
		}
		else {
			incrementClock(process->remainingTime);
			process->endTime = clock;
			printStatus(*process);
		}
	}
	delete process;
	return true;
}

// ----------------------------------------------
bool SchedulerSim::loadProcessesFromFile(int argc, char* argv[]) {
	std::string filename = getFilename(argc, argv);
	std::ifstream inputStream;
	inputStream.open(filename);
	if (!inputStream) {
		std::cerr << "Error: Could not open file:\n";
		std::cerr << filename << std::endl;
		return false;
	}
	std::cout << std::endl << "Input file:\n";
	std::cout << filename << std::endl;

	int priority;
	int time;
	int pidCount = 0;
	while (inputStream >> priority >> time) {
		Process* process = initProcess(++pidCount, priority, time);
		queue.enqueue(*process, priority);
		delete process;
	}
	return true;
}

// ----------------------------------------------
void SchedulerSim::printTable() {
	std::cout << std::endl;
	std::cout << std::setw(13) << "Initial " << std::setw(8) << "Time " << std::setw(9) << "Time  " << std::setw(7) << "Time " << std::setw(10) << "Final  " << std::endl;
	std::cout << "PID" << std::setw(10) << "Priority" << std::setw(8) << "Needed" << std::setw(9) << "Started" << std::setw(7) << "Ended" << std::setw(10) << "Priority" << std::endl;
	std::cout << std::setw(47) << std::setfill('-') << "-" << std::endl;
	std::cout << std::setfill(' ');
}

// ----------------------------------------------
void SchedulerSim::printStatus(const Process& process) {
	std::cout << std::setw(2) << process.pid;
	std::cout << std::setw(7) << process.initialPriority;
	std::cout << std::setw(11) << process.totalTime;
	std::cout << std::setw(7) << process.startTime;
	std::cout << std::setw(9) << process.endTime;
	std::cout << std::setw(8) << process.currentPriority << std::endl;
}

// ----------------------------------------------
void SchedulerSim::incrementClock(int time) {
	clock += time;
}

// ----------------------------------------------
Process* SchedulerSim::initProcess(int pid, int priority, int time) {
	Process* process = new Process;
	process->pid = pid;
	process->initialPriority = priority;
	process->currentPriority = priority;
	process->totalTime = time;
	process->startTime = 0;
	process->remainingTime = time;
	process->endTime = 0;
	return process;
}

// ----------------------------------------------
std::string SchedulerSim::getFilename(int argc, char* argv[]) {
	std::string filename;
	if (argc == 1) {
		std::cerr << "No data filename provided. Using the default (sim.txt).\n";
		filename = "sim.txt";
	}
	else {
		filename = argv[1];
	}
	return filename;
}