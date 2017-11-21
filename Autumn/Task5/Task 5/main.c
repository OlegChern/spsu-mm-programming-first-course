#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

char inputString(char* s);

int main()
{
	int inputNumber, period, i;
	long double number;
	int *a;
	int l = 1;

	int k = 0;

	while (k == 0)
	{
		printf("Enter the number which is not a square integer.\nN = ");
		char s[16];
		scanf("%15s", &s);
		if (inputString(s) != 'u')
		{
			printf("\nError! Try again.\n");
		}
		else
		{
			inputNumber = atoi(&s);
			if (sqrt(inputNumber) == (int)sqrt(inputNumber))
			{
				printf("\nError! Try again.\n");
			}
			else
			{
				k++;
			}
		}
	}

	i = 1;
	period = 0;
	number = sqrt(inputNumber);

	a = (int*)malloc(sizeof(int) * l);

	a[0] = (int)number;
	long double numerator, denominator;
	numerator = a[0];
	denominator = inputNumber - numerator * numerator;
	
	if (inputNumber - numerator * numerator == 1)
	{
		printf("Period = 1\na[0] = %d\na[1] = %d", a[0], a[0] * 2);
		return 0;
	}

	do
	{
		period++;
		l++;
		a = (int*)realloc(a, sizeof(int) * l);
		a[i] = (int)((number + numerator) / denominator);
		numerator = a[i] * denominator - numerator;
		denominator = (inputNumber - numerator * numerator) / denominator;
		i++;
	} while (denominator != 1);
	
	period++;
	l++;
	a = (int*)realloc(a, sizeof(int) * l);
	a[i] = a[0] + numerator;

	printf("Period = %d\n", period);
	for (int j = 0; j < i + 1; j++)
	{
		printf("a[%d] = %d\n", j, a[j]);
	}

	return 0;
}