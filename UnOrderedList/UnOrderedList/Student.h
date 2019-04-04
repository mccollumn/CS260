/*
@Filename:		Student.h
@Author:		Nick McCollum
@Date:			4/4/2019
@Version:		1.0

CS-260-02 Assignment 1
Interface and implementation for Student class
*/

#pragma once

#include <string>

using namespace std;

class Student {
public:
	//constructor
	Student(const string name = "anonymous", char letterGrade = 'W');

	/*
	setName: Sets the student name.
	@param: string - student name
	@return: none
	*/
	void setName(string name);

	/*
	setGrade: Sets the student letter grade.
	@param: char - student leter grade
	@return: none
	*/
	void setGrade(char letterGrade);

	/*
	getName: Returns the student name.
	@param: none
	@return: string - student name
	*/
	string getName() const;

	/*
	getGrade: Returns the student letter grade.
	@param: none
	@return: chare - student letter grade
	*/
	char getGrade() const;

	//operator overloads
	friend bool operator== (const Student& stu1, const Student& stu2);
	friend ostream& operator<< (ostream& stream, const Student& student);
private:
	string name;
	char letterGrade;
};

//operator overloads (provided because they aren’t covered in detail until CS202)
bool operator== (const Student& stu1, const Student& stu2)
{
	if (stu1.name == stu2.name && stu1.letterGrade == stu2.letterGrade)
		return true;
	else
		return false;
}
ostream& operator<< (ostream& stream, const Student& student)
{
	stream << student.name;
	stream << " (" << student.letterGrade << ") ";
	return stream;
}

Student::Student(const string name, char letterGrade) {
	this->name = name;
	this->letterGrade = letterGrade;
}

void Student::setName(string name) {
	this->name = name;
}

void Student::setGrade(char letterGrade) {
	this->letterGrade = letterGrade;
}

string Student::getName() const {
	return name;
}

char Student::getGrade() const {
	return letterGrade;
}