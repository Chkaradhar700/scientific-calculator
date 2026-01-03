#ifndef PARSER_H
#define PARSER_H

#include "common.h"
#include "list.h"
#include "tree.h"

/*
 * Declares functions for transforming user input into internal representations.
 */


struct FunctionInfos
{
	char name[FUNCTION_NAME_SIZE];
	char arg1[FUNCTION_ARGS_SIZE];
	char arg2[FUNCTION_ARGS_SIZE];
};
typedef struct FunctionInfos FunctionInfos;

FunctionInfos getFunctionInfos(char[]);
long double operate(char[]);
char *getInternalFunction(char[]);
long double toDecimal(char const *);

void manageConstant(List *, OperationObject *);
void manageNumber(List *, OperationObject *);
void manageOperator(List *, OperationObject *);
void manageExternalFunction(List *, OperationObject *);
void manageAdditionalParentheses(List *);

void sortOperators(OperationObject **, int);
void manageBlockOperators(Block *, List *);
void manageAllObjects(Tree *);

List *stringToList(char *);
void manageAllConstants(List *);
void manageImplicitMultiplications(List *);


#endif /* PARSER_H */