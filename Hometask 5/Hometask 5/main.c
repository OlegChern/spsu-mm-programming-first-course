#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_NO_WARNINGS
#define INIT_NUMB 10
#define DELTA 5

int main()
{
	int *a = malloc(INIT_NUMB * sizeof(int));
	int count = 0, i, length = INIT_NUMB;
	int *nums = malloc(INIT_NUMB * sizeof(int)), *dens = malloc(INIT_NUMB * sizeof(int));
	int n, sqN, p;
	int ok;
	int num, den;
	do
	{
		ok = 1;
		printf("Enter N: ");
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
		if (count >= length)
		{
			length += DELTA;
			a = realloc(a, length * sizeof(int));
			nums = realloc(nums, length * sizeof(int));
			dens = realloc(dens, length * sizeof(int));
		}
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
