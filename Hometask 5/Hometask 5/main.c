#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_NUMB 100

int main()
{
	int a[MAX_NUMB];
	int count = 0, i;
	int nums[MAX_NUMB], dens[MAX_NUMB];
	int n, sqN, p;
	int ok;
	int num, den;
	do
	{
		ok = 1;
		printf("Enter N: ");//for example 503
		scanf_s("%d", &n);
		if (n <= 0)
		{
			printf("Error!\n");
			ok = 0;
		}
		else
		{
			sqN = sqrt(n);
			if (sqN*sqN == n)
			{
				printf("Integral root!");
				ok = 0;
			}
		}

	} while (!ok);

	num = 1; den = sqN;
	do
	{
		nums[count] = num;
		dens[count] = den;
		p = (n - den*den) / num;
		a[count] = (den + sqN) / p;
		num = p;
		den = sqN - (den + sqN) % p;
		count++;

	} while (num != nums[0] || den != dens[0]);

	printf("Period = %d\n", count);
	printf("%d; ", sqN);
	for (i = 0; i < count; i++)
	{
		printf("%d, ", a[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}