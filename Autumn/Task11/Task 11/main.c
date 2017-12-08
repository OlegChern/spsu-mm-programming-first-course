#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int digitalRoot(int n)
{
	if (n % 9 == 0)
	{
		return 9;
	}
	else
	{
		return (n % 9);
	}
}

int sumRoot(int *a)
{
	if (a[3] < a[1])
	{
		if ((a[1] - a[3]) % 3 > 0)
		{
			return a[7] * 8 
			 	 + a[6] * 7
				 + a[4] * 5
				 + (a[2] / 2) * 9
				 + a[0] * 1
				 + a[3] * 8
				 + ((a[1] - a[3]) / 3) * 8 
				 + (a[2] % 2) * 6 
				 + (((a[1] - a[3]) % 3) - (a[2] % 2)) * 2;
		}
		else
		{
			return a[7] * 8
				+ a[6] * 7
				+ a[4] * 5
				+ (a[2] / 2) * 9
				+ a[0] * 1
				+ a[3] * 8
				+ ((a[1] - a[3]) / 3) * 8
				+ (a[2] % 2) * 3;
		}
	}
	else
	{
		if (a[3] > a[1])
		{
			return a[7] * 8
				+ a[6] * 7
				+ a[4] * 5
				+ (a[2] / 2) * 9
				+ a[0] * 1
				+ a[1] * 8
				+ (a[3] - a[1]) * 4
				+ (a[2] % 2) * 3;
		}
		else
		{
			return a[7] * 8
				+ a[6] * 7
				+ a[4] * 5
				+ (a[2] / 2) * 9
				+ a[0] * 1
				+ a[1] * 8
				+ (a[2] % 2) * 3;
		}
	}
}

int main()
{
	int a[8];
	int sum = 0;
	int *simpleNumber;
	int k = 1, i = 3, simple = 0;
	simpleNumber = (int*)malloc(k * sizeof(int));
	simpleNumber[0] = 2;
	k++;
	do
	{
		while (simple == 0)
		{
			int j = 0;
			do
			{
				if (i % simpleNumber[j] == 0)
				{
					simple = 0;
					break;
				}
				else
				{
					simple = 1;
				}
				j++;
			}
			while (simpleNumber[j] < sqrt(i));
			i++;
		}
		simpleNumber = (int*)realloc(simpleNumber, k * sizeof(int));
		simpleNumber[k - 1] = i - 1;
		k++;
		simple = 0;
	}
	while (i < 1000000);

	k--;
	k--;
	for (i = 2; i < 1000000; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			a[j] = 0;
		}
		int n = i;
		int j = 0;
		while (n != 1)
		{
			if (simpleNumber[j] > sqrt(n))
			{
				a[digitalRoot(n) - 1]++;
				n = 1;
			}
			else
			{
				if (n % simpleNumber[j] == 0)
				{
					n /= simpleNumber[j];
					a[digitalRoot(simpleNumber[j]) - 1]++;
				}
				else
				{
					j++;
				}
			}
		}
		sum += sumRoot(a);
	}

	printf("Summ MDRS(n) = %d", sum);

	_getch();

	return 0;
}