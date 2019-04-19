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

#include "Postfix.h"

// ----------------------------------------------
Postfix::Postfix() {
	exp = "";
	infixExp = "";
	postfixExp = "";
}

// ----------------------------------------------
Postfix::Postfix(std::string exp = "") {
	this->exp = exp;
	infixExp = "";
	postfixExp = "";
}

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
void Postfix::printError(std::string error = "") {
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