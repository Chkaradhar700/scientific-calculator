#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <float.h>

//NOTE : We will use the "long double" type to represent real numbers and the "long long" type to represent integers.

//#define PI 3.14159265358979323846264338327950288419
//#define EXP expl(1)
#define FUNCTION_NAME_SIZE 20
#define FUNCTION_ARGS_SIZE 10000
#define MAX_LENGTH_OF_NUMBER 100
#define COMMAND_LENGTH 500
#define LENGTH_OF_MODE 4

//The commands
#define C_SET_M "setMode"
#define C_BACK "back"
#define C_SET_P "setPrecision"
#define C_DISPLAY_I "displayInfos"
#define C_CLEAR "clear"
#define C_EXIT "exit"

//Constants
#define PI "pi"
#define E "e"

//Operators
#define OP_DIVIDE "/"
#define OP_TIMES "*"
#define OP_U_MINUS "u-"
#define OP_B_MINUS "b-"
#define OP_PLUS "+"
#define OP_PERCENT "%"
#define OP_FACTORIAL "!"
#define OP_POWER "^"

//External functions; E for External
//External functions are the functions that the user can use. Their names can be easily imagined by the user, for example "sin", "ln". They all have a correspondence among the internal functions.
#define E_SQRT "sqrt"
#define E_SIN "sin"
#define E_COS "cos"
#define E_TAN "tan"
#define E_LN "ln"
#define E_LOG "log"
#define E_ASIN "asin"
#define E_ACOS "acos"
#define E_ATAN "atan"
#define E_EXP "exp"

//Internal functions
//Internal functions are the functions used only inside the program. Their names are like abbreviations because the normal names of some functions are too long.
#define ACOSL "ac"
#define ASINL "as"
#define ATANL "at"
#define COSL "co"
#define SINL "si"
#define TANL "ta"
#define EXPL "ex"
#define LOGL "ln"
#define LOG10L "lg"
#define POWL "po"
#define SQRTL "sq"
#define ADD "ad"
#define SUBTRACT "su"
#define MULTIPLY "mu"
#define DIVIDE "di"
#define PERCENTAGE "pe"
#define FACTORIAL "fa"
#define OPPOSITE "op"
#define TO_DECIMAL "td"

enum Direction
{
	left_to_right,
	right_to_left
};
typedef enum Direction Direction;

struct FunctionInfos
{
	char name[FUNCTION_NAME_SIZE];
	char arg1[FUNCTION_ARGS_SIZE];
	char arg2[FUNCTION_ARGS_SIZE];
};
typedef struct FunctionInfos FunctionInfos;

//For the linked list
typedef struct OperationObject OperationObject;
struct OperationObject
{
	short int id;
	char value[MAX_LENGTH_OF_NUMBER]; //This table can contain a number, an operator, etc.. But its maximum length should be the maximum length of numbers.
	OperationObject *previous;
	OperationObject *next;
};

typedef struct List List;
struct List
{
	short int nbrOfCreatedObjects; //The number of objects created is incremented when a new object is inserted and is not decremented when an object is deleted. This number is set to zero when the list is initialized.
	OperationObject *first;
};

typedef struct Operators Operators;
struct Operators
{
	short int nbrOfOperators;
	OperationObject **operators;
};

//For the tree
typedef struct Block Block;
struct Block
{
	OperationObject *beginning;
	OperationObject *end;
	short int nbrOfOperators;
	OperationObject **operators;
	short int nbrOfSubBlocks;
	Block **subBlocks;
};

typedef struct Tree Tree;
struct Tree
{
	Block *root;
	List *associatedList;
};

typedef struct Blocks Blocks;
struct Blocks
{
	short int nbrOfBlocks;
	Block **blocks;
};

//Function to print errors
void printError(int, int);

//Operations functions
long double add(long double, long double);
long double subtract(long double, long double);
long double multiply(long double, long double);
long double divide(long double, long double);
long double percentage(long double);
long double factorial(long double);
long double opposite(long double);
long double toDecimal(char const *);

//String manipulation functions
void writeInString(char[], int, int, char const *);
void deleteFromString(char[], int, int, int);
char *copyFromString(char[], int, int);

//Functions to operate
FunctionInfos getFunctionInfos(char[]);
long double operate(char[]);
long double detectNanInfErrors(long double);

//Linked list manipulation functions
List *initializeList();
short int getNewId(List *);
OperationObject *getObject(List *, short int);
void insertBefore(List *, char[], OperationObject *);
void insertAfter(List *, char[], OperationObject *);
void insertAtTheEnd(List *, char[]);
void deleteFromList(List *, OperationObject *);
void deleteAllFromList(List *);
void printList(List *);
char *listToString(List *);

bool isIncluded(List *, OperationObject *);
bool isExternalFunction(OperationObject *);
bool isInternalFunction(OperationObject *);
bool isFunction(OperationObject *);
bool isOperator(OperationObject *);
bool isConstant(OperationObject *);
bool isNumber(OperationObject *);

bool isOperatorCategory1(OperationObject *);
bool isOperatorCategory2(OperationObject *);
bool isOperatorCategory3(OperationObject *);
bool isOperatorCategory4(OperationObject *);
bool isLeftSeparator(OperationObject *);
bool isRightSeparator(OperationObject *);
bool isSeparator(OperationObject *);

Operators identifyOperatorsBetween(List *, OperationObject *, OperationObject *);
Block *identifyBlockFrom(List *, OperationObject *, Direction);
Blocks identifyBlocksBetween(List *, OperationObject *, OperationObject *);

char *getInternalFunction(char[]);

void manageConstant(List *, OperationObject *);
void manageNumber(List *, OperationObject *);
void manageOperator(List *, OperationObject *);
void manageExternalFunction(List *, OperationObject *);
void manageAdditionalParentheses(List *);

//Tree manipulation functions
Tree *initializeTree();
void fillBlock(Block *, List *);
void fillTree(Tree *, List *);
void deleteBlock(Block *);
void deleteAllFromTree(Tree *);
char *blockToString(Block *);
char *treeToString(Tree *);

void sortOperators(OperationObject **, int);
void manageBlockOperators(Block *, List *);
void manageAllObjects(Tree *);

//Interface functions
List *stringToList(char *);
bool analyzeSyntaxForNumber(OperationObject *);
bool analyzeSyntaxForOperator(OperationObject *);
bool analyzeSyntaxForConstant(OperationObject *);
bool analyzeSyntaxForSeparator(OperationObject *);
bool analyzeSyntaxForExternalFunction(OperationObject *);
bool checkLeftAndRightSeparators(List *, OperationObject *);
void printSyntaxError(List *, OperationObject *);
bool syntaxAnalysis(List *);
void manageAllConstants(List *);
void manageImplicitMultiplications(List *);

//General functions
void scan(char *, int);
void emptyBuffer();

//Command functions
bool isCommand(char *);
void runCommand(char *, char *, int *);

void c_setMode(char *, bool);
void c_back(char *);
void c_setPrecision(int *);
void c_displayInfos(int);
void c_clear();
void c_exit(char *);

//Tool functions
void identifyPrimeNumber(char *);

//Global variables
bool errorInInterpretation;
bool errorInExecution;

int main(int argc, char *argv[])
{
	
	char const *literal = "123456789123456789.900000100002";
	printf("\t%Lf , %lf , %lf", divide(1, 6), PI, EXP);
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
	

















	/*
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
	*/
	
	
	
}



//****************************************
//Function to print errors
//****************************************
/**
 * We use this function to manage the display of errors.
 *
 */
void printError(int functionId, int errorId)
{
	fprintf(stderr, "\n\nERROR : %d-%d\n\n", functionId, errorId);
}



//****************************************
//Operations functions
//****************************************
long double add(long double a, long double b)
{
	return a + b;
}

long double subtract(long double a, long double b)
{
	return a - b;
}

long double multiply(long double a, long double b)
{
	return a * b;
}

long double divide(long double a, long double b)
{
	//********************
	const int FUNCTION_ID = 1;
	//********************

	if (b == 0)
	{
		printError(FUNCTION_ID, 1);
		fprintf(stderr, "Division by zero\n\n");
		errorInExecution = true;
		//exit(EXIT_FAILURE);
		return 0.0L;
	}
	else
	{
		return a / b;
	}
}

/**
 * This function allows to compute the percentage.
 * Note that it simply divides by 100. But on at least two calculator apps (that I have), the % operator has a different role.
 *
 */
long double percentage(long double a)
{
	return a / 100;
}

long double factorial(long double a)
{
	//********************
	const int FUNCTION_ID = 2;
	//********************

	if (a == floorl(a))
	{
		if (a < 0)
		{
			printError(FUNCTION_ID, 2);
			fprintf(stderr, "Factorial of negative number \n\n");
			errorInExecution = true;
			//exit(EXIT_FAILURE);
			return 0.0L;
		}
		else
		{
			long double product;
			int i;
			for (i = a, product = 1.0L; i > 1; i--)
			{
				product *= i;
			}
			return product;
		}
	}
	else
	{
		printError(FUNCTION_ID, 1);
		fprintf(stderr, "Factorial of decimal number\n\n");
		errorInExecution = true;
		//exit(EXIT_FAILURE);
		return 0.0L;
	}
}

long double opposite(long double a)
{
	return -a;
}

/**
 * We use this function to manage the secure conversion of string to decimal. Note that function "strtold(...)" is used to do the conversion.
 * Also note that this function accepts negative numbers. But when interpreting the operation entered by the user, the numbers can only contain digits or decimal points.
 *
 */
long double toDecimal(char const *literal)
{
	//********************
	const int FUNCTION_ID = 3;
	//********************

	const short int length = strlen(literal);
	if (length > 0)
	{
		bool strangeCharacter = false;
		short int nbrOfDigit = 0;
		short int nbrOfMinus = 0;
		short int nbrOfPoint = 0;
		short int pointPosition;
		int i;
		for (i = 0; i < length; i++)
		{
			if (isdigit(literal[i]))
			{
				nbrOfDigit++;
			}
			else if (literal[i] == '-')
			{
				nbrOfMinus++;
			}
			else if (literal[i] == '.')
			{
				nbrOfPoint++;
				pointPosition = i;
			}
			else
			{
				strangeCharacter = true;
				break;
			}
		}
		if (!strangeCharacter && nbrOfDigit > 0 && nbrOfMinus < 2 && nbrOfPoint < 2)
		{
			bool wrongPosition = false;
			if (nbrOfMinus == 1)
			{
				if (literal[0] != '-')
				{
					wrongPosition = true;
				}
			}
			if (nbrOfPoint == 1)
			{
				if (pointPosition != 0 && pointPosition != length - 1)
				{
					if (isdigit(literal[pointPosition - 1]) && isdigit(literal[pointPosition + 1]))
					{
					}
					else
					{
						wrongPosition = true;
					}
				}
				else
				{
					wrongPosition = true;
				}
			}

			if (!wrongPosition)
			{
				return strtold(literal, 0);
			}
			else
			{
				printError(FUNCTION_ID, 3);
				exit(EXIT_FAILURE);
				//return 0L;
			}
		}
		else
		{
			printError(FUNCTION_ID, 2);
			exit(EXIT_FAILURE);
			//return 0L;
		}
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return 0L;
	}
}



//****************************************
//String manipulation functions
//****************************************
/**
 * We use this function to copy a string ("stringToCopy") to another ("mainString").
 * "arraySize" is the size of the "mainString" character table (not to be confused with the length of the character string "mainString").
 * "startPosition" is the position to start copying.
 *
 */
void writeInString(char mainString[], int arraySize, int startPosition, char const *stringToCopy)
{
	//********************
	const int FUNCTION_ID = 4;
	//********************

	const short int mainStringSize = arraySize;
	const short int mainStringLength = strlen(mainString);
	if (mainStringLength < mainStringSize && startPosition <= mainStringLength && startPosition >= 0)
	{
		const short int stringToCopyLength = strlen(stringToCopy);
		if (mainStringLength + stringToCopyLength < mainStringSize)
		{
			//First we copy some old characters to new location
			int i;
			for (i = mainStringLength - 1; i >= startPosition; i--)
			{
				mainString[i + stringToCopyLength] = mainString[i];
			}
			//Second we copy the new characters
			int j;
			for (i = startPosition, j = 0; i <= startPosition + stringToCopyLength - 1; i++, j++)
			{
				mainString[i] = stringToCopy[j];
			}
			//Finally, we put '\0' in all unused boxes of the table
			for (i = mainStringLength + stringToCopyLength; i <= mainStringSize - 1; i++)
			{
				mainString[i] = '\0';
			}
			return; //Everything went well
		}
		else
		{
			printError(FUNCTION_ID, 2);
			exit(EXIT_FAILURE);
			//return; //There is an error
		}
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return; //There is an error
	}
}

/**
 * We use this function to delete "nbrOfCharacter" characters from "string".
 * "arraySize" is the size of the "string" character table (not to be confused with the length of the character string "string").
 * "startPosition" is the position to start deleting.
 *
 */
void deleteFromString(char string[], int arraySize, int startPosition, int nbrOfCharacter)
{
	//********************
	const int FUNCTION_ID = 5;
	//********************

	const short int stringLength = strlen(string);
	if (stringLength < arraySize && startPosition >= 0 && startPosition < stringLength && startPosition + nbrOfCharacter - 1 < stringLength)
	{
		//First we copy some characters to new location
		int i;
		for (i = startPosition; i <= stringLength - 1; i++)
		{
			string[i] = string[i + nbrOfCharacter];
		}
		//Finally, we put '\0' in all unused boxes of the table
		for (i = stringLength - nbrOfCharacter; i <= arraySize - 1; i++)
		{
			string[i] = '\0';
		}
		return; //Everything went well
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return; //There is an error
	}
}

/**
 * We use this function to copy the characters of "string" between "startPosition" position and "endPosition" position.
 *
 */
char *copyFromString(char string[], int startPosition, int endPosition)
{
	//********************
	const int FUNCTION_ID = 6;
	//********************

	const short int stringLength = strlen(string);
	if (stringLength > 0 && startPosition >= 0 && startPosition < stringLength && endPosition >= 0 && endPosition < stringLength && startPosition <= endPosition)
	{
		const short int resultsLength = endPosition - startPosition + 1;
		char results[resultsLength + 1];
		int i, j;
		for (i = startPosition, j = 0; i <= endPosition; i++, j++)
		{
			results[j] = string[i];
		}
		results[resultsLength] = '\0';
		char *finalResults = results;
		return finalResults;
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//char *results = "";
		//return results;
	}
}



//****************************************
//Functions to operate
//****************************************
/**
 * We use this function to retrieve function information contained in a string ("string").  This information is: the name of the function, its first argument and its second argument (if it has two).
 * For example: in "add(3,5)", "add" is the name, "3" the first argument and "5" the second argument;  in "sinl(-6)", "sinl" is the name, "-6" is the first argument, as for the second argument, it is null.
 * Note that the character string must be correct and must not contain a space (" ") for example.  This function does not handle all possible syntax errors.
 *
 */
FunctionInfos getFunctionInfos(char string[])
{
	//********************
	const int FUNCTION_ID = 7;
	//********************

	FunctionInfos infos;
	const short int stringLength = strlen(string);

	char name[FUNCTION_NAME_SIZE];
	int i;
	for (i = 0; string[i] != '(' && i < stringLength; i++)
	{
		name[i] = string[i];
	}
	name[i] = '\0';
	strcpy(infos.name, name);

	char arg1[FUNCTION_ARGS_SIZE];
	int nbrOfOpenP = 0; //P for parentheses
	int nbrOfClosedP = 0;
	int j;
	if (strcmp(name, ADD) != 0 && strcmp(name, SUBTRACT) != 0 && strcmp(name, MULTIPLY) != 0 && strcmp(name, DIVIDE) != 0 && strcmp(name, POWL) != 0)
	{
		for (j = 0, ++i; !(string[i] == ')' && nbrOfOpenP == nbrOfClosedP) && i < stringLength; j++, i++)
		{
			arg1[j] = string[i];
			if (string[i] == '(')
			{
				nbrOfOpenP++;
			}
			else if (string[i] == ')')
			{
				nbrOfClosedP++;
			}
		}
		arg1[j] = '\0';
		strcpy(infos.arg1, arg1);

		strcpy(infos.arg2, "");

		//We make an additional verification
		if (stringLength == strlen(name) + strlen(arg1) + 2) //+2 because of '(' and ')'
		{
			return infos;
		}
		else
		{
			printError(FUNCTION_ID, 1);
			exit(EXIT_FAILURE);
			//strcpy(infos.name, "");
			//strcpy(infos.arg1, "");
			//return infos;
		}
	}
	else
	{
		for (j = 0, ++i; !(string[i] == ',' && nbrOfOpenP == nbrOfClosedP) && i < stringLength; j++, i++)
		{
			arg1[j] = string[i];
			if (string[i] == '(')
			{
				nbrOfOpenP++;
			}
			else if (string[i] == ')')
			{
				nbrOfClosedP++;
			}
		}
		arg1[j] = '\0';
		strcpy(infos.arg1, arg1);

		char arg2[FUNCTION_ARGS_SIZE];
		nbrOfOpenP = 0;
		nbrOfClosedP = 0;
		for (j = 0, ++i; !(string[i] == ')' && nbrOfOpenP == nbrOfClosedP) && i < stringLength; j++, i++)
		{
			arg2[j] = string[i];
			if (string[i] == '(')
			{
				nbrOfOpenP++;
			}
			else if (string[i] == ')')
			{
				nbrOfClosedP++;
			}
		}
		arg2[j] = '\0';
		strcpy(infos.arg2, arg2);

		//We make an additional verification
		if (stringLength == strlen(name) + strlen(arg1) + strlen(arg2) + 3) //+3 because of '(' , ',' and ')'
		{
			return infos;
		}
		else
		{
			printError(FUNCTION_ID, 2);
			exit(EXIT_FAILURE);
			//strcpy(infos.name, "");
			//strcpy(infos.arg1, "");
			//strcpy(infos.arg2, "");
			//return infos;
		}
	}
}

/**
 * We use this function to "operate" on a string ("string"), i.e. do the operation or operations it indicates. The principle is that from the function information returned by "getFunctionInfos(...)", we determine the function to be executed and its arguments.
 * Note that this function (the "operate(...)" function) is recursively called until the "toDecimal(...)" function is called (unless "toDecimal(...)" is directly called  on the first execution of "operate(...)").
 *Also note that for each return, we use the "detectNanInfErrors(...)" function to ensure that the return value of the operation functions is not "NaN" or "Inf".
 *
 */
long double operate(char string[])
{
	//********************
	const int FUNCTION_ID = 8;
	//********************

	FunctionInfos infos = getFunctionInfos(string);
	if (strcmp(infos.name, TO_DECIMAL) == 0)
	{
		return detectNanInfErrors(toDecimal(infos.arg1));
	}
	else if (strcmp(infos.name, ADD) == 0)
	{
		return detectNanInfErrors(add(operate(infos.arg1), operate(infos.arg2)));
	}
	else if (strcmp(infos.name, SUBTRACT) == 0)
	{
		return detectNanInfErrors(subtract(operate(infos.arg1), operate(infos.arg2)));
	}
	else if (strcmp(infos.name, MULTIPLY) == 0)
	{
		return detectNanInfErrors(multiply(operate(infos.arg1), operate(infos.arg2)));
	}
	else if (strcmp(infos.name, DIVIDE) == 0)
	{
		return detectNanInfErrors(divide(operate(infos.arg1), operate(infos.arg2)));
	}
	else if (strcmp(infos.name, PERCENTAGE) == 0)
	{
		return detectNanInfErrors(percentage(operate(infos.arg1)));
	}
	else if (strcmp(infos.name, FACTORIAL) == 0)
	{
		return detectNanInfErrors(factorial(operate(infos.arg1)));
	}
	else if (strcmp(infos.name, OPPOSITE) == 0)
	{
		return detectNanInfErrors(opposite(operate(infos.arg1)));
	}
	else if (strcmp(infos.name, ACOSL) == 0)
	{
		return detectNanInfErrors(acosl(operate(infos.arg1)));
	}
	else if (strcmp(infos.name, ASINL) == 0)
	{
		return detectNanInfErrors(asinl(operate(infos.arg1)));
	}
	else if (strcmp(infos.name, ATANL) == 0)
	{
		return detectNanInfErrors(atanl(operate(infos.arg1)));
	}
	else if (strcmp(infos.name, COSL) == 0)
	{
		return detectNanInfErrors(cosl(operate(infos.arg1)));
	}
	else if (strcmp(infos.name, SINL) == 0)
	{
		return detectNanInfErrors(sinl(operate(infos.arg1)));
	}
	else if (strcmp(infos.name, TANL) == 0)
	{
		return detectNanInfErrors(tanl(operate(infos.arg1)));
	}
	else if (strcmp(infos.name, EXPL) == 0)
	{
		return detectNanInfErrors(expl(operate(infos.arg1)));
	}
	else if (strcmp(infos.name, LOGL) == 0)
	{
		return detectNanInfErrors(logl(operate(infos.arg1)));
	}
	else if (strcmp(infos.name, LOG10L) == 0)
	{
		return detectNanInfErrors(log10l(operate(infos.arg1)));
	}
	else if (strcmp(infos.name, POWL) == 0)
	{
		return detectNanInfErrors(powl(operate(infos.arg1), operate(infos.arg2)));
	}
	else if (strcmp(infos.name, SQRTL) == 0)
	{
		return detectNanInfErrors(sqrtl(operate(infos.arg1)));
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return 0.0L;
	}
}

/**
 * This function allows you to detect NaN (not a number) and INF (Infinity) errors. It avoids the use of these constants during operations.
 *
 */
long double detectNanInfErrors(long double number)
{
	//********************
	const int FUNCTION_ID = 18;
	//********************

	if (isnanl(number))
	{
		printError(FUNCTION_ID, 1);
		fprintf(stderr, "The operand or the results is not a number\n\n");
		errorInExecution = true;
		//exit(EXIT_FAILURE);
		return 0.0L;
	}
	else if (isinfl(number))
	{
		printError(FUNCTION_ID, 2);
		fprintf(stderr, "The operand or the results is a infinity value\n\n");
		errorInExecution = true;
		//exit(EXIT_FAILURE);
		return 0.0L;
	}
	else
	{
		return number;
	}
}



//****************************************
//Linked list manipulation functions
//****************************************
/**
 * This function is used to initialize a list. It return an empty list.
 *
 */
List *initializeList()
{
	//********************
	const int FUNCTION_ID = 9;
	//********************

	List *list = (List *)malloc(sizeof(List));
	if (list != NULL)
	{
		list->nbrOfCreatedObjects = 0;
		list->first = NULL;
		return list;
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return NULL;
	}
}

/**
 * This function is used to obtain a new identifier from the number of objects inserted (created and inserted) in the list. It is used by the insertion functions.
 *
 */
short int getNewId(List *list)
{
	//********************
	const int FUNCTION_ID = 10;
	//********************

	if (list != NULL)
	{
		return ++list->nbrOfCreatedObjects;
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return 0;
	}
}

/**
 * This function is used to obtain the pointer to an operation object using its identifier.
 *
 */
OperationObject *getObject(List *list, short int id)
{
	//********************
	const int FUNCTION_ID = 11;
	//********************

	if (list != NULL)
	{
		OperationObject *object = list->first;
		while (object != NULL)
		{
			if (object->id == id)
			{
				return object;
			}
			else
			{
				object = object->next;
			}
		}
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//return NULL;//There is no object with the given identifier
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return NULL;
	}
}

/**
 * This function is used to insert a new object before another reference. The "newValue" character string provides the value of the object to insert.
 *
 */
void insertBefore(List *list, char newValue[], OperationObject *referenceObject)
{
	//********************
	const int FUNCTION_ID = 12;
	//********************

	if (list != NULL && referenceObject != NULL && strlen(newValue) < MAX_LENGTH_OF_NUMBER)
	{
		OperationObject *object = list->first;
		while (object != NULL)
		{
			if (object == referenceObject)
			{
				OperationObject *newObject = (OperationObject *)malloc(sizeof(OperationObject));
				if (newObject != NULL)
				{
					newObject->id = getNewId(list);
					strcpy(newObject->value, newValue);

					newObject->previous = referenceObject->previous;
					newObject->next = referenceObject;

					referenceObject->previous = newObject;
					if (newObject->previous == NULL)
					{
						list->first = newObject;
					}
					else
					{
						newObject->previous->next = newObject;
					}
					return; //All went well
				}
				else
				{
					printError(FUNCTION_ID, 3);
					exit(EXIT_FAILURE);
					//return;
				}
			}
			else
			{
				object = object->next;
			}
		}
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//return;//The reference object is not found
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}
}

/**
 * This function is used to insert a new object after another reference. The "newValue" character string provides the value of the object to insert.
 *
 */
void insertAfter(List *list, char newValue[], OperationObject *referenceObject)
{
	//********************
	const int FUNCTION_ID = 13;
	//********************

	if (list != NULL && referenceObject != NULL && strlen(newValue) < MAX_LENGTH_OF_NUMBER)
	{
		OperationObject *object = list->first;
		while (object != NULL)
		{
			if (object == referenceObject)
			{
				OperationObject *newObject = (OperationObject *)malloc(sizeof(OperationObject));
				if (newObject != NULL)
				{
					newObject->id = getNewId(list);
					strcpy(newObject->value, newValue);

					newObject->previous = referenceObject;
					newObject->next = referenceObject->next;

					referenceObject->next = newObject;
					if (newObject->next == NULL)
					{
						return;
					}
					else
					{
						newObject->next->previous = newObject;
						return;
					}
				}
				else
				{
					printError(FUNCTION_ID, 3);
					exit(EXIT_FAILURE);
					//return;
				}
			}
			else
			{
				object = object->next;
			}
		}
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//return;//The reference object is not found
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}
}

/**
 * This function is used to insert a new object at the end of the list.  The "newValue" character string provides the value of the object to insert.
 * Note that this function is used when one wants to obtain the list which corresponds to a given character string.
 *
 */
void insertAtTheEnd(List *list, char newValue[])
{
	//********************
	const int FUNCTION_ID = 14;
	//********************

	if (list != NULL && strlen(newValue) < MAX_LENGTH_OF_NUMBER)
	{
		OperationObject *newObject = (OperationObject *)malloc(sizeof(OperationObject));
		if (newObject != NULL)
		{
			newObject->id = getNewId(list);
			strcpy(newObject->value, newValue);
			newObject->next = NULL;

			if (list->first == NULL)
			{
				newObject->previous = NULL;
				list->first = newObject;
			}
			else
			{
				OperationObject *lastObject = list->first;
				while (lastObject->next != NULL)
				{
					lastObject = lastObject->next;
				}

				newObject->previous = lastObject;
				lastObject->next = newObject;
			}
			return; //All went well
		}
		else
		{
			printError(FUNCTION_ID, 2);
			exit(EXIT_FAILURE);
			//return;
		}
	}
	else
	{
		if (strlen(newValue) >= MAX_LENGTH_OF_NUMBER)
		{
			printError(FUNCTION_ID, 1);
			fprintf(stderr, "Operation Object too long\n\n");
			errorInInterpretation = true;
			//exit(EXIT_FAILURE);
			return;
		}
		else
		{
			printError(FUNCTION_ID, 1);
			exit(EXIT_FAILURE);
			//return;
		}
	}
}

/**
 * This function is used to delete an object from the list.
 *
 */
void deleteFromList(List *list, OperationObject *objectToDelete)
{
	//********************
	const int FUNCTION_ID = 15;
	//********************

	if (list != NULL && objectToDelete != NULL)
	{
		OperationObject *object = list->first;
		while (object != NULL)
		{
			if (object == objectToDelete)
			{
				if (objectToDelete->previous != NULL)
				{
					objectToDelete->previous->next = objectToDelete->next;
				}
				else
				{
					list->first = objectToDelete->next;
				}
				if (objectToDelete->next != NULL)
				{
					objectToDelete->next->previous = objectToDelete->previous;
				}
				free(objectToDelete);
				return;
			}
			else
			{
				object = object->next;
			}
		}
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//return;//The object to delete is not found
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}
}

/**
 * This function is used to remove all objects from a list. After that the list will be empty.
 *
 */
void deleteAllFromList(List *list)
{
	//********************
	const int FUNCTION_ID = 16;
	//********************

	if (list != NULL)
	{
		while (list->first != NULL)
		{
			deleteFromList(list, list->first);
		}
		return;
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}
}

/**
 * This function is used to display a list.  It displays the contents of the list by browsing it from left to right then from right to left. 
 *
 */
void printList(List *list)
{
	//********************
	const int FUNCTION_ID = 17;
	//********************

	if (list != NULL)
	{
		if (list->first == NULL)
		{
			printf("\nThe list is empty\n");
			return;
		}
		else
		{
			OperationObject *object = list->first;
			OperationObject *lastObject;
			printf("\nLeft to right : NULL->");
			do
			{
				printf("[\"%s\"][%d]->", object->value, object->id);
				lastObject = object;
				object = object->next;
			} while (object != NULL);
			printf("NULL");
			object = lastObject;
			printf("\nRight to left : NULL->");
			do
			{
				printf("[\"%s\"][%d]->", object->value, object->id);
				object = object->previous;
			} while (object != NULL);
			printf("NULL\n");
			return;
		}
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}
}

/**
 * This function is used to obtain the character string corresponding to a list. It reads the value of the "OperationObject" contained in the list one by one.  This reading is done from left to right and it is the character string obtained which is returned.
 *
 */
char *listToString(List *list)
{
	//********************
	const int FUNCTION_ID = 25;
	//********************

	if (list != NULL)
	{
		OperationObject *object = list->first;
		char results[FUNCTION_ARGS_SIZE];
		strcpy(results, "");
		while (object != NULL)
		{
			strcat(results, object->value);
			object = object->next;
		}
		char *finalResults = results;
		return finalResults;
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return NULL;
	}
}

/**
 * This function allow to check if an "OperationObject" is included in a given list.
 *
 */
bool isIncluded(List *list, OperationObject *soughtObject)
{
	//********************
	const int FUNCTION_ID = 21;
	//********************

	if (list != NULL && soughtObject != NULL)
	{
		OperationObject *currentObject = list->first;
		while (currentObject != NULL)
		{
			if (currentObject == soughtObject)
			{
				return true;
			}
			else
			{
				currentObject = currentObject->next;
			}
		}
		return false;
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}
}

/**
 * This function allow to check if an "OperationObject" is an external function.
 *
 */
bool isExternalFunction(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 22;
	//********************

	if (object != NULL)
	{
		if (strcmp(object->value, E_SQRT) == 0 || strcmp(object->value, E_SIN) == 0 || strcmp(object->value, E_COS) == 0 || strcmp(object->value, E_TAN) == 0 || strcmp(object->value, E_LN) == 0 ||
			strcmp(object->value, E_LOG) == 0 || strcmp(object->value, E_ASIN) == 0 || strcmp(object->value, E_ACOS) == 0 || strcmp(object->value, E_ATAN) == 0 || strcmp(object->value, E_EXP) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}
}

/**
 * This function allow to check if an "OperationObject" is an internal function.
 *
 */
bool isInternalFunction(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 40;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	if (strcmp(object->value, ACOSL) == 0 || strcmp(object->value, ASINL) == 0 || strcmp(object->value, ATANL) == 0 || strcmp(object->value, COSL) == 0 || strcmp(object->value, SINL) == 0 ||
		strcmp(object->value, TANL) == 0 || strcmp(object->value, EXPL) == 0 || strcmp(object->value, LOGL) == 0 || strcmp(object->value, LOG10L) == 0 || strcmp(object->value, POWL) == 0 ||
		strcmp(object->value, SQRTL) == 0 || strcmp(object->value, ADD) == 0 || strcmp(object->value, SUBTRACT) == 0 || strcmp(object->value, MULTIPLY) == 0 || strcmp(object->value, DIVIDE) == 0 ||
		strcmp(object->value, PERCENTAGE) == 0 || strcmp(object->value, FACTORIAL) == 0 || strcmp(object->value, TO_DECIMAL) == 0 || strcmp(object->value, OPPOSITE) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * This function allow to check if an "OperationObject" is a function.
 *
 */
bool isFunction(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 41;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	if (isExternalFunction(object) || isInternalFunction(object))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * This function allow to check if an "OperationObject" is an operator.
 *
 */
bool isOperator(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 19;
	//********************

	if (object != NULL)
	{
		if (strcmp(object->value, OP_DIVIDE) == 0 || strcmp(object->value, OP_TIMES) == 0 || strcmp(object->value, OP_U_MINUS) == 0 || strcmp(object->value, OP_B_MINUS) == 0 ||
			strcmp(object->value, OP_PLUS) == 0 || strcmp(object->value, OP_PERCENT) == 0 || strcmp(object->value, OP_FACTORIAL) == 0 || strcmp(object->value, OP_POWER) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}
}

/**
 * This function allow to check if an "OperationObject" is a constant.
 *
 */
bool isConstant(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 33;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	if (strcmp(object->value, PI) == 0 || strcmp(object->value, E) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * This function allow to check if an "OperationObject" is a number.
 * Note that a number can only contain numbers and point and it must be a positive number.
 *
 */
bool isNumber(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 34;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	char const *literal = object->value;
	const short int length = strlen(literal);
	if (length == 0)
	{
		return false;
	}

	bool strangeCharacter = false;
	short int nbrOfDigit = 0;
	short int nbrOfPoint = 0;
	short int pointPosition;
	int i;
	for (i = 0; i < length; i++)
	{
		if (isdigit(literal[i]))
		{
			nbrOfDigit++;
		}
		else if (literal[i] == '.')
		{
			nbrOfPoint++;
			pointPosition = i;
		}
		else
		{
			strangeCharacter = true;
			break;
		}
	}
	if (strangeCharacter || nbrOfDigit < 1 || nbrOfPoint > 1)
	{
		return false;
	}

	bool wrongPosition = false;
	if (nbrOfPoint == 1)
	{
		if (pointPosition == 0 || pointPosition == length - 1)
		{
			wrongPosition = true;
		}
	}

	if (wrongPosition)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/**
 * This function is used to determine whether an "OperationObject" is a category 1 operator or not.
 * Note: For parsing the operators, I have divided them into four categories. This is not to be confused with operator groups used for operator sorting.
 *
 */
bool isOperatorCategory1(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 49;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	if (strcmp(object->value, OP_DIVIDE) == 0 || strcmp(object->value, OP_TIMES) == 0 || strcmp(object->value, OP_POWER) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * This function is used to determine whether an "OperationObject" is a category 2 operator or not.
 * Note: For parsing the operators, I have divided them into four categories. This is not to be confused with operator groups used for operator sorting.
 *
 */
bool isOperatorCategory2(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 50;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	if (strcmp(object->value, OP_B_MINUS) == 0 || strcmp(object->value, OP_PLUS) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * This function is used to determine whether an "OperationObject" is a category 3 operator or not.
 * Note: For parsing the operators, I have divided them into four categories. This is not to be confused with operator groups used for operator sorting.
 *
 */
bool isOperatorCategory3(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 51;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	if (strcmp(object->value, OP_U_MINUS) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * This function is used to determine whether an "OperationObject" is a category 4 operator or not.
 * Note: For parsing the operators, I have divided them into four categories. This is not to be confused with operator groups used for operator sorting.
 *
 */
bool isOperatorCategory4(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 52;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	if (strcmp(object->value, OP_PERCENT) == 0 || strcmp(object->value, OP_FACTORIAL) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * This function is used to determine whether an "OperationObject" is a left separator or not.
 *
 */
bool isLeftSeparator(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 53;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	if (strcmp(object->value, "(") == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * This function is used to determine whether an "OperationObject" is a right separator or not.
 *
 */
bool isRightSeparator(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 54;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	if (strcmp(object->value, ")") == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * This function is used to determine whether an "OperationObject" is a separator or not.
 *
 */
bool isSeparator(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 55;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	if (strcmp(object->value, "(") == 0 || strcmp(object->value, ")") == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * This function can detect operators between two "OperationObject". It returns a structure object containing the number of operators and a table of operators.
 *
 */
Operators identifyOperatorsBetween(List *list, OperationObject *firstObject, OperationObject *secondObject)
{
	//********************
	const int FUNCTION_ID = 23;
	//********************

	if (list != NULL && firstObject != NULL && secondObject != NULL)
	{
		Block *associatedBlock = identifyBlockFrom(list, firstObject, left_to_right);
		if (associatedBlock != NULL && associatedBlock->end == secondObject)
		{
			OperationObject *currentObject;
			if (strcmp(firstObject->value, "(") == 0) //The block begins with an open parenthesis.
			{
				currentObject = firstObject->next;
			}
			else if (isFunction(firstObject)) //The block begins with a name of function.
			{
				currentObject = firstObject->next->next;
			}
			else //The block is a number.
			{
				Operators results;
				results.nbrOfOperators = 0;
				results.operators = NULL;
				return results;
			}

			short int nbrOfOperators = 0;
			while (currentObject != NULL && currentObject != secondObject) //This first browse is to count the number of operators.
			{
				Block *possibleBlock = identifyBlockFrom(list, currentObject, left_to_right);
				if (possibleBlock != NULL)
				{
					currentObject = possibleBlock->end->next;
				}
				else if (isOperator(currentObject))
				{
					nbrOfOperators++;
					currentObject = currentObject->next;
				}
				else
				{
					printError(FUNCTION_ID, 3);
					exit(EXIT_FAILURE);
					//Operators results;
					//results.nbrOfOperators = 0;
					//results.operators = NULL;
					//return results;
				}
			}

			if (currentObject == secondObject)
			{
				if (nbrOfOperators == 0)
				{
					Operators results;
					results.nbrOfOperators = 0;
					results.operators = NULL;
					return results;
				}
				else
				{
					if (strcmp(firstObject->value, "(") == 0) //The block begins with an open parenthesis.
					{
						currentObject = firstObject->next;
					}
					else //The block begins with a name of external function. Note that the case where the block is a number is already eliminated.
					{
						currentObject = firstObject->next->next;
					}

					Operators results;
					results.nbrOfOperators = nbrOfOperators;
					results.operators = (OperationObject **)malloc(nbrOfOperators * sizeof(OperationObject));
					if (results.operators == NULL)
					{
						printError(FUNCTION_ID, 5);
						exit(EXIT_FAILURE);
						//Operators results;
						//results.nbrOfOperators = 0;
						//results.operators = NULL;
						//return results;
					}

					short int ind = 0;

					while (currentObject != secondObject) //This second browse is for operators registration. Note that we make less of controls at this step.
					{
						Block *possibleBlock = identifyBlockFrom(list, currentObject, left_to_right);
						if (possibleBlock != NULL)
						{
							currentObject = possibleBlock->end->next;
						}
						else if (isOperator(currentObject))
						{
							results.operators[ind] = currentObject;
							ind++;
							currentObject = currentObject->next;
						}
					}

					return results; //All went well
				}
			}
			else
			{
				printError(FUNCTION_ID, 4);
				exit(EXIT_FAILURE);
				//Operators results;
				//results.nbrOfOperators = 0;
				//results.operators = NULL;
				//return results;
			}
		}
		else
		{
			printError(FUNCTION_ID, 2);
			exit(EXIT_FAILURE);
			//Operators results;
			//results.nbrOfOperators = 0;
			//results.operators = NULL;
			//return results;
		}
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//Operators results;
		//results.nbrOfOperators = 0;
		//results.operators = NULL;
		//return results;
	}
}

/**
 * This function checks if there is a block that starts with a given "OperationObject".  If the given "OperationObject" is the beginning or the end of a block (depending on the direction indicated), it tries to detect the end(or the beginning) of this block.
 *
 */
Block *identifyBlockFrom(List *list, OperationObject *startObject, Direction direction)
{
	//********************
	const int FUNCTION_ID = 20;
	//********************

	if (list != NULL && startObject != NULL && (direction == left_to_right || direction == right_to_left))
	{
		if (isIncluded(list, startObject))
		{
			if (isNumber(startObject)) //The start object is a number.
			{
				Block *block = (Block *)malloc(sizeof(Block));
				if (block == NULL)
				{
					printError(FUNCTION_ID, 8);
					exit(EXIT_FAILURE);
					//return NULL;
				}
				block->beginning = startObject;
				block->end = startObject;
				block->nbrOfOperators = 0;
				block->operators = NULL;
				block->nbrOfSubBlocks = 0;
				block->subBlocks = NULL;

				return block;
			}
			else
			{
				OperationObject *currentObject = startObject;
				if (direction == left_to_right)
				{
					if (isFunction(currentObject))
					{
						currentObject = currentObject->next;
					}
					else if (strcmp(currentObject->value, "(") == 0)
					{
					}
					else
					{
						return NULL;
					}

					if (currentObject != NULL) //This condition check is necessary only if "currentObject" = "startObject->next"
					{
						short int nbrOfOpenP = 0; //P for parentheses
						short int nbrOfClosedP = 0;
						if (strcmp(currentObject->value, "(") == 0)
						{
							nbrOfOpenP++;
							currentObject = currentObject->next;
							while (currentObject != NULL && nbrOfOpenP != nbrOfClosedP)
							{
								if (strcmp(currentObject->value, "(") == 0)
								{
									nbrOfOpenP++;
								}
								else if (strcmp(currentObject->value, ")") == 0)
								{
									nbrOfClosedP++;
								}
								if (nbrOfOpenP != nbrOfClosedP)
								{
									currentObject = currentObject->next;
								}
							}

							if (nbrOfOpenP == nbrOfClosedP) //Finally the block is detected
							{
								Block *block = (Block *)malloc(sizeof(Block));
								if (block == NULL)
								{
									printError(FUNCTION_ID, 9);
									exit(EXIT_FAILURE);
									//return NULL;
								}

								block->beginning = startObject;
								block->end = currentObject;
								//Note that we do not initialize all fields.
								return block;
							}
							else //We reached the end of list but the end of block is not detected
							{
								printError(FUNCTION_ID, 6);
								exit(EXIT_FAILURE);
								//return NULL;
							}
						}
						else
						{
							printError(FUNCTION_ID, 5);
							exit(EXIT_FAILURE);
							//return NULL;
						}
					}
					else
					{
						printError(FUNCTION_ID, 4);
						exit(EXIT_FAILURE);
						//return NULL;
					}
				}
				else if (direction == right_to_left)
				{
					if (strcmp(currentObject->value, ")") == 0)
					{
					}
					else
					{
						return NULL;
					}

					short int nbrOfOpenP = 0; //P for parentheses
					short int nbrOfClosedP = 0;
					nbrOfClosedP++;
					currentObject = currentObject->previous;
					while (currentObject != NULL && nbrOfOpenP != nbrOfClosedP)
					{
						if (strcmp(currentObject->value, "(") == 0)
						{
							nbrOfOpenP++;
						}
						else if (strcmp(currentObject->value, ")") == 0)
						{
							nbrOfClosedP++;
						}
						if (nbrOfOpenP != nbrOfClosedP)
						{
							currentObject = currentObject->previous;
						}
					}

					if (nbrOfOpenP == nbrOfClosedP)
					{
						if (currentObject->previous != NULL)
						{
							if (isFunction(currentObject->previous))
							{
								currentObject = currentObject->previous;
							}
						}

						Block *block = (Block *)malloc(sizeof(Block));
						if (block == NULL)
						{
							printError(FUNCTION_ID, 10);
							exit(EXIT_FAILURE);
							//return NULL;
						}

						block->beginning = currentObject;
						block->end = startObject;
						//Note that we do not initialize all fields.
						return block;
					}
					else //We reached the beginning of the list, but the beginning of the block is not detected
					{
						printError(FUNCTION_ID, 7);
						exit(EXIT_FAILURE);
						//return NULL;
					}
				}
				else
				{
					printError(FUNCTION_ID, 3);
					exit(EXIT_FAILURE);
					//return NULL;
				}
			}
		}
		else
		{
			printError(FUNCTION_ID, 2);
			exit(EXIT_FAILURE);
			//return NULL;
		}
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return NULL;
	}
}

/**
 * This function makes it possible to detect blocks between two "OperationObject". It returns a structure object containing the number of blocks and a block table.
 *
 */
Blocks identifyBlocksBetween(List *list, OperationObject *firstObject, OperationObject *secondObject)
{
	//********************
	const int FUNCTION_ID = 24;
	//********************

	if (list != NULL && firstObject != NULL && secondObject != NULL)
	{
		Block *associatedBlock = identifyBlockFrom(list, firstObject, left_to_right);
		if (associatedBlock != NULL && associatedBlock->end == secondObject)
		{
			OperationObject *currentObject;
			if (strcmp(firstObject->value, "(") == 0) //The block begins with an open parenthesis.
			{
				currentObject = firstObject->next;
			}
			else if (isFunction(firstObject)) //The block begins with a name of function.
			{
				currentObject = firstObject->next->next;
			}
			else //The block is a number.
			{
				Blocks results;
				results.nbrOfBlocks = 0;
				results.blocks = NULL;
				return results;
			}

			short int nbrOfBlocks = 0;
			while (currentObject != NULL && currentObject != secondObject) //This first browse is to count the number of blocks.
			{
				Block *possibleBlock = identifyBlockFrom(list, currentObject, left_to_right);
				if (possibleBlock != NULL)
				{
					nbrOfBlocks++;
					currentObject = possibleBlock->end->next;
				}
				else if (isOperator(currentObject))
				{
					currentObject = currentObject->next;
				}
				else
				{
					printError(FUNCTION_ID, 3);
					exit(EXIT_FAILURE);
					//Blocks results;
					//results.nbrOfBlocks = 0;
					//results.blocks = NULL;
					//return results;
				}
			}

			if (currentObject == secondObject)
			{
				if (nbrOfBlocks == 0)
				{
					Blocks results;
					results.nbrOfBlocks = 0;
					results.blocks = NULL;
					return results;
				}
				else
				{
					if (strcmp(firstObject->value, "(") == 0) //The block begins with an open parenthesis.
					{
						currentObject = firstObject->next;
					}
					else //The block begins with a name of function. Note that the case where the block is a number is already eliminated.
					{
						currentObject = firstObject->next->next;
					}

					Blocks results;
					results.nbrOfBlocks = nbrOfBlocks;
					results.blocks = (Block **)malloc(nbrOfBlocks * sizeof(Block));
					if (results.blocks == NULL)
					{
						printError(FUNCTION_ID, 5);
						exit(EXIT_FAILURE);
						//Blocks results;
						//results.nbrOfBlocks = 0;
						//results.blocks = NULL;
						//return results;
					}

					short int ind = 0;

					while (currentObject != secondObject) //This second browse is for blocks registration. Note that we make less of controls at this step.
					{
						Block *possibleBlock = identifyBlockFrom(list, currentObject, left_to_right);
						if (possibleBlock != NULL)
						{
							results.blocks[ind] = possibleBlock;
							ind++;
							currentObject = possibleBlock->end->next;
						}
						else if (isOperator(currentObject))
						{
							currentObject = currentObject->next;
						}
					}

					return results; //All went well
				}
			}
			else
			{
				printError(FUNCTION_ID, 4);
				exit(EXIT_FAILURE);
				//Blocks results;
				//results.nbrOfBlocks = 0;
				//results.blocks = NULL;
				//return results;
			}
		}
		else
		{
			printError(FUNCTION_ID, 2);
			exit(EXIT_FAILURE);
			//Blocks results;
			//results.nbrOfBlocks = 0;
			//results.blocks = NULL;
			//return results;
		}
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//Blocks results;
		//results.nbrOfBlocks = 0;
		//results.blocks = NULL;
		//return results;
	}
}

/**
 * This function allow to get the name of internal function that match with an operator or an external function.
 *
 */
char *getInternalFunction(char name[])
{
	//********************
	const int FUNCTION_ID = 38;
	//********************

	//OPERATORS
	if (strcmp(name, OP_DIVIDE) == 0)
	{
		return DIVIDE;
	}
	else if (strcmp(name, OP_TIMES) == 0)
	{
		return MULTIPLY;
	}
	else if (strcmp(name, OP_U_MINUS) == 0)
	{
		return OPPOSITE;
	}
	else if (strcmp(name, OP_B_MINUS) == 0)
	{
		return SUBTRACT;
	}
	else if (strcmp(name, OP_PLUS) == 0)
	{
		return ADD;
	}
	else if (strcmp(name, OP_PERCENT) == 0)
	{
		return PERCENTAGE;
	}
	else if (strcmp(name, OP_FACTORIAL) == 0)
	{
		return FACTORIAL;
	}
	else if (strcmp(name, OP_POWER) == 0)
	{
		return POWL;
	}

	//FUNCTIONS
	if (strcmp(name, E_SQRT) == 0)
	{
		return SQRTL;
	}
	else if (strcmp(name, E_SIN) == 0)
	{
		return SINL;
	}
	else if (strcmp(name, E_COS) == 0)
	{
		return COSL;
	}
	else if (strcmp(name, E_TAN) == 0)
	{
		return TANL;
	}
	else if (strcmp(name, E_LN) == 0)
	{
		return LOGL;
	}
	else if (strcmp(name, E_LOG) == 0)
	{
		return LOG10L;
	}
	else if (strcmp(name, E_ASIN) == 0)
	{
		return ASINL;
	}
	else if (strcmp(name, E_ACOS) == 0)
	{
		return ACOSL;
	}
	else if (strcmp(name, E_ATAN) == 0)
	{
		return ATANL;
	}
	else if (strcmp(name, E_EXP) == 0)
	{
		return EXPL;
	}
	else
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return "";
	}
}

/**
 * This function makes it possible to manage the constants. Currently, all the values of the constants can be obtained using one of the external functions.
 *
 */
void manageConstant(List *list, OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 35;
	//********************

	if (list == NULL || object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	if (!isIncluded(list, object) || !isConstant(object))
	{
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//return;
	}

	//We will change "pi" constant by "(acos(-1))".
	if (strcmp(object->value, PI) == 0)
	{
		insertAfter(list, ")", object);
		insertAfter(list, ")", object);
		insertAfter(list, "1", object);
		insertAfter(list, OP_U_MINUS, object);
		insertAfter(list, "(", object);
		insertAfter(list, E_ACOS, object);
		insertAfter(list, "(", object);
		deleteFromList(list, object);
		return;
	}

	//We will change "e" constant by "(exp(1))".
	if (strcmp(object->value, E) == 0)
	{
		insertAfter(list, ")", object);
		insertAfter(list, ")", object);
		insertAfter(list, "1", object);
		insertAfter(list, "(", object);
		insertAfter(list, E_EXP, object);
		insertAfter(list, "(", object);
		deleteFromList(list, object);
		return;
	}
}

/**
 * This function allow to manage the numbers.
 *
 */
void manageNumber(List *list, OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 36;
	//********************

	if (list == NULL || object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	if (!isIncluded(list, object) || !isNumber(object))
	{
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//return;
	}

	//We will include the number between "toDecimal()" function.
	insertAfter(list, ")", object);
	insertBefore(list, "(", object);
	insertBefore(list, TO_DECIMAL, object->previous);
	return;
}

/**
 * This function is used to manage operators. It treats binary and unary operators separately. As far as unary operators are concerned, it handles both possibilities that exist.
 *
 */
void manageOperator(List *list, OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 37;
	//********************

	if (list == NULL || object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	if (!isIncluded(list, object) || !isOperator(object))
	{
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//return;
	}

	if (strcmp(object->value, OP_DIVIDE) == 0 || strcmp(object->value, OP_TIMES) == 0 || strcmp(object->value, OP_B_MINUS) == 0 || strcmp(object->value, OP_PLUS) == 0 || strcmp(object->value, OP_POWER) == 0)
	{
		//Example "a+b" can become "add(a,b)".
		Block *a = identifyBlockFrom(list, object->previous, right_to_left);
		Block *b = identifyBlockFrom(list, object->next, left_to_right);
		if (a == NULL || b == NULL)
		{
			printError(FUNCTION_ID, 3);
			exit(EXIT_FAILURE);
			//return;
		}

		insertAfter(list, ")", b->end);
		insertBefore(list, getInternalFunction(object->value), a->beginning);
		insertBefore(list, "(", a->beginning);
		strcpy(object->value, ",");
		return;
	}
	else if (strcmp(object->value, OP_PERCENT) == 0 || strcmp(object->value, OP_FACTORIAL) == 0)
	{
		//Example "a!" can become "fact(a)".
		Block *a = identifyBlockFrom(list, object->previous, right_to_left);
		if (a == NULL)
		{
			printError(FUNCTION_ID, 4);
			exit(EXIT_FAILURE);
			//return;
		}

		insertBefore(list, getInternalFunction(object->value), a->beginning);
		insertBefore(list, "(", a->beginning);
		strcpy(object->value, ")");
		return;
	}
	else if (strcmp(object->value, OP_U_MINUS) == 0)
	{
		//Example "-a" can become "opp(a)".
		Block *a = identifyBlockFrom(list, object->next, left_to_right);
		if (a == NULL)
		{
			printError(FUNCTION_ID, 5);
			exit(EXIT_FAILURE);
			//return;
		}

		insertAfter(list, ")", a->end);
		strcpy(object->value, getInternalFunction(object->value));
		insertBefore(list, "(", a->beginning);
		return;
	}
}

/**
 * This function is used to manage external functions.  It changes each outer function to its corresponding inner function.
 *
 */
void manageExternalFunction(List *list, OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 39;
	//********************

	if (list == NULL || object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	if (!isIncluded(list, object) || !isExternalFunction(object))
	{
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//return;
	}

	//Currently all functions take only one parameter.  It is therefore sufficient to change the name of the external function by its correspondence among the internal functions.
	strcpy(object->value, getInternalFunction(object->value));
}

/**
 * This function allow to delete the additional parentheses contained in a list. The additional parentheses are those who aren't associated with an external function.
 * Note that this function can be called only after the management of constants, operators, external functions and numbers.
 *
 */
void manageAdditionalParentheses(List *list)
{
	//********************
	const int FUNCTION_ID = 45;
	//********************

	if (list == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	OperationObject *listBeginning = list->first;
	OperationObject *listEnd;

	OperationObject *currentObject = listBeginning;
	while (currentObject->next != NULL)
	{
		currentObject = currentObject->next;
	}
	listEnd = currentObject;

	Block *associatedBlock = identifyBlockFrom(list, listBeginning, left_to_right);
	if (associatedBlock == NULL || associatedBlock->end != listEnd || strcmp(associatedBlock->beginning->value, "(") != 0)
	{
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//return;
	}

	OperationObject *pBeginning; //p for parentheses
	OperationObject *pEnd;

	Block *temporaryBlock;

	currentObject = listBeginning;
	while (currentObject->next != NULL)
	{
		if (strcmp(currentObject->value, "(") == 0 && (currentObject->previous == NULL || !isInternalFunction(currentObject->previous)))
		{
			temporaryBlock = identifyBlockFrom(list, currentObject, left_to_right);
			pBeginning = currentObject;
			pEnd = temporaryBlock->end;

			currentObject = currentObject->next;
			deleteFromList(list, pBeginning);
			deleteFromList(list, pEnd);
		}
		else
		{
			currentObject = currentObject->next;
		}
	}
	return;
}



//****************************************
//Tree manipulation functions
//****************************************
/**
 * This function is used to initialize a tree. It returns the pointer to an empty tree.
 * Note that this function is not written to empty trees. To empty a tree, use the "deleteAllFromTree(...)" function instead.
 *
 */
Tree *initializeTree()
{
	//********************
	const int FUNCTION_ID = 26;
	//********************

	Tree *tree = (Tree *)malloc(sizeof(Tree));
	if (tree == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return NULL;
	}

	tree->root = NULL;
	tree->associatedList = NULL;
	return tree;
}

/**
 * This function makes it possible to fill a block. It defines the remaining fields of this block that are "nbrOfOperators", "operators", "nbrOfSubBlocks" and "subBlocks".
 * Note that the fields "beginning" and "end" of the block must be defined before the function call.
 *
 */
void fillBlock(Block *block, List *list)
{
	//********************
	const int FUNCTION_ID = 27;
	//********************

	if (block == NULL || list == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	//Note that it's not necessary to check if the beginning and the end of block is valid because that checking will be do in "identifyOperatorsBetween(...)" and "identifyBlocksBetween(...)" functions.
	Operators operators = identifyOperatorsBetween(list, block->beginning, block->end);
	block->nbrOfOperators = operators.nbrOfOperators;
	block->operators = operators.operators;

	Blocks subBlocks = identifyBlocksBetween(list, block->beginning, block->end);
	block->nbrOfSubBlocks = subBlocks.nbrOfBlocks;
	block->subBlocks = subBlocks.blocks;

	if (block->nbrOfSubBlocks > 0)
	{
		int i;
		for (i = 0; i < block->nbrOfSubBlocks; i++)
		{
			fillBlock(block->subBlocks[i], list);
		}
	}
	return;
}

/**
 * This function is used to fill a tree.  It defines the tree blocks and their fields.  To start, it does some checking and then calls the "fillBlock(...)" function to fill in the root block.  
 * Note that the given list must form a valid block that starts with "(" and ends with ")". 
 * Also we define at the same time the list associated with the tree.
 *
 */
void fillTree(Tree *tree, List *list)
{
	//********************
	const int FUNCTION_ID = 28;
	//********************

	if (tree == NULL || list == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	if (tree->root != NULL || tree->associatedList != NULL || list->first == NULL)
	{
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//return;
	}

	OperationObject *listBeginning = list->first;
	OperationObject *listEnd;

	OperationObject *object = listBeginning;
	while (object->next != NULL)
	{
		object = object->next;
	}
	listEnd = object;

	Block *rootBlock = identifyBlockFrom(list, listBeginning, left_to_right);
	if (rootBlock == NULL)
	{
		printError(FUNCTION_ID, 3);
		exit(EXIT_FAILURE);
		//return;
	}

	if (strcmp(rootBlock->beginning->value, "(") != 0 || rootBlock->end != listEnd || strcmp(rootBlock->end->value, ")") != 0)
	{
		printError(FUNCTION_ID, 4);
		exit(EXIT_FAILURE);
		//return;
	}

	fillBlock(rootBlock, list);
	tree->root = rootBlock;
	tree->associatedList = list;
	return;
}

/**
 * This function is used to delete a block.  It frees the memory occupied by this block.
 *
 */
void deleteBlock(Block *block)
{
	//********************
	const int FUNCTION_ID = 29;
	//********************

	if (block == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	if (block->nbrOfSubBlocks > 0)
	{
		int i;
		for (i = 0; i < block->nbrOfSubBlocks; ++i)
		{
			deleteBlock(block->subBlocks[i]);
		}
	}

	block = NULL;
	free(block); //We assume that all "Block" type variable was dynamically created.
	return;
}

/**
 * This function is used to delete the contain of a tree. It frees the memory occupied by the tree and change it root to "NULL". It also define the associated list on "NULL".
 *
 */
void deleteAllFromTree(Tree *tree)
{
	//********************
	const int FUNCTION_ID = 30;
	//********************

	if (tree == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	if (tree->root == NULL && tree->associatedList == NULL)
	{
		return;
	}
	else
	{
		deleteBlock(tree->root);
		tree->root = NULL;
		tree->associatedList = NULL;
		return;
	}
}

/**
 * This function is used to get the characters string matching with a block.
 * Note that its return value don't depend on the block's list but on the informations contained in the block and its subblocks.
 *
 */
char *blockToString(Block *block)
{
	//********************
	const int FUNCTION_ID = 31;
	//********************

	if (block == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//char *results = "";
		//return results;
	}

	char results[FUNCTION_ARGS_SIZE];
	strcpy(results, "");
	if (isFunction(block->beginning))
	{
		strcat(results, block->beginning->value);
		strcat(results, "(");
	}
	else if (strcmp(block->beginning->value, "(") == 0)
	{
		strcat(results, "(");
	}
	else //The block is a number
	{
		strcat(results, block->beginning->value);
		char *finalResults = results;
		return finalResults;
	}

	if (block->nbrOfSubBlocks < 1)
	{
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//char *results = "";
		//return results;
	}

	int i;
	for (i = 0; i < block->nbrOfSubBlocks; i++)
	{
		strcat(results, blockToString(block->subBlocks[i]));
		strcat(results, " ");
	}

	if (block->nbrOfOperators > 0)
	{
		for (i = 0; i < block->nbrOfOperators; i++)
		{
			strcat(results, block->operators[i]->value);
			strcat(results, " ");
		}
	}

	deleteFromString(results, FUNCTION_ARGS_SIZE, strlen(results) - 1, 1);
	strcat(results, ")");
	char *finalResults = results;
	return finalResults;
}

/**
 * This function is used to get the characters string matching with a tree.
 * Note that its return value don't depend on the tree's list but on the informations contained in the tree's root block and its subblocks.
 *
 */
char *treeToString(Tree *tree)
{
	//********************
	const int FUNCTION_ID = 32;
	//********************

	if (tree == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//char *results = "";
		//return results;
	}

	if (tree->root == NULL) //The tree is empty
	{
		return "The tree is empty";
	}
	else
	{
		return blockToString(tree->root);
	}
}

/**
 * This function is used to sort the operators contained in an array of operators.
 *
 * This is the list of operators classified in order of decreasing priority. Operators on the same line have the same level of priority.
 *    ! %           -->
 *    ^ u-          <--
 *    / *           -->
 *    + b-          -->
 * To sort the operators of an expression, we choose to group them first by group (group of operators of the same level).  The operators are thus grouped into four (4) groups.
 * Then each group is evaluated by following the direction of evaluation associated with it.  During the evaluation phase, we obviously start with the highest priority group to reach the lowest priority group.
 *
 */
void sortOperators(OperationObject **operators, int nbrOfOperators)
{
	//********************
	const int FUNCTION_ID = 42;
	//********************

	if (operators == NULL || nbrOfOperators < 0)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	if (nbrOfOperators < 2)
	{
		return;
	}

	OperationObject **group1;
	OperationObject **group2;
	OperationObject **group3;
	OperationObject **group4;

	int nbrOfG1Operators, nbrOfG2Operators, nbrOfG3Operators, nbrOfG4Operators; //G for Group
	nbrOfG1Operators = 0;
	nbrOfG2Operators = 0;
	nbrOfG3Operators = 0;
	nbrOfG4Operators = 0;

	int i;
	for (i = 0; i < nbrOfOperators; i++) //This first run is used to count the number of operators per group.
	{
		if (strcmp(operators[i]->value, OP_FACTORIAL) == 0 || strcmp(operators[i]->value, OP_PERCENT) == 0)
		{
			nbrOfG1Operators++;
		}
		else if (strcmp(operators[i]->value, OP_POWER) == 0 || strcmp(operators[i]->value, OP_U_MINUS) == 0)
		{
			nbrOfG2Operators++;
		}
		else if (strcmp(operators[i]->value, OP_DIVIDE) == 0 || strcmp(operators[i]->value, OP_TIMES) == 0)
		{
			nbrOfG3Operators++;
		}
		else if (strcmp(operators[i]->value, OP_PLUS) == 0 || strcmp(operators[i]->value, OP_B_MINUS) == 0)
		{
			nbrOfG4Operators++;
		}
		else
		{
			printError(FUNCTION_ID, 2);
			exit(EXIT_FAILURE);
			//return;
		}
	}

	//We allocate the memory to group arrays.
	if (nbrOfG1Operators > 0)
	{
		group1 = (OperationObject **)malloc(nbrOfG1Operators * sizeof(OperationObject));
	}
	if (nbrOfG2Operators > 0)
	{
		group2 = (OperationObject **)malloc(nbrOfG2Operators * sizeof(OperationObject));
	}
	if (nbrOfG3Operators > 0)
	{
		group3 = (OperationObject **)malloc(nbrOfG3Operators * sizeof(OperationObject));
	}
	if (nbrOfG4Operators > 0)
	{
		group4 = (OperationObject **)malloc(nbrOfG4Operators * sizeof(OperationObject));
	}

	int j1, j2, j3, j4;
	for (i = j1 = j2 = j3 = j4 = 0; i < nbrOfOperators; i++) //This second run is used to save the operators from each group. Note that we are doing less checking at this stage.
	{
		if (strcmp(operators[i]->value, OP_FACTORIAL) == 0 || strcmp(operators[i]->value, OP_PERCENT) == 0)
		{
			group1[j1] = operators[i];
			j1++;
		}
		else if (strcmp(operators[i]->value, OP_POWER) == 0 || strcmp(operators[i]->value, OP_U_MINUS) == 0)
		{
			group2[j2] = operators[i];
			j2++;
		}
		else if (strcmp(operators[i]->value, OP_DIVIDE) == 0 || strcmp(operators[i]->value, OP_TIMES) == 0)
		{
			group3[j3] = operators[i];
			j3++;
		}
		else if (strcmp(operators[i]->value, OP_PLUS) == 0 || strcmp(operators[i]->value, OP_B_MINUS) == 0)
		{
			group4[j4] = operators[i];
			j4++;
		}
	}

	//Now let's form the sorted array.  Each group will be traversed according to its direction of evaluation.
	i = 0;
	for (j1 = 0; j1 < nbrOfG1Operators; j1++, i++) //Direction : -->
	{
		operators[i] = group1[j1];
	}
	for (j2 = nbrOfG2Operators - 1; j2 >= 0; j2--, i++) //Direction : <--
	{
		operators[i] = group2[j2];
	}
	for (j3 = 0; j3 < nbrOfG3Operators; j3++, i++) //Direction : -->
	{
		operators[i] = group3[j3];
	}
	for (j4 = 0; j4 < nbrOfG4Operators; j4++, i++) //Direction : -->
	{
		operators[i] = group4[j4];
	}

	//All went well.
	return;
}

/**
 * This function is used to manage all the operators of a block and its sub-blocks (if it has sub-blocks).
 *
 */
void manageBlockOperators(Block *block, List *list)
{
	//********************
	const int FUNCTION_ID = 43;
	//********************

	if (block == NULL || list == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	if (identifyBlockFrom(list, block->beginning, left_to_right) == NULL || identifyBlockFrom(list, block->beginning, left_to_right)->end != block->end)
	{
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//return;
	}

	int i;
	if (block->nbrOfOperators > 0)
	{
		sortOperators(block->operators, block->nbrOfOperators);
		for (i = 0; i < block->nbrOfOperators; i++)
		{
			manageOperator(list, block->operators[i]);
		}
	}
	if (block->nbrOfSubBlocks > 0)
	{
		for (i = 0; i < block->nbrOfSubBlocks; i++)
		{
			manageBlockOperators(block->subBlocks[i], list);
		}
	}
	return;
}

/**
 * This function is used to manage all the operation objects contained in a list which is associated with a given tree.
 * It first handles operators and then handles external functions and numbers.  At the end it handles the extra parentheses.
 *
 */
void manageAllObjects(Tree *tree)
{
	//********************
	const int FUNCTION_ID = 44;
	//********************

	if (tree == NULL || tree->root == NULL || tree->associatedList == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	manageBlockOperators(tree->root, tree->associatedList);
	OperationObject *object = tree->associatedList->first;
	while (object != NULL)
	{
		if (isExternalFunction(object))
		{
			manageExternalFunction(tree->associatedList, object);
		}
		else if (isNumber(object))
		{
			manageNumber(tree->associatedList, object);
		}
		object = object->next;
	}
	manageAdditionalParentheses(tree->associatedList);
	return;
}



//****************************************
//Interface functions
//****************************************
/**
 * This function returns the list corresponding to the given character string.
 * It traverses the provided string character by character. During this course, four possibilities may arise:
 * 1 - The character is an operator or a separator: At this level, a new object is inserted at the end of the list. The value of this object will be the current character.
 * In the special case of the '-' operator, we first determine whether it is binary or unary.
 *
 * 2- The character is a number or the decimal point: Two sub-cases arise:
 * 2-a- If a number was being written, the current character is added to it.
 * 2-b- If no number was being written, we start writing a new number. The current character is thus inserted at the beginning of a transient character string.
 *
 * 3- The character is a letter of the alphabet: Again there are two sub-cases:
 * 3-a- If a word was being written, the current character is added to it.
 * 3-b- If no word was being written, we start writing a new word. The current character is thus inserted at the beginning of a transient character string.
 *
 * 4- The character is not recognized: In this case, we insert a new object at the end of the list. The value of this object will be the current character.
 *
 * In addition to these ways of doing things, in each of its four cases, it is checked whether the transient character string was in use or not. And in some cases, we insert a new object at the end of the list. The value of this object will be the contents of the transient string.
 *
 * Finally when we have finished browsing the provided character string, we check if the transient string is still in use or not. If so, a new object is inserted at the end of the list and its value will be the content of the transient string.
 *
 */
List *stringToList(char *string)
{
	//********************
	const int FUNCTION_ID = 47;
	//********************

	if (string == NULL || strlen(string) < 1)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return NULL;
	}

	List *list = initializeList();
	int length = strlen(string);
	char transientString[length + 1];
	bool transientStringInProgress = false;
	int i, j;
	for (i = 0; i < length; i++)
	{
		if (string[i] == '/' || string[i] == '*' || string[i] == '-' || string[i] == '+' || string[i] == '%' || string[i] == '!' || string[i] == '^' || string[i] == '(' || string[i] == ')') //It is an operator or separator.
		{
			if (transientStringInProgress)
			{
				transientString[j] = '\0';
				insertAtTheEnd(list, transientString);
				transientStringInProgress = false;
			}
			if (string[i] == '-') //We should identify if it is an unary or binary minus.
			{
				if (i == 0 || string[i - 1] == '/' || string[i - 1] == '*' || string[i - 1] == '^' || string[i - 1] == '(') //It is an unary minus.
				{
					insertAtTheEnd(list, OP_U_MINUS);
				}
				else //It is an binary minus.
				{
					insertAtTheEnd(list, OP_B_MINUS);
				}
			}
			else
			{
				strcpy(transientString, "?");
				transientString[0] = string[i];
				insertAtTheEnd(list, transientString);
			}
		}
		else if (isdigit(string[i]) || string[i] == '.') //It is a part of a number.
		{
			if (transientStringInProgress)
			{
				if (isalpha(string[i - 1]))
				{
					transientString[j] = '\0';
					insertAtTheEnd(list, transientString);
					transientStringInProgress = false;

					j = 0;
					transientString[j] = string[i];
					j++;
					transientStringInProgress = true;
				}
				else
				{
					transientString[j] = string[i];
					j++;
				}
			}
			else
			{
				j = 0;
				transientString[j] = string[i];
				j++;
				transientStringInProgress = true;
			}
		}
		else if (isalpha(string[i])) //It is part of an external function or constant.
		{
			if (transientStringInProgress)
			{
				if (isalpha(string[i - 1]))
				{
					transientString[j] = string[i];
					j++;
				}
				else
				{
					transientString[j] = '\0';
					insertAtTheEnd(list, transientString);
					transientStringInProgress = false;

					j = 0;
					transientString[j] = string[i];
					j++;
					transientStringInProgress = true;
				}
			}
			else
			{
				j = 0;
				transientString[j] = string[i];
				j++;
				transientStringInProgress = true;
			}
		}
		else //It is an unknowed character.
		{
			if (transientStringInProgress)
			{
				transientString[j] = '\0';
				insertAtTheEnd(list, transientString);
				transientStringInProgress = false;
			}
			strcpy(transientString, "?");
			transientString[0] = string[i];
			insertAtTheEnd(list, transientString);
		}
	}

	if (transientStringInProgress)
	{
		transientString[j] = '\0';
		insertAtTheEnd(list, transientString);
		transientStringInProgress = false;
	}
	return list;
}

/**
 * This function allows to know if the syntax of a number is valid or not. It checks the nature of the previous and the next of the provided object.
 * Note that we don't check if the supplied object is really a number or not.
 *
 */
bool analyzeSyntaxForNumber(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 56;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	OperationObject *previous = object->previous;
	OperationObject *next = object->next;

	if (previous == NULL || (isOperator(previous) && !isOperatorCategory4(previous)) || isLeftSeparator(previous))
	{
		if (next == NULL || (isOperator(next) && !isOperatorCategory3(next)) || isConstant(next) || isSeparator(next) || isExternalFunction(next))
		{
			return true;
		}
	}

	return false;
}

/**
 * This function allows to know if the syntax of an operator is valid or not. It checks the nature of the previous and the next of the provided object.
 * Note that we don't check if the supplied object is really an operator or not.
 *
 */
bool analyzeSyntaxForOperator(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 57;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	OperationObject *previous = object->previous;
	OperationObject *next = object->next;

	//For category 1
	if (isOperatorCategory1(object))
	{
		if (previous == NULL)
		{
			return false;
		}
		if (isNumber(previous) || isOperatorCategory4(previous) || isConstant(previous) || isRightSeparator(previous))
		{
			if (next == NULL)
			{
				return false;
			}
			if (isNumber(next) || isOperatorCategory3(next) || isConstant(next) || isLeftSeparator(next) || isExternalFunction(next))
			{
				return true;
			}
		}
	}
	//For category 2
	else if (isOperatorCategory2(object))
	{
		if (previous == NULL)
		{
			return false;
		}
		if (isNumber(previous) || isOperatorCategory4(previous) || isConstant(previous) || isRightSeparator(previous))
		{
			if (next == NULL)
			{
				return false;
			}
			if (isNumber(next) || isConstant(next) || isLeftSeparator(next) || isExternalFunction(next))
			{
				return true;
			}
		}
	}
	//For category 3
	else if (isOperatorCategory3(object))
	{
		if (previous == NULL || isOperatorCategory1(previous) || isLeftSeparator(previous))
		{
			if (next == NULL)
			{
				return false;
			}
			if (isNumber(next) || isConstant(next) || isLeftSeparator(next) || isExternalFunction(next))
			{
				return true;
			}
		}
	}
	//For category 4
	else if (isOperatorCategory4(object))
	{
		if (previous == NULL)
		{
			return false;
		}
		if (isNumber(previous) || isOperatorCategory4(previous) || isConstant(previous) || isRightSeparator(previous))
		{
			if (next == NULL || (isOperator(next) && !isOperatorCategory3(next)) || isConstant(next) || isSeparator(next) || isExternalFunction(next))
			{
				return true;
			}
		}
	}

	return false;
}

/**
 * This function allows to know if the syntax of a constant is valid or not. It checks the nature of the previous and the next of the provided object.
 * Note that we don't check if the supplied object is really a constant or not.
 *
 */
bool analyzeSyntaxForConstant(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 58;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	OperationObject *previous = object->previous;
	OperationObject *next = object->next;

	if (previous == NULL || isNumber(previous) || isOperator(previous) || isConstant(previous) || isSeparator(previous))
	{
		if (next == NULL || (isOperator(next) && !isOperatorCategory3(next)) || isConstant(next) || isSeparator(next) || isExternalFunction(next))
		{
			return true;
		}
	}

	return false;
}

/**
 * This function allows to know if the syntax of a separator is valid or not. It checks the nature of the previous and the next of the provided object.
 * Note that we don't check if the supplied object is really a separator or not.
 *
 */
bool analyzeSyntaxForSeparator(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 59;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	OperationObject *previous = object->previous;
	OperationObject *next = object->next;

	//For category 1
	if (isLeftSeparator(object))
	{
		if (previous == NULL || isNumber(previous) || isOperator(previous) || isConstant(previous) || isSeparator(previous) || isExternalFunction(previous))
		{
			if (next == NULL)
			{
				return false;
			}
			if (isNumber(next) || isOperatorCategory3(next) || isConstant(next) || isLeftSeparator(next) || isExternalFunction(next))
			{
				return true;
			}
		}
	}
	//For category 2
	else if (isRightSeparator(object))
	{
		if (previous == NULL)
		{
			return false;
		}
		if (isNumber(previous) || isOperatorCategory4(previous) || isConstant(previous) || isRightSeparator(previous))
		{
			if (next == NULL || (isOperator(next) && !isOperatorCategory3(next)) || isConstant(next) || isSeparator(next) || isExternalFunction(next))
			{
				return true;
			}
		}
	}

	return false;
}

/**
 * This function allows to know if the syntax of an external function is valid or not. It checks the nature of the previous and the next of the provided object.
 * Note that we don't check if the supplied object is really an external function or not.
 *
 */
bool analyzeSyntaxForExternalFunction(OperationObject *object)
{
	//********************
	const int FUNCTION_ID = 60;
	//********************

	if (object == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	OperationObject *previous = object->previous;
	OperationObject *next = object->next;

	if (previous == NULL || isNumber(previous) || isOperator(previous) || isConstant(previous) || isSeparator(previous))
	{
		if (next == NULL)
		{
			return false;
		}
		if (isLeftSeparator(next))
		{
			return true;
		}
	}

	return false;
}

/**
 * This function allows to make an additional control on the separators. It checks if an open parenthesis has been closed and if a closed parenthesis has been opened.
 *
 */
bool checkLeftAndRightSeparators(List *list, OperationObject *separator)
{
	//********************
	const int FUNCTION_ID = 61;
	//********************

	if (list == NULL || separator == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	if (!isIncluded(list, separator))
	{
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//return false;
	}

	if (!isSeparator(separator))
	{
		printError(FUNCTION_ID, 3);
		exit(EXIT_FAILURE);
		//return false;
	}

	OperationObject *object;
	int nbrOfLeftS = 0, nbrOfRightS = 0; //S for Separators.
	if (isLeftSeparator(separator))		 //It is "("
	{
		nbrOfLeftS = 1;
		object = separator->next;
		while (object != NULL && nbrOfLeftS != nbrOfRightS)
		{
			if (isLeftSeparator(object))
			{
				nbrOfLeftS++;
			}
			else if (isRightSeparator(object))
			{
				nbrOfRightS++;
			}
			object = object->next;
		}
		if (nbrOfLeftS == nbrOfRightS)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else //It is ")"
	{
		nbrOfRightS = 1;
		object = separator->previous;
		while (object != NULL && nbrOfLeftS != nbrOfRightS)
		{
			if (isLeftSeparator(object))
			{
				nbrOfLeftS++;
			}
			else if (isRightSeparator(object))
			{
				nbrOfRightS++;
			}
			object = object->previous;
		}
		if (nbrOfLeftS == nbrOfRightS)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

/**
 * This function is used to display syntax errors.  It displays the list from its first object to the erroneous object. The erroneous object is displayed in red.
 *
 */
void printSyntaxError(List *list, OperationObject *wrongObject)
{
	//********************
	const int FUNCTION_ID = 62;
	//********************

	if (list == NULL || wrongObject == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	if (!isIncluded(list, wrongObject))
	{
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//return;
	}

	printf("\e[31mSYNTAX ERROR : \e[0m");
	OperationObject *object = list->first;
	while (object != NULL)
	{
		if (object == wrongObject)
		{
			printf("\e[31m");
			if (strcmp(wrongObject->value, OP_U_MINUS) == 0 || strcmp(wrongObject->value, OP_B_MINUS) == 0) //This is a special case.
			{
				printf("-");
			}
			else
			{
				printf("%s", wrongObject->value);
			}
			printf("\e[0m");
			object = NULL;
		}
		else
		{
			if (strcmp(object->value, OP_U_MINUS) == 0 || strcmp(object->value, OP_B_MINUS) == 0) //This is a special case.
			{
				printf("-");
			}
			else
			{
				printf("%s", object->value);
			}
			object = object->next;
		}
	}
	return;
}

/**
 * This function is used to analyze the syntax of a list.
 * It goes through the list object by object.
 * For each object it determines its type.
 * If this type is known it checks the syntax of the object.
 * If the type is unknown or if the type is known but the syntax is incorrect then it is signaled that there is a syntax error in the list and the program is exited by returning false.
 *
 */
bool syntaxAnalysis(List *list)
{
	//********************
	const int FUNCTION_ID = 48;
	//********************

	if (list == NULL || list->first == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	OperationObject *object = list->first;
	while (object != NULL)
	{
		if (isNumber(object))
		{
			if (analyzeSyntaxForNumber(object) == false)
			{
				printSyntaxError(list, object);
				return false;
			}
		}
		else if (isOperator(object))
		{
			if (analyzeSyntaxForOperator(object) == false)
			{
				printSyntaxError(list, object);
				return false;
			}
		}
		else if (isConstant(object))
		{
			if (analyzeSyntaxForConstant(object) == false)
			{
				printSyntaxError(list, object);
				return false;
			}
		}
		else if (isSeparator(object))
		{
			if (analyzeSyntaxForSeparator(object) == false)
			{
				printSyntaxError(list, object);
				return false;
			}
			if (checkLeftAndRightSeparators(list, object) == false)
			{
				printSyntaxError(list, object);
				return false;
			}
		}
		else if (isExternalFunction(object))
		{
			if (analyzeSyntaxForExternalFunction(object) == false)
			{
				printSyntaxError(list, object);
				return false;
			}
		}
		else
		{
			printSyntaxError(list, object);
			return false;
		}

		object = object->next;
	}

	return true;
}

/**
 * This function allow to manage all constants contained in a list.
 *
 */
void manageAllConstants(List *list)
{
	//********************
	const int FUNCTION_ID = 63;
	//********************

	if (list == NULL || list->first == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	OperationObject *object = list->first;
	while (object != NULL)
	{
		if (isConstant(object))
		{
			manageConstant(list, object);
		}
		object = object->next;
	}
	return;
}

/**
 * This function is used to manage the implicit multiplications found in a list.
 * An implicit multiplication appear when a block is directly followed by another block.
 * For example: "2(3+4*5)ln(10)" will be transformed into "2*(3+4*5)*ln(10)".
 *
 */
void manageImplicitMultiplications(List *list)
{
	//********************
	const int FUNCTION_ID = 64;
	//********************

	if (list == NULL || list->first == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	OperationObject *object = list->first;
	Block *possibleBlock;
	while (object != NULL)
	{
		possibleBlock = identifyBlockFrom(list, object, left_to_right);
		if (possibleBlock == NULL)
		{
			object = object->next;
		}
		else
		{
			if (possibleBlock->end->next == NULL)
			{
				object = object->next;
			}
			else
			{
				if (identifyBlockFrom(list, possibleBlock->end->next, left_to_right) != NULL)
				{
					insertAfter(list, OP_TIMES, possibleBlock->end);
				}
				object = object->next;
			}
		}
	}
	return;
}



//****************************************
//General functions
//****************************************
/**
 * This function is used to make secure inputs in the program.
 *
 */
void scan(char *string, int maxLength)
{
	//********************
	const int FUNCTION_ID = 46;
	//********************

	if (string == NULL || maxLength < 1)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	bool scanSucessful = false;
	do
	{
		if (fgets(string, maxLength + 1 + 1, stdin) == NULL)
		{
			printf("\nERROR : Please try again\n");
		}
		else
		{
			int length = strlen(string);
			if (string[length - 1] == '\n')
			{
				string[length - 1] = '\0';
			}
			length = strlen(string);
			if (length < 1)
			{
				printf("\nERROR : Enter at least one character.\n");
				scanSucessful = false;
			}
			else if (length > maxLength)
			{
				emptyBuffer();
				printf("\nERROR : Enter at most %d characters.\n", maxLength);
				scanSucessful = false;
			}
			else
			{
				scanSucessful = true;
			}
		}
	} while (!scanSucessful);
}

/**
 * This function allow to empty the buffer.
 *
 */
void emptyBuffer()
{
	char n;
	do
	{
		n = getchar();
	} while (n != '\n');
}



//****************************************
//Command functions
//****************************************
/**
 * This function allow to know if a character string is a command or not.
 *
 */
bool isCommand(char *string)
{
	//********************
	const int FUNCTION_ID = 65;
	//********************

	if (string == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return false;
	}

	if (strcmp(string, C_SET_M) == 0 || strcmp(string, C_BACK) == 0 || strcmp(string, C_SET_P) == 0 || strcmp(string, C_DISPLAY_I) == 0 || strcmp(string, C_CLEAR) == 0 || strcmp(string, C_EXIT) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * This function is used to execute commands. It calls the function corresponding to the given command.
 *
 */
void runCommand(char *command, char *mode, int *precision)
{
	//********************
	const int FUNCTION_ID = 66;
	//********************

	if (!isCommand(command))
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	if (strcmp(command, C_SET_M) == 0)
	{
		c_setMode(mode, false);
	}
	else if (strcmp(command, C_BACK) == 0)
	{
		c_back(mode);
	}
	else if (strcmp(command, C_SET_P) == 0)
	{
		c_setPrecision(precision);
	}
	else if (strcmp(command, C_DISPLAY_I) == 0)
	{
		c_displayInfos(*precision);
	}
	else if (strcmp(command, C_CLEAR) == 0)
	{
		c_clear();
	}
	else if (strcmp(command, C_EXIT) == 0)
	{
		c_exit(mode);
	}
	else
	{
		printError(FUNCTION_ID, 2);
		exit(EXIT_FAILURE);
		//return;
	}
}

/**
 * This function allow user to select the operating mode of the program.
 * The "mode" character string is used to store the mode. For example, the character string "2130" corresponds to the "2-1-3" mode.
 * The boolean "settingInProgress" indicates whether the initial value (value when calling the function) of "mode" must be taken into account or not.
 *
 * Case where "settingInProgress" = "false": The mode is first initialized to zero (for example "0000" or "000" or "00") then the user is asked to choose his mode from the  beginning.
 * For example the user can choose "1000" then "1300" then "1320".
 *
 * Case where "settingInProgress" = "true": In this case, we go up one level before asking the user to choose the mode he wants.
 * Suppose for example that the mode supplied as a parameter is "2130".
 * We go up one level and we get "2100". Then the user is invited to choose his mode.
 * He can then choose the modes "2110", "2120", 2130",...,"2111", 2112",...,"2121", "2122"  ,...,"2131", "2132",...
 *
 */
void c_setMode(char *mode, bool settingInProgress)
{
	//********************
	const int FUNCTION_ID = 67;
	//********************

	if (mode == NULL || strlen(mode) != LENGTH_OF_MODE)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	char n;
	int i;
	if (!settingInProgress)
	{
		for (i = 0; i < LENGTH_OF_MODE; i++) //Initialization
		{
			mode[i] = '0';
		}
		mode[i] = '\0';

		printf("\nSelect a mode :\n1 - Calculator\n2 - Tools\n3 - Documentation\n\n");
		do
		{
			scanf("%c", &n);
		} while (n != '1' && n != '2' && n != '3');
		mode[0] = n;
		emptyBuffer();
	}
	else
	{
		for (i = LENGTH_OF_MODE - 1; i >= 0; i--) //Return to the back level
		{
			if (mode[i] != '0')
			{
				mode[i] = '0';
				break;
			}
		}
	}

	//Calculator
	if (mode[0] == '1')
	{
	}
	//Tools
	else if (mode[0] == '2')
	{
		printf("\nSelect a tool :\n1 - Identifier of prime numbers\n\n");
		do
		{
			scanf("%c", &n);
		} while (n != '1');
		mode[1] = n;
		emptyBuffer();

		//Tools : Identifier of prime numbers
		if (mode[1] == '1')
		{
		}
	}
	//Documentation
	else if (mode[0] == '3')
	{
		printf("\nSelect a documentation :\n1 - Credit\n2 - How to use ?\n3 - Operators precedence\n\n");
		do
		{
			scanf("%c", &n);
		} while (n != '1' && n != '2' && n != '3');
		mode[1] = n;
		emptyBuffer();

		//Documentation : Credit
		if (mode[1] == '1')
		{
		}
		//Documentation : How to use
		else if (mode[1] == '2')
		{
		}
		//Documentation : Operators Precedence
		else if (mode[1] == '3')
		{
		}
	}
	//Error : We chose to use Calculator by default.
	else
	{
		for (i = 0; i < LENGTH_OF_MODE; i++) //Initialization
		{
			mode[i] = '0';
		}
		mode[0] = '1';
	}
}

/**
 * This function allows the user to choose an operating mode after returning to the previous level.
 *
 */
void c_back(char *mode)
{
	//********************
	const int FUNCTION_ID = 68;
	//********************

	if (mode == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	c_setMode(mode, true);
}

/**
 * This function allow user to choose the display precision of decimal numbers.
 *
 */
void c_setPrecision(int *precision)
{
	//********************
	const int FUNCTION_ID = 69;
	//********************

	if (precision == NULL)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	char n;
	printf("\nSelect the precision :\n1 - 10 digits after the decimal point\n2 - 20 digits after the decimal point\n3 - 30 digits after the decimal point\n\n");
	do
	{
		scanf("%c", &n);
	} while (n != '1' && n != '2' && n != '3');
	emptyBuffer();

	switch (n)
	{
	case '1':
		*precision = 10;
		break;
	case '2':
		*precision = 20;
		break;
	case '3':
		*precision = 30;
		break;
	}
}

/**
 * This function allow to display information about representable values, display precision of real numbers, etc.
 *
 */
void c_displayInfos(int precision)
{
	printf("\nRepresentable decimal values : min = (-) %Lg ; max = (-) %Lg \nRepresentable integer values : min = %lld ; max = %lld\n", LDBL_MIN, LDBL_MAX, LLONG_MIN, LLONG_MAX);
	printf("Display precision of decimal values = %d digits after the decimal point\n", precision);
	printf("Length of entries : min = 1 ; max = %d\n", COMMAND_LENGTH);
	printf("Maximum length of numbers = %d\n\n", MAX_LENGTH_OF_NUMBER - 1);
	printf("NOTE:\n- The decimal representation is used by default. It is always used in Calculator mode.\n- The integer representation is used only when it is the best fit. It is used in tools that operate on integers.\n\n");
}

/**
 * This function allow to clear the screen.
 *
 */
void c_clear()
{
	printf("\e[2J\e[1;1H");
}

/**
 * This function allow to stop the program and exit. Therefore, we set the mode to the stop mode which corresponds to null mode (eg "0000" or "000").
 *
 */
void c_exit(char *mode)
{
	//********************
	const int FUNCTION_ID = 70;
	//********************

	if (mode == NULL || strlen(mode) != LENGTH_OF_MODE)
	{
		printError(FUNCTION_ID, 1);
		exit(EXIT_FAILURE);
		//return;
	}

	int i;
	for (i = 0; i < LENGTH_OF_MODE; i++)
	{
		mode[i] = '0';
	}
	mode[i] = '\0';
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