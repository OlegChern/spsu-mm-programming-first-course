#define _CRT_SECURE_NO_WARNINGS

#include "stdlib.h"
#include "stdio.h"

char inputString(char* s);

void numCoin(int rest, long long *var, int *coin, int index)
{
	if (index == 2)
	{
		for (int i = 0; i <= (rest / coin[index]); i++)
		{
			(*var) += (rest - i * coin[index]) / coin[index - 1] + 1;
		}
		return;
	}
	if (index == 1)
	{
		(*var) += (rest / coin[index] + 1);
		return;
	}
	if (index == 0)
	{
		(*var)++;
		return;
	}
	if (rest < coin[index])
	{
		numCoin(rest, var, coin, index - 1);
		return;
	}
	int k = 0;
	k = rest / coin[index];
	int i = 0;
	do
	{
		numCoin(rest % coin[index] + i * coin[index], var, coin, index - 1);
		k--;
		i++;
	} while (k > 0);
	numCoin(rest % coin[index] + i * coin[index], var, coin, index - 1);
}

int main()
{
	int coin[8] = { 1, 2, 5, 10, 20, 50, 100, 200 };
	long long var;
	var = 0;
	int N;
	N = 0;

	int k = 0;

	while (k == 0)
	{
		printf("Enter the natural number .\nN = ");
		char s[16];
		scanf("%15s", &s);
		if (inputString(s) != 'u')
		{
			printf("\nError! Try again.\n");
		}
		else
		{
			N = atoi(&s);
			k = 1;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (N >= coin[7 - i])
		{
			numCoin(N, &var, coin, 7 - i);
			break;
		}
	}

	printf("All variations: %lld", var);

	_getch();

	return 0;
}