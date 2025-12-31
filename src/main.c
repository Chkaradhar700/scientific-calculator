#include "common.h"
#include "globals.h"
#include "arithmetic.h"
#include "utils.h"
#include "list.h"
#include "tree.h"
#include "parser.h"
#include "validation.h"
#include "commands.h"



//Tool functions
void identifyPrimeNumber(char *);


int main(int argc, char *argv[])
{
	/*
	char const *literal = "123456789123456789.900000100002";
	printf("\t%Lf", divide(1, 6));
	printf("\n\t%.12LF", toDecimal(literal));
	printf("\n\t%.12LF", strtold(literal, 0));

	char str[20] = "T'es qui ?";
	//printf("\n\t%d %d", strlen(str), (sizeof str) / sizeof(char));
	writeInString(str, 20, 0, "()");
	printf("\n\n\t\"%s\"", str);
	deleteFromString(str, 20, 6, 4);
	printf("\n\t\"%s\"", str);

	char str2[20];
	strcpy(str2, copyFromString(str, 1, 1));
	printf("\n\n\t\"%s\"", str2);

	char str3[] = FACTORIAL "(2 * 6)";
	FunctionInfos infos;
	infos = getFunctionInfos(str3);
	printf("\n\n\tname \"%s\" arg1 \"%s\" arg2 \"%s\"", infos.name, infos.arg1, infos.arg2);

	char str4[] = SUBTRACT "(" ADD "(" TO_DECIMAL "(2)," MULTIPLY "(" TO_DECIMAL "(4)," TO_DECIMAL "(6)))," SQRTL "(" ADD "(" TO_DECIMAL "(8)," TO_DECIMAL "(10))))";
	FunctionInfos infos2;
	infos2 = getFunctionInfos(str4);
	printf("\n\n\tstring : \"%s\"", str4);
	printf("\n\tname \"%s\" -_- arg1 \"%s\" -_- arg2 \"%s\"", infos2.name, infos2.arg1, infos2.arg2);
	printf("\n\n\tResults : \"%.50Lf\"", operate(str4));
	
	printf("\n\n\t%Lg", operate(FACTORIAL "(" TO_DECIMAL "(1500.00000000000000000000000000000001))"));
	*/

	/*
	List *list;
	list = initializeList();
	printList(list);
	printf("\t%d\n", list->nbrOfCreatedObjects);
	int id = getNewId(list);
	printf("\t%d = %d\n\n", list->nbrOfCreatedObjects, id);

	printf("********** 1 **********\n");
	list = initializeList();
	insertAtTheEnd(list, "1st");
	printList(list);
	insertAtTheEnd(list, "2nd");
	printList(list);
	insertBefore(list, "Another", getObject(list, 2));
	printList(list);

	printf("\n\n\n********** 2 **********\n");
	list = initializeList();
	insertAtTheEnd(list, "1st");
	printList(list);
	insertAfter(list, "2nd", getObject(list, 1));
	printList(list);
	insertAfter(list, "3rd", getObject(list, 1));
	printList(list);

	printf("\n\n\n********** 3 **********\n");
	list = initializeList();
	insertAtTheEnd(list, "1st");
	insertAtTheEnd(list, "2nd");
	insertAtTheEnd(list, "3rd");
	insertAtTheEnd(list, "4th");
	printList(list);
	deleteFromList(list, getObject(list, 3));
	printList(list);
	deleteFromList(list, getObject(list, 4));
	printList(list);
	deleteFromList(list, getObject(list, 1));
	printList(list);
	deleteFromList(list, getObject(list, 2));
	printList(list);

	printf("\n\n\n********** 4 **********\n");
	list = initializeList();
	insertAtTheEnd(list, "1st");
	insertAtTheEnd(list, "2nd");
	printList(list);
	deleteAllFromList(list);
	printList(list);
	insertAtTheEnd(list, "1st");
	printList(list);
	deleteAllFromList(list);
	printList(list);
	deleteAllFromList(list);
	printList(list);
	
	printf("\n\n\n********** 5 **********\n");
	list = initializeList();
	insertAtTheEnd(list, "sin");
	insertAtTheEnd(list, "(");
	insertAtTheEnd(list, "3");
	insertAtTheEnd(list, "+");
	insertAtTheEnd(list, "6");
	insertAtTheEnd(list, "sqrt");
	insertAtTheEnd(list, "(");
	insertAtTheEnd(list, "16");
	insertAtTheEnd(list, ")");
	insertAtTheEnd(list, "(");
	insertAtTheEnd(list, "5");
	insertAtTheEnd(list, "*");
	insertAtTheEnd(list, "6");
	insertAtTheEnd(list, ")");
	insertAtTheEnd(list, ")");
	printf("%s", listToString(list));
	*/

	/*
	List *list;
	list = initializeList();
	insertAtTheEnd(list, "25");
	insertAtTheEnd(list, "*");
	insertAtTheEnd(list, E_SIN);
	insertAtTheEnd(list, "(");
	insertAtTheEnd(list, "87");
	insertAtTheEnd(list, "*");
	insertAtTheEnd(list, "(");
	insertAtTheEnd(list, ")");
	insertAtTheEnd(list, ")");
	insertAtTheEnd(list, ")");
	printList(list);

	printf("\n\n\t%d  %d  %d", isIncluded(list, getObject(list, 1)), isExternalFunction(getObject(list, 8)), isOperator(getObject(list, 3)));

	Block *block = identifyBlockFrom(list, getObject(list, 3), left_to_right);
	if (block != NULL)
	{
		printf("\n\n\t%d , %d", block->beginning->id, block->end->id);
	}

	block = identifyBlockFrom(list, getObject(list, 9), right_to_left);
	if (block != NULL)
	{
		printf("\n\n\t%d , %d", block->beginning->id, block->end->id);
	}
	

	Operators operators = identifyOperatorsBetween(list, getObject(list, 4), getObject(list, 9));
	int i;
	printf("\n\n\t");
	for (i = 0; i < operators.nbrOfOperators; i++)
	{
		printf("[\"%s\" %d] ", operators.operators[i]->value, operators.operators[i]->id);
	}
	
	Blocks blocks = identifyBlocksBetween(list, getObject(list, 3), getObject(list, 9));
	printf("\n\n\t");
	for (i = 0; i < blocks.nbrOfBlocks; i++)
	{
		printf("[%d-%d] ", blocks.blocks[i]->beginning->id, blocks.blocks[i]->end->id);
	}
	*/

	/*
	List *list = initializeList();
	insertAtTheEnd(list, "(");
	insertAtTheEnd(list, "u-");
	insertAtTheEnd(list, "34");
	insertAtTheEnd(list, "+");
	insertAtTheEnd(list, "43.2");
	insertAtTheEnd(list, "*");
	insertAtTheEnd(list, E_SQRT);
	insertAtTheEnd(list, "(");
	insertAtTheEnd(list, "12");
	insertAtTheEnd(list, "!");
	insertAtTheEnd(list, "b-");
	insertAtTheEnd(list, "56");
	insertAtTheEnd(list, ")");
	insertAtTheEnd(list, ")");

	Tree *tree = initializeTree();
	printf("\"%s\"", treeToString(tree));
	fillTree(tree, list);
	printf("\n\"%s\"", treeToString(tree));

	deleteAllFromTree(tree);
	printf("\n\n\"%s\"", treeToString(tree));
	deleteAllFromTree(tree);
	printf("\n\"%s\"", treeToString(tree));

	fillTree(tree, list);
	insertAtTheEnd(list, ")");
	insertAtTheEnd(list, "+][+");
	printf("\n\n\"%s\"", treeToString(tree));
	deleteAllFromList(list);
	printf("\n\"%s\"", treeToString(tree));
	*/

	/*
	List *list = initializeList();
	insertAtTheEnd(list, "5");
	insertAtTheEnd(list, "+");
	insertAtTheEnd(list, "3.0");
	insertAtTheEnd(list, "!");
	insertAtTheEnd(list, "u-");
	insertAtTheEnd(list, "sin");
	insertAtTheEnd(list, "(");
	insertAtTheEnd(list, "pi");
	insertAtTheEnd(list, ")");
	
	printf("\t%s", listToString(list));
	printf("\n\t%d   %d", isConstant(getObject(list, 8)), isNumber(getObject(list, 3)));
	
	printf("\n\n\t%s", getInternalFunction("b-"));

	manageNumber(list, getObject(list, 1));
	printf("\n\n\t%s", listToString(list));
	manageConstant(list, getObject(list, 8));
	printf("\n\t%s", listToString(list));
	
	deleteAllFromList(list);
	insertAtTheEnd(list, "5");
	insertAtTheEnd(list, "+");
	insertAtTheEnd(list, "3.0");
	insertAtTheEnd(list, "!");
	insertAtTheEnd(list, "u-");
	insertAtTheEnd(list, "sin");
	insertAtTheEnd(list, "(");
	insertAtTheEnd(list, "pi");
	insertAtTheEnd(list, ")");
	
	//printList(list);
	printf("\n\n\t%s", listToString(list));
	manageOperator(list, getObject(list, 21));
	printf("\n\t%s", listToString(list));
	manageOperator(list, getObject(list, 23));
	printf("\n\t%s", listToString(list));
	manageOperator(list, getObject(list, 24));
	printf("\n\t%s", listToString(list));
	manageExternalFunction(list, getObject(list, 25));
	printf("\n\t%s", listToString(list));
	*/

	/*
	List *list = initializeList();
	insertAtTheEnd(list, "(");
	insertAtTheEnd(list, "+");
	insertAtTheEnd(list, "!");
	insertAtTheEnd(list, "*");
	insertAtTheEnd(list, "b-");
	insertAtTheEnd(list, "^");
	insertAtTheEnd(list, "/");
	insertAtTheEnd(list, "u-");
	insertAtTheEnd(list, "%");
	insertAtTheEnd(list, ")");
	printf("\t%s", listToString(list));
	
	Operators operators = identifyOperatorsBetween(list, getObject(list, 1), getObject(list, 10));
	printf ("\n\n\t");
	int i;
	for (i = 0; i < operators.nbrOfOperators; i++)
	{
		printf ("%s ", operators.operators[i]->value);
	}
	
	sortOperators(operators.operators, operators.nbrOfOperators);
	printf ("\n\n\t");
	for (i = 0; i < operators.nbrOfOperators; i++)
	{
		printf ("%s ", operators.operators[i]->value);
	}
	
	deleteAllFromList(list);
	insertAtTheEnd(list, "(");
	insertAtTheEnd(list, "5");
	insertAtTheEnd(list, "b-");
	insertAtTheEnd(list, "6");
	insertAtTheEnd(list, "+");
	insertAtTheEnd(list, "2");
	insertAtTheEnd(list, "*");
	insertAtTheEnd(list, "3");
	insertAtTheEnd(list, "/");
	insertAtTheEnd(list, "u-");
	insertAtTheEnd(list, "4");
	insertAtTheEnd(list, "^");
	insertAtTheEnd(list, "3");
	insertAtTheEnd(list, "!");
	insertAtTheEnd(list, "%");
	insertAtTheEnd(list, ")");
	//printList(list);
	
	Tree *tree = initializeTree();
	fillTree(tree, list);
	printf("\n\n\t%s", listToString(list));
	printf("\n\t%s", treeToString(tree));
	manageAllObjects(tree);
	printf("\n\n\t%s\n", listToString(list));
	char *string = listToString(list);
	printf("\nThe results of operation is : %.10Lf", operate(string));
	
	deleteAllFromTree(tree);
	deleteAllFromList(list);
	insertAtTheEnd(list, "(");
	insertAtTheEnd(list, "u-");
	insertAtTheEnd(list, "(");
	insertAtTheEnd(list, "4");
	insertAtTheEnd(list, "+");
	insertAtTheEnd(list, "1");
	insertAtTheEnd(list, ")");
	insertAtTheEnd(list, "*");
	insertAtTheEnd(list, "sqrt");
	insertAtTheEnd(list, "(");
	insertAtTheEnd(list, "16");
	insertAtTheEnd(list, "!");
	insertAtTheEnd(list, ")");
	insertAtTheEnd(list, ")");
	//printList(list);
	
	fillTree(tree, list);
	printf("\n\n\n\t%s", listToString(list));
	printf("\n\t%s", treeToString(tree));
	manageAllObjects(tree);
	printf("\n\n\t%s\n", listToString(list));
	string = listToString(list);
	printf("\nThe results of operation is : %.10Lf", operate(string));
	deleteAllFromTree(tree);
	deleteAllFromList(list);
	*/

	/*
	printf("Enter a characters string : ");
	char string[100];
	scan(string, 100);
	printf("\"%s\"", string);
	List *list = initializeList();
	list = stringToList(string);
	printList(list);

	//printSyntaxError(list, getObject(list, 3));
	printf("\n\n");
	if (syntaxAnalysis(list))
	{
		printf("The syntax is correct.");
		printf("\n%s", listToString(list));
		manageAllConstants(list);
		printf("\n%s", listToString(list));
		manageImplicitMultiplications(list);
		printf("\n%s", listToString(list));
	}
	*/
	

















	
	//Main variables
	char mode[LENGTH_OF_MODE + 1];
	char stopMode[LENGTH_OF_MODE + 1];
	int precision;
	char string[COMMAND_LENGTH + 1 + 1]; //+1 for '\n' and another +1 for '\0'
	char stringToOperate[FUNCTION_ARGS_SIZE];
	long double results;
	//Main variables

	int i;
	for (i = 0; i < LENGTH_OF_MODE; i++) //Initializations
	{
		mode[i] = '0';
		stopMode[i] = '0';
	}
	mode[i] = '\0';
	stopMode[i] = '\0';

	c_setPrecision(&precision);
	c_setMode(mode, false);

	while (strcmp(mode, stopMode) != 0)
	{
		//Calculator
		if (mode[0] == '1')
		{
			while (mode[0] == '1')
			{
				printf("\e[32mCalculator : \e[0m");
				scan(string, COMMAND_LENGTH);
				if (isCommand(string))
				{
					runCommand(string, mode, &precision);
					continue;
				}

				List *list = initializeList();
				errorInInterpretation = false;
				list = stringToList(string);
				if (errorInInterpretation)
				{
					continue;
				}

				if (syntaxAnalysis(list) == false)
				{
					printf("\n\n");
					continue;
				}
				manageAllConstants(list);
				manageImplicitMultiplications(list);

				Tree *tree = initializeTree();
				insertBefore(list, "(", list->first);
				insertAtTheEnd(list, ")");
				fillTree(tree, list);
				manageAllObjects(tree);
				strcpy(stringToOperate, listToString(list));

				deleteAllFromList(list);
				deleteAllFromTree(tree);

				errorInExecution = false;
				results = operate(stringToOperate);
				if (!errorInExecution)
				{
					printf("\e[32mResults : \e[0m");
					switch (precision)
					{
					case 10:
						printf("%.10Lg\n\n", results);
						break;
					case 20:
						printf("%.20Lg\n\n", results);
						break;
					case 30:
						printf("%.30Lg\n\n", results);
						break;
					}
				}
			}
		}
		//Tools
		else if (mode[0] == '2')
		{
			//Identifier of prime number
			if (mode[1] == '1')
			{
				while (mode[0] == '2' && mode[1] == '1')
				{
					printf("\e[32mTools->IdentifierOfPN : \e[0m");
					scan(string, COMMAND_LENGTH);
					if (isCommand(string))
					{
						runCommand(string, mode, &precision);
						continue;
					}

					printf("\e[32mResults : \e[0m");
					identifyPrimeNumber(string);
				}
			}
		}
		//Documentation
		else if (mode[0] == '3')
		{
			bool firstTime;
			firstTime = true;

			//Credit
			if (mode[1] == '1')
			{
				while (mode[0] == '3' && mode[1] == '1')
				{
					printf("\e[32mDoc->Credit : \e[0m");
					if (firstTime)
					{
						printf("\n"
							   "-----DEVELOPER-----"
							   "\n"
							   "J. G. O. Samuel AKABASSI"
							   "\n\n");
						firstTime = false;
						continue;
					}
					scan(string, COMMAND_LENGTH);
					if (isCommand(string))
					{
						runCommand(string, mode, &precision);
						continue;
					}
				}
			}
			//How to use ?
			else if (mode[1] == '2')
			{
				while (mode[0] == '3' && mode[1] == '2')
				{
					printf("\e[32mDoc->HowToUse : \e[0m");
					if (firstTime)
					{
						printf("\n"
							   "HOW TO USE ?"
							   "\n"
							   "This program is divided into two main parts:"
							   "\n"
							   "- a calculator which allows you to perform all the basic operations and also offers some scientific functions;"
							   "\n"
							   "- a set of mathematical tools (for example to check if a number is prime or not)."
							   "\n"
							   "\n"
							   "This program also has a control system using commands. Here are the available commands and their functions:"
							   "\n"
							   "1- setMode: Allows you to choose an operating mode."
							   "\n"
							   "2- back: Returns to the previous mode selection step."
							   "\n"
							   "3- setPrecision: Sets the display precision of decimal results."
							   "\n"
							   "4- displayInfos: Allows you to display information about representable values, display precision of real numbers, etc."
							   "\n"
							   "5- clear: Clears the screen."
							   "\n"
							   "6- exit: Allows you to stop the program and exit."
							   "\n"
							   "\n"
							   "THE CALCULATOR"
							   "\n"
							   "To perform an operation, you must select Calculator mode and then write your operation. Your operation can only contain five (5) types of elements: Numbers, Operators, Constants, Separators, Functions."
							   "\n"
							   "1- The numbers are expressed in decimal base. The decimal point is indicated by the character \".\" . Example: 45.6 ."
							   "\n"
							   "2- This is the list of available operators: \"/\" (Division), \"*\" (Multiplication), \"-\" (Subtraction), \"+\" (Addition), \"%%\" (Percentage), \"!\" (Factorial  ), \"^\" (Exponentation). Example: 2.2+3*4.4 ."
							   "\n"
							   "3- There are two constants: \"pi\" (Mathematical constant Pi) and \"e\" (Mathematical constant e). Example: 2pi*e ."
							   "\n"
							   "4- There are two separators that allow you to group operations: \"(\" and \")\". Example: 2.2(3+4)(5+6) ."
							   "\n"
							   "5- This is the list of available functions: \"sqrt\" (Square Root), \"sin\" (Sinus), \"cos\" (Cosine), \"tan\" (Tangent), \"ln\" (Natural Logarithm), \"log\" (Decimal Logarithm), \"asin\" (Arc Sinus), \"acos\" (Arc Cosine), \"atan\" (Arc Tangent), \"exp\" (Exponential). To apply a function to a number(or operation), surround it with separators. Example: sin(sqrt(16)+5) ."
							   "\n"
							   "NOTE: Please see the \"Operators Precedence\" section of the documentation for details on how operators are evaluated."
							   "\n"
							   "\n"
							   "TOOLS"
							   "\n"
							   "To use a tool, select the corresponding mode."
							   "\n\n");
						firstTime = false;
						continue;
					}
					scan(string, COMMAND_LENGTH);
					if (isCommand(string))
					{
						runCommand(string, mode, &precision);
						continue;
					}
				}
			}
			//Operators precedence
			else if (mode[1] == '3')
			{
				while (mode[0] == '3' && mode[1] == '3')
				{
					printf("\e[32mDoc->OperatorsPrecedence : \e[0m");
					if (firstTime)
					{
						printf("\n"
							   "OPERATORS PRECEDENCE"
							   "\n"
							   "This is the list of operators grouped in descending order of priority :"
							   "\n"
							   "\t! %%\t\t-->"
							   "\n"
							   "\t^ unary-\t<--"
							   "\n"
							   "\t/ *\t\t-->"
							   "\n"
							   "\t+ binary-\t-->"
							   "\n"
							   "Operators on the same line have the same precedence and are evaluated against each other following the direction of the associated arrow."
							   "\n"
							   "Example 1: In \"2+3*4\", \"*\" is evaluated and then \"+\". The expression is therefore equivalent to: \"2+(3*4)\". The result is: 14 ."
							   "\n"
							   "Example 2: In \"2+3-4\", \"+\" is evaluated and then \"-\". The expression is therefore equivalent to: \"(2+3)-4\". The result is: 1 ."
							   "\n"
							   "Example 3: In \"-3^4^5\", the last \"^\" is evaluated, then the first \"^\" and finally the \"-\". The expression is therefore equivalent to: \"-(3^(4^5))\". The result is approximately: -3.733918487×10⁴⁸⁸ ."
							   "\n"
							   "Example 4: In \"-3^4+5^-6-7!\", \"!\" is evaluated, then the second \"-\", then the second \"^\", then the first \"^\", then the first \"-\", then the \"+\", then the last \"-\".  The expression is therefore equivalent to: \"((-(3^4))+(5^(-6)))-(7!)\". The result is: -5120.999936 ."
							   "\n\n");
						firstTime = false;
						continue;
					}
					scan(string, COMMAND_LENGTH);
					if (isCommand(string))
					{
						runCommand(string, mode, &precision);
						continue;
					}
				}
			}
		}
	}

	printf("\n");
	system("pause");
	return 0;
	
	
	
	
}





//****************************************
//Tool functions
//****************************************
/**
 * This function takes a character string as a parameter. It tries to convert it to an integer. When all is well, this function displays whether the obtained number is prime or not.
 *
 */
void identifyPrimeNumber(char *string)
{
	//********************
	const int FUNCTION_ID = 71;
	//********************

	if (string == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	long long number, i;
	bool isPrime;
	number = strtoll(string, 0, 10);

	char verificationString[COMMAND_LENGTH];
	sprintf(verificationString, "%lld", number);

	if (strcmp(string, verificationString) != 0 || !isdigit(string[0])) //The second condition is to check if the number is negative or not.
	{
		printf("\e[31mSyntax error\n\n\e[0m");
		return;
	}
	else
	{
		if (number < 2)
		{
			printf("It is not prime\n\n");
			return;
		}

		for (i = 2, isPrime = true; i < number; i++)
		{
			if (number % i == 0)
			{
				isPrime = false;
				break;
			}
		}

		if (isPrime)
		{
			printf("It is prime\n\n");
			return;
		}
		else
		{
			printf("It is not prime\n\n");
			return;
		}
	}
}