#include "tools.h"
#include "common.h"
#include "utils.h"

/*
 * Implements auxiliary utilities and tools used in the calculator.
 */


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