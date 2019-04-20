/** ---------------------------------------------
*
* @file		PostfixTesting.cpp
* @author	Nick McCollum
* @version	2.0
*
* CS-260-02 - Assignment 3
* Test code for the Postfix class
*
* -------------------------------------------- */

#include "Postfix_template.h"

const int NUM_EXPRESSIONS = 5;

int main() {
	int result;
	float floatResult;
	Postfix<int> exp[NUM_EXPRESSIONS];
	exp[0].setExp("5 # 2");
	exp[1].setExp("5 * - 6 8");
	exp[2].setExp("5*2  +   3");
	exp[3].setExp("3 + 5 * (7-2)");
	exp[4].setExp("3 + ( (8-5) * (4+9) )");
	Postfix<int> mdExp("42 + (123 - 456 ) * (78-75)");
	Postfix<int> negExp("-4 + -5 * 3");
	Postfix<float> fpExp("4.1 + 4 * 4.25");

	std::cout << "Author: Nick McCollum\n\n";

	for (int x = 0; x < NUM_EXPRESSIONS; x++) {
		std::cout << "Processing:\t" << exp[x].getExp() << std::endl;
		std::cout << "Infix:\t\t";
		if (exp[x].convertToInfix()) {
			exp[x].print(exp[x].getInfixExp());
			exp[x].convertToPostfix();
			std::cout << "Postfix:\t";
			exp[x].print(exp[x].getPostfixExp());
			std::cout << "Result:\t\t";
			if (exp[x].evalPostfix(result)) {
				std::cout << result << std::endl;
			}
			else {
				exp[x].printError("Invalid postfix expression");
			}
		}
		else {
			exp[x].printError("Invalid expression");
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << "************\n";
	std::cout << "EXTRA CREDIT\n";
	std::cout << "************\n\n";

	std::cout << "Multidigit numbers:\n";
	std::cout << "Processing:\t" << mdExp.getExp() << std::endl;
	std::cout << "Infix:\t\t";
	if (mdExp.convertToInfix()) {
		mdExp.print(mdExp.getInfixExp());
		mdExp.convertToPostfix();
		std::cout << "Postfix:\t";
		mdExp.print(mdExp.getPostfixExp());
		std::cout << "Result:\t\t";
		if (mdExp.evalPostfix(result)) {
			std::cout << result << std::endl;
		}
		else {
			mdExp.printError("Invalid postfix expression");
		}
	}
	else {
		mdExp.printError("Invalid expression");
	}
	std::cout << std::endl;
	
	std::cout << "Negative numbers:\n";
	std::cout << "Processing:\t" << negExp.getExp() << std::endl;
	std::cout << "Infix:\t\t";
	if (negExp.convertToInfix()) {
		negExp.print(negExp.getInfixExp());
		negExp.convertToPostfix();
		std::cout << "Postfix:\t";
		negExp.print(negExp.getPostfixExp());
		std::cout << "Result:\t\t";
		if (negExp.evalPostfix(result)) {
			std::cout << result << std::endl;
		}
		else {
			negExp.printError("Invalid postfix expression");
		}
	}
	else {
		negExp.printError("Invalid expression");
	}
	std::cout << std::endl;

	std::cout << "Floating point numbers:\n";
	std::cout << "Processing:\t" << fpExp.getExp() << std::endl;
	std::cout << "Infix:\t\t";
	if (fpExp.convertToInfix()) {
		fpExp.print(fpExp.getInfixExp());
		fpExp.convertToPostfix();
		std::cout << "Postfix:\t";
		fpExp.print(fpExp.getPostfixExp());
		std::cout << "Result:\t\t";
		if (fpExp.evalPostfix(floatResult)) {
			std::cout << floatResult << std::endl;
		}
		else {
			fpExp.printError("Invalid postfix expression");
		}
	}
	else {
		fpExp.printError("Invalid expression");
	}
	std::cout << std::endl;

	return 1;
}