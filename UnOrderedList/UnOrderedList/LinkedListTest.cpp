/*
@Filename:		LinkedListTest.cpp
@Author:		Nick McCollum
@Date:			4/2/2019
@Version:		1.0

CS-260-02 Assignment 1
Test code for UnOrderedList class
*/

#include "UnOrderedList.h"
#include <iostream>

using namespace std;

int main() {
	// test template with ints --------------------------------
	UnOrderedList intList;
	intList.prepend(10);
	intList.prepend(20);
	intList.prepend(5);
	intList.append(15);
	intList.append(25);
	intList.print();

	cout << "5 is in position " << intList.find(5) << endl;
	cout << "15 is in position " << intList.find(15) << endl;
	cout << "20 is in position " << intList.find(20) << endl;
	cout << "8 is in position " << intList.find(8) << endl;

	intList.remove(15);
	intList.remove(5);
	intList.remove(25);
	intList.print();

	intList.removeAll();
	intList.print();
	cout << endl << endl;

	return 1;
}
