/** ---------------------------------------------
*
* @file		Postfix.h
* @author	Nick McCollum
* @version	2.0
*
* CS-260-02 - Assignment 3
* Interface and implementation for Postfix class template
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
	std::string op;
	int prec;
};

const int NUM_OPERATORS = 7;
const Operators OPERATORS[] = { {"*", 3}, {"/", 3}, {"+", 2}, {"-", 2}, {"(", 1}, {")", 0}, {".", 0} };

template <typename Type>
class Postfix
{
public:
	/**
		Default constructor.
		Sets the expression when instantiated.

		@param	exp	The expression to be converted to postfix
	*/
	Postfix(std::string exp = "");

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
	bool evalPostfix(Type& result);

private:
	std::string exp;
	std::string infixExp;
	std::string postfixExp;
	std::stack<std::string> operatorStack;
	std::stack<Type> operandStack;
	std::list<std::string> infixExpLst;
	std::list<std::string> postfixExpLst;

	/**
		Checks that the expression only contains valid characters

		@param	exp	The expression to be validated
		@return		True if the expression is valid, false otherwise
	*/
	bool validate(std::string exp);

	/**
		Determines if the provided character is a valid operator

		@param	op	The operator to check
		@return		True if valid operator, false if not
	*/
	bool isOperator(std::string op);

	/**
		Determines the precedence of an operator

		@param	op	The operator to check
		@return		An integer representing the precedence relative to the other operators.
					Possible values are 0 - 3.
	*/
	int getPrecedence(std::string op);

	/**
		Concatenates a list of strings into a single string

		@param	list	List of strings
		@return			String containing all values from the list
	*/
	std::string buildString(std::list<std::string> list);

	/**
		Evalutates a simple binomial expression

		@param	op			The operator
		@param	operand1	The first operand to be used in the expression
		@param	operand2	The second operand to be used in the expression
		@return				Result after evaluating the expression
	*/
	Type evaluate(std::string op, Type operand1, Type operand2);

	/**
		Splits a string based on predefined delimiters and places the substrings in a list

		@param	exp		The string to be parsed
		@param	list	The list to be populated with substrings
	*/
	void parseToList(std::string exp, std::list<std::string>& list);
};

// ----------------------------------------------
template <typename Type>
Postfix<Type>::Postfix(std::string exp) {
	this->exp = exp;
	infixExp = "";
	postfixExp = "";
}

// ----------------------------------------------
template <typename Type>
void Postfix<Type>::setExp(std::string exp) {
	this->exp = exp;
}

// ----------------------------------------------
template <typename Type>
std::string Postfix<Type>::getExp() {
	return exp;
}

// ----------------------------------------------
template <typename Type>
std::string Postfix<Type>::getInfixExp() {
	return infixExp;
}

// ----------------------------------------------
template <typename Type>
std::string Postfix<Type>::getPostfixExp() {
	return postfixExp;
}

// ----------------------------------------------
template <typename Type>
void Postfix<Type>::print(std::string exp) {
	std::cout << exp << std::endl;
}

// ----------------------------------------------
template <typename Type>
void Postfix<Type>::printError(std::string error) {
	if (error != "") {
		std::cerr << error << std::endl;
	}
	else {
		std::cerr << "Error!\n";
	}
}

// ----------------------------------------------
template <typename Type>
bool Postfix<Type>::convertToInfix() {
	if (validate(exp)) {
		parseToList(exp, infixExpLst);
		infixExp = buildString(infixExpLst);
		return true;
	}
	return false;
}

// ----------------------------------------------
template <typename Type>
bool Postfix<Type>::convertToPostfix() {
	int listLength = infixExpLst.size();
	std::string token;

	for (std::list<std::string>::iterator it = infixExpLst.begin(); it != infixExpLst.end(); it++) {
		token = *it;
		if (std::regex_match(token, std::regex("([0-9.]+)|^(-[0-9.]+)"))) {
			postfixExpLst.push_back(token);
			postfixExp += token;
		}
		else if (token == "(") {
			operatorStack.push(token);
		}
		else if (token == ")") {
			std::string topToken = operatorStack.top();
			operatorStack.pop();
			while (topToken != "(") {
				postfixExpLst.push_back(topToken);
				postfixExp += topToken;
				topToken = operatorStack.top();
				operatorStack.pop();
			}
		}
		else {
			while (!operatorStack.empty() && getPrecedence(operatorStack.top()) >= getPrecedence(token)) {
				std::string topToken = operatorStack.top();
				postfixExpLst.push_back(topToken);
				postfixExp += topToken;
				operatorStack.pop();
			}
			operatorStack.push(token);

		}
	}
	while (!operatorStack.empty()) {
		postfixExpLst.push_back(operatorStack.top());
		postfixExp += operatorStack.top();
		operatorStack.pop();
	}
	return true;
}

// ----------------------------------------------
template <typename Type>
bool Postfix<Type>::evalPostfix(Type& result) {
	int listLength = postfixExpLst.size();
	std::string token;

	for (std::list<std::string>::iterator it = postfixExpLst.begin(); it != postfixExpLst.end(); it++) {
		token = *it;
		if (isOperator(token)) {
			if (operandStack.size() < 2) {
				return false;
			}
			Type operand2 = operandStack.top();
			operandStack.pop();
			Type operand1 = operandStack.top();
			operandStack.pop();
			Type opResult = evaluate(token, operand1, operand2);
			operandStack.push(opResult);
		}
		else {
			if (token.find(".") == 1) {
				float operand = std::stof(token);
				operandStack.push(operand);
			}
			else {
				int operand = std::stoi(token);
				operandStack.push(operand);
			}
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
template <typename Type>
bool Postfix<Type>::validate(std::string exp) {
	int strLength = exp.length();
	std::string opStr;
	for (int c = 0; c < strLength; c++) {
		opStr = exp[c];
		if (!isdigit(exp[c]) && !isspace(exp[c]) && !isOperator(opStr)) {
			return false;
		}
	}
	return true;
}

// ----------------------------------------------
template <typename Type>
bool Postfix<Type>::isOperator(std::string op) {
	for (int x = 0; x < NUM_OPERATORS; x++) {
		if (OPERATORS[x].op == op) {
			return true;
		}
	}
	return false;
}

// ----------------------------------------------
template <typename Type>
int Postfix<Type>::getPrecedence(std::string op) {
	for (int x = 0; x < NUM_OPERATORS; x++) {
		if (OPERATORS[x].op == op) {
			return OPERATORS[x].prec;
		}
	}
	return 0;
}

// ----------------------------------------------
template <typename Type>
std::string Postfix<Type>::buildString(std::list<std::string> list) {
	std::string str = "";
	for (std::list<std::string>::iterator it = list.begin(); it != list.end(); it++) {
		str += *it;
	}
	return str;
}

// ----------------------------------------------
template <typename Type>
Type Postfix<Type>::evaluate(std::string token, Type operand1, Type operand2) {
	if (token == "*") {
		return operand1 * operand2;
	}
	if (token == "/") {
		return operand1 / operand2;
	}
	if (token == "+") {
		return operand1 + operand2;
	}
	if (token == "-") {
		return operand1 - operand2;
	}
	return 0;
}

// ----------------------------------------------
template <typename Type>
void Postfix<Type>::parseToList(std::string exp, std::list<std::string>& list) {
	// This is kludgy but it works.
	// TODO: Improve regex patterns to eliminate the extra logic
	std::string dPattern = "([\\(\\)\\*/[:space:]\\+-]|[^\\(\\)\\*/[:space:]\\+-]+)";
	std::string dPatternNeg = "([\\(\\)\\*/[:space:]\\+]|[^\\(\\)\\*/[:space:]\\+]+)";
	std::string negPattern = "^\\s?(-[0-9.]+)";
	typename std::regex blank("(^[[:space:]]$)");
	typename std::regex negInStr("[+-/*]+\\s-[0-9]+");
	typename std::regex negBeginStr("^-");
	typename std::regex delimiters;
	if (std::regex_search(exp, negBeginStr) || std::regex_search(exp, negInStr)) {
		delimiters = negPattern + "|" + dPatternNeg;
	}
	else {
		delimiters = negPattern + "|" + dPattern;
	}

	std::string token;
	typename std::regex_iterator<std::string::iterator> rit(exp.begin(), exp.end(), delimiters);
	typename std::regex_iterator<std::string::iterator> rend;
	while (rit != rend) {
		token = rit->str();
		if (!std::regex_match(token, blank)) {
			list.push_back(token);
		}
		++rit;
	}
}