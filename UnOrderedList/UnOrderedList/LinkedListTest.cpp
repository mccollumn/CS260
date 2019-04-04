/*
@Filename:		LinkedListTest.cpp
@Author:		Nick McCollum
@Date:			4/4/2019
@Version:		2.0

CS-260-02 Assignment 1
Test code for UnOrderedList class
*/

#include "UnOrderedList.h"
#include "Student.h"
#include <iostream>

using namespace std;

int main() {
	// test template with ints --------------------------------
	UnOrderedList<int> intList;
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

	// test on list of chars --------------------------------
	UnOrderedList<char>* charList = new UnOrderedList<char>;
	charList->append('k');
	charList->append('s');
	charList->prepend('r');
	charList->prepend('o');
	charList->prepend('w');
	charList->print();

	charList->remove('r');
	charList->remove('w');
	charList->remove('s');
	charList->print();

	charList->removeAll();
	charList->print();
	delete charList;
	cout << endl << endl;

	// test it on Students ------------------------------------
	Student student1("Charles", 'A');
	Student student2("Marie", 'B');
	Student student3("Albert", 'C');
	Student student4("Thomas", 'D');
	Student student5("Nikola", 'F');

	UnOrderedList<Student> studentList;
	studentList.append(student1);
	studentList.append(student2);
	studentList.prepend(student3);
	studentList.prepend(student4);
	studentList.prepend(student5);
	studentList.print();

	cout << student1.getName() << " is in position " << studentList.find(student1) << endl;
	cout << student5.getName() << " is in position " << studentList.find(student5) << endl;

	studentList.remove(student2);
	studentList.remove(student3);
	studentList.remove(student4);
	studentList.print();

	studentList.removeAll();
	studentList.print();

	return 1;
}
