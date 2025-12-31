#include "common.h"
#include "list.h"
#include "utils.h"


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
