#include "tree.h"
#include "utils.h"

/*
 * Implements the creation and management of trees for operation hierarchies.
 */


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

	free(block); //We assume that all "Block" type variable was dynamically created.
	block = NULL;
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
