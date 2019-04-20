/** ---------------------------------------------
*
* @file		Postfix.h
* @author	Nick McCollum
* @version	1.0
*
* CS-260-02 - Assignment 3
* Interface for Postfix class
*
* -------------------------------------------- */

#pragma once

#include <string>
#include <stack>
#include <list>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <regex>

struct Operators {
	char op;
	int prec;
};

const int NUM_OPERATORS = 6;
const Operators OPERATORS[] = { {'*', 3}, {'/', 3}, {'+', 2}, {'-', 2}, {'(', 1}, {')', 0} };

class Postfix
{
public:
	/**
		Default constructor
	*/
	Postfix();

	/**
		Constructor that sets the expression when instantiated

		@param	exp	The expression to be converted to postfix
	*/
	//Postfix(std::string exp);

	/**
		Sets the expression to be converted to postfix

		@param	exp	A string representing the expression to be converted
	*/
	void setExp(std::string exp);

	/**
		Returns a copy the expression to be converted to postfix

		@return		The expression to be converted
	*/
	std::string getExp();

	/**
		Returns the infix expression

		@return		The infix expression if the original expression has been converted.
					Otherwise returns empty string.
	*/
	std::string getInfixExp();

	/**
		Returns the postfix expression

		@return		The postfix expression if the infix has been converted.
					Otherwise returns empty string.
	*/
	std::string getPostfixExp();

	/**
		Prints the provided expression to stdout

		@param	exp	The expression to print
	*/
	void print(std::string exp);

	/**
		Prints the provided string to stderr

		@param	error	The error message to print
	*/
	void printError(std::string error = "");

	/**
		Validates the provided expression and converts it to infix

		@return		True is the conversion was successful, false if not
	*/
	bool convertToInfix();

	/**
		Converts the infix expression to postfix

		@return		True is the conversion was successful, false if not
	*/
	bool convertToPostfix();

	/**
		Evaluates the postfix expression and provides the result

		@param	result	The result of the evaluated expression
		@return			True is the evaluation was successful, false if not
	*/
	bool evalPostfix(int& result);

	void parseToList(std::string exp, std::list<std::string>& list);
private:
	std::string exp;
	std::string infixExp;
	std::string postfixExp;
	std::stack<char> operatorStack;
	std::stack<int> operandStack;
	std::list<std::string> infixExpLst;
	std::list<std::string> postfixExpLst;

	/**
		Checks that the expression only contains valid characters

		@param	exp	The expression to be validated
		@return		True if the expression is valid, false otherwise
	*/
	bool validate(std::string exp);

	/**
		Removes all whitespace characters from a string

		@param	infixExp	The expression that contains whitespace
		@return				The expression with whitespace removed
	*/
	std::string stripWhitespace(std::string infixExp);

	/**
		Determines if the provided character is a valid operator

		@param	op	The operator to check
		@return		True if valid operator, false if not
	*/
	bool isOperator(char op);

	/**
		Determines the precedence of an operator

		@param	op	The operator to check
		@return		An integer representing the precedence relative to the other operators.
					Possible values are 0 - 3.
	*/
	int getPrecedence(char op);

	/**
		Evalutates a simple binomial expression

		@param	op			The operator
		@param	operand1	The first operand to be used in the expression
		@param	operand2	The second operand to be used in the expression
		@return				Result after evaluating the expression
	*/
	int evaluate(char op, int operand1, int operand2);

	
};

/** ---------------------------------------------
*
* @file		Postfix.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-260-02 - Assignment 3
* Implementation of Postfix class
*
* -------------------------------------------- */

//#include "Postfix.h"

// ----------------------------------------------
Postfix::Postfix() {
	exp = "";
	infixExp = "";
	postfixExp = "";
}

// ----------------------------------------------
//Postfix::Postfix(std::string exp = "") {
//	this->exp = exp;
//	infixExp = "";
//	postfixExp = "";
//}

// ----------------------------------------------
void Postfix::setExp(std::string exp) {
	this->exp = exp;
}

// ----------------------------------------------
std::string Postfix::getExp() {
	return exp;
}

// ----------------------------------------------
std::string Postfix::getInfixExp() {
	return infixExp;
}

// ----------------------------------------------
std::string Postfix::getPostfixExp() {
	return postfixExp;
}

// ----------------------------------------------
void Postfix::print(std::string exp) {
	std::cout << exp << std::endl;
}

// ----------------------------------------------
void Postfix::printError(std::string error) {
	if (error != "") {
		std::cerr << error << std::endl;
	}
	else {
		std::cerr << "Error!\n";
	}
}

// ----------------------------------------------
bool Postfix::convertToInfix() {
	std::string infixExpClean = stripWhitespace(exp);
	if (validate(infixExpClean)) {
		infixExp = infixExpClean;
		return true;
	}
	return false;
}

// ----------------------------------------------
bool Postfix::convertToPostfix() {
	std::string infixExpClean = stripWhitespace(infixExp);
	int strLength = infixExpClean.length();
	char token;

	for (int c = 0; c < strLength; c++) {
		token = infixExpClean[c];
		if (isdigit(token)) {
			postfixExp += token;
		}
		else if (token == '(') {
			operatorStack.push(token);
		}
		else if (token == ')') {
			char topToken = operatorStack.top();
			operatorStack.pop();
			while (topToken != '(') {
				postfixExp += topToken;
				topToken = operatorStack.top();
				operatorStack.pop();
			}
		}
		else {
			while (!operatorStack.empty() && getPrecedence(operatorStack.top()) >= getPrecedence(token)) {
				char topToken = operatorStack.top();
				postfixExp += topToken;
				operatorStack.pop();
			}
			operatorStack.push(token);

		}
	}
	while (!operatorStack.empty()) {
		postfixExp += operatorStack.top();
		operatorStack.pop();
	}
	return true;
}

// ----------------------------------------------
bool Postfix::evalPostfix(int& result) {
	int strLength = postfixExp.length();
	char token;

	for (int c = 0; c < strLength; c++) {
		token = postfixExp[c];
		if (isOperator(token)) {
			if (operandStack.size() < 2) {
				return false;
			}
			int operand2 = operandStack.top();
			operandStack.pop();
			int operand1 = operandStack.top();
			operandStack.pop();
			int opResult = evaluate(token, operand1, operand2);
			operandStack.push(opResult);
		}
		else {
			operandStack.push(token - '0');
		}
	}
	result = operandStack.top();
	operandStack.pop();

	if (operandStack.size() != 0) {
		return false;
	}
	return true;
}

// ----------------------------------------------
bool Postfix::validate(std::string exp) {
	int strLength = exp.length();
	for (int c = 0; c < strLength; c++) {
		if (!isdigit(exp[c]) && !isOperator(exp[c])) {
			return false;
		}
	}
	return true;
}

// ----------------------------------------------
std::string Postfix::stripWhitespace(std::string infixExp) {
	infixExp.erase(std::remove_if(infixExp.begin(), infixExp.end(), std::isspace), infixExp.end());
	//for (int x = 0; x < infixExp.length(); x++) {
	//	if (std::isspace(infixExp[x])) {
	//		infixExp.erase(infixExp.begin() + x);
	//	}
	//}
	return infixExp;
}

// ----------------------------------------------
bool Postfix::isOperator(char op) {
	for (int x = 0; x < NUM_OPERATORS; x++) {
		if (OPERATORS[x].op == op) {
			return true;
		}
	}
	return false;
}

// ----------------------------------------------
int Postfix::getPrecedence(char op) {
	for (int x = 0; x < NUM_OPERATORS; x++) {
		if (OPERATORS[x].op == op) {
			return OPERATORS[x].prec;
		}
	}
	return 0;
}

// ----------------------------------------------
int Postfix::evaluate(char token, int operand1, int operand2) {
	if (token == '*') {
		return operand1 * operand2;
	}
	if (token == '/') {
		return operand1 / operand2;
	}
	if (token == '+') {
		return operand1 + operand2;
	}
	if (token == '-') {
		return operand1 - operand2;
	}
	return 0;
}

void Postfix::parseToList(std::string exp, std::list<std::string>& list) {
//	char delimiters[] = { " ", "+" };
	//char* token;
	//char* temp = _strdup(exp.c_str());
	//token = strtok(temp, " +	");

	//while (token != NULL) {
	//	list.push_back(token);
	//	token = strtok(NULL, " +	");
	//}

//	std::regex delimiters("([\\(\\)\\*[:space:]\\+-\]|[^\\(\\)\\*[:space:]\\+-\]+)");
	std::string dPattern = "([\\(\\)\\*[:space:]\\+-\]|[^\\(\\)\\*[:space:]\\+-\]+)";
	typename std::regex delimiters(dPattern);
	typename std::regex_iterator<std::string::iterator> rit(exp.begin(), exp.end(), delimiters);
	typename std::regex_iterator<std::string::iterator> rend;
	typename std::regex blank("(^[[:space:]]$)");
	while (rit != rend) {
		if (!std::regex_match(rit->str(), blank)) {
			list.push_back(rit->str());
		}
		++rit;
	}

}