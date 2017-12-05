// long.cpp : Defines the entry point for the console application.
//
#include <stdlib.h>
#include <stdio.h>
#include "LongNumbers.h"


int main()
{
	longNumber *number = createLongNumberFromInt(3);
	longNumber *result = raiseToPower(number, 5000);
	printNumber(result);
	putchar('\n');
	deleteNumber(&number);
	deleteNumber(&result);
	
	return 0;
}

