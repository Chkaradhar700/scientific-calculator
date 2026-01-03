#include "parser.h"
#include "utils.h"
#include "arithmetic.h"

/*
 * Implements the logic for parsing and managing mathematical expressions.
 */


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
