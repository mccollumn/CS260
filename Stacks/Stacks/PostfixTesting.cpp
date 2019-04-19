/** ---------------------------------------------
*
* @file		PostfixTesting.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-260-02 - Assignment 3
* Test code for the Postfix class
*
* -------------------------------------------- */

#include "Postfix.h"

const int NUM_EXPRESSIONS = 5;

int main() {
	Postfix exp[NUM_EXPRESSIONS];
	exp[0].setExp("5 # 2");
	exp[1].setExp("5 * - 6 8");
	exp[2].setExp("5*2  +   3");
	exp[3].setExp("3 + 5 * (7-2)");
	exp[4].setExp("3 + ( (8-5) * (4+9) )");

	int result;

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

	return 1;
}