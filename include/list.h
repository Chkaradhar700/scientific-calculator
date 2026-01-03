#ifndef LIST_H
#define LIST_H

#include "common.h"

/*
 * Declares structures and functions for linked list management.
 * Provides a foundation for representing and manipulating sequences of operations.
 */


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

#endif /* LIST_H */