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
#include <cctype>
#include <iostream>
#include <algorithm>

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
	Postfix(std::string exp);

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
	void printError(std::string error);

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
private:
	std::string exp;
	std::string infixExp;
	std::string postfixExp;
	std::stack<char> operatorStack;
	std::stack<int> operandStack;

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

