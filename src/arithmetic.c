#include "common.h"
#include "arithmetic.h"
#include "globals.h"
#include "utils.h"

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
