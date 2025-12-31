#include "common.h"
#include "utils.h"

/**
 * We use this function to manage the display of errors.
 *
 */
void printError(int functionId, int errorId)
{
	fprintf(stderr, "\n\nERROR : %d-%d\n\n", functionId, errorId);
}

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
