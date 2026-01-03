#include "common.h"
#include "list.h"
#include "globals.h"
#include "utils.h"
#include "tree.h"

/*
 * Implements linked list functionality for the calculator.
 * Handles insertion, deletion, traversal, and conversion of operation sequences.
 */


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
