#include <stdlib.h>
#include <stdio.h>
#include "LongNumbers.h"

typedef struct longNumber
{
	int numberOfDigits;
	int *numberInArray;
} longNumber;


longNumber *createLongNumberFromInt(int intNumber)
{
	longNumber *number = malloc(sizeof(longNumber));
	
	int tempArray[5];
	int numberOfDigits = 0;
	while (intNumber / 16 > 0)
	{
		tempArray[numberOfDigits] = intNumber % 16;
		intNumber = intNumber / 16;
		numberOfDigits++;
	}
	tempArray[numberOfDigits] = intNumber;
	numberOfDigits++;

	number->numberInArray = malloc(numberOfDigits * sizeof(int*));
	for (int i = 0; i < numberOfDigits; i++)
	{
		number->numberInArray[i] = tempArray[i];
	}

	number->numberOfDigits = numberOfDigits;
	return number;
}

longNumber *buildLongNumber(int length)
{
	longNumber *number = malloc(sizeof(longNumber));
	
	number->numberInArray = malloc(length * sizeof(int*));
	for (int i = 0; i < length; i++)
	{
		number->numberInArray[i] = 0;
	}

	number->numberOfDigits = length;
}

char convertNumberTo16(int number)
{
	switch (number)
	{
	case 10:
	{
		return 'A';
	}
	case 11:
	{
		return 'B';
	}
	case 12:
	{
		return 'C';
	}
	case 13:
	{
		return 'D';
	}
	case 14:
	{
		return 'E';
	}
	case 15:
	{
		return 'F';
	}
	default:
	{
		return number + '0';
	}
	}
}

void printNumber(longNumber *number)
{
	for (int i = realLength(number) - 1; i >= 0; i--)
	{
		printf("%c", convertNumberTo16(number->numberInArray[i]));
	}
}

void deleteNumber(longNumber **number)
{
	if (*number == NULL)
	{
		return;
	}
	free((*number)->numberInArray);
	free(*number);
}

int realLength(longNumber *number)
{
	if (number->numberInArray[number->numberOfDigits - 1] == 0)
	{
		return number->numberOfDigits - 1;
	}
	return number->numberOfDigits;
}

longNumber *addition(longNumber *first, longNumber *second)
{
	longNumber *max;
	longNumber *min;
	if (realLength(first) > realLength(second))
	{
		max = first;
		min = second;
	}
	else
	{
		max = second;
		min = first;
	}

	longNumber *result = buildLongNumber(realLength(max) + 1);
	int carry = 0;
	for (int i = 0; i < realLength(min); i++)
	{
		result->numberInArray[i] = (first->numberInArray[i] + second->numberInArray[i] + carry) % 16;
		carry = (first->numberInArray[i] + second->numberInArray[i] + carry) / 16;
	}
	for (int i = realLength(min); i < realLength(max); i++)
	{
		result->numberInArray[i] = (max->numberInArray[i] + carry) % 16;
		carry = (max->numberInArray[i] + carry) / 16;
	}
	result->numberInArray[realLength(max)] = carry;

	return result;
}

longNumber *multiplication(longNumber *first, longNumber *second)
{
	longNumber *result = buildLongNumber(realLength(first) + realLength(second));

	for (int j = 0; j < realLength(second); j++)
	{
		int carry = 0;
		for (int i = 0; i < realLength(first); i++)
		{
			int t = first->numberInArray[i] * second->numberInArray[j] + carry + result->numberInArray[i + j];
			result->numberInArray[i + j] = t % 16;
			carry = t / 16;
		}
		result->numberInArray[j + realLength(first)] = carry;
	}

	return result;
}

longNumber *raiseToPower(longNumber *number, int power)
{
	if (power == 0)
	{
		longNumber *res = createLongNumberFromInt(1);
		return res;
	}

	if (power % 2 == 1)
	{
		longNumber *first = raiseToPower(number, power - 1);
		longNumber *second = number;
		longNumber *res = multiplication(first, second);
		deleteNumber(&first);
		return res;
	}
	else
	{
		longNumber *first = raiseToPower(number, power / 2);
		longNumber *res = multiplication(first, first);
		deleteNumber(&first);
		return res;
	}

}