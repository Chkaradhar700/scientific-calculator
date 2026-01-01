/*
 *
 * Temporary manual test suite.
 *
 * This file groups together various test snippets used during development.
 *
 * TODO: Replace this file with a proper test framework (unit tests + 
 * automated assertions).
 */

#include "common.h"
#include "globals.h"
#include "arithmetic.h"
#include "utils.h"
#include "list.h"
#include "tree.h"
#include "parser.h"
#include "validation.h"
#include "commands.h"
#include "tools.h"


void test_arithmetic_utils_parser(void);
void test_list_1(void);
void test_list_2(void);
void test_tree(void);
void test_parser_1(void);
void test_parser_2(void);
void test_validation(void);


int main(void)
{
    printf("=== Manual test suite ===\n\n");

    test_arithmetic_utils_parser();
    test_list_1();
    test_list_2();
    test_tree();
    test_parser_1();
    test_parser_2();
    test_validation();

    printf("\n=== End of tests ===\n");
    return 0;
}

void test_arithmetic_utils_parser(void)
{
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
}

void test_list_1(void)
{
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
}

void test_list_2(void)
{
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
}

void test_tree(void)
{
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
}

void test_parser_1(void)
{
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
}


void test_parser_2(void)
{
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
}

void test_validation(void)
{
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
}
