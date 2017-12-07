#define _CRT_SECURE_NO_WARNINGS

#include "stdlib.h"
#include "stdio.h"

char inputString(char* s);

void numC2(int rest, int *var, int c2)
{
	(*var) += (rest / c2 + 1);
}

void numC5(int rest, int *var, int c5)
{
	if (rest < c5)
	{
		numC2(rest, var, 2);
		return;
	}
	int k = 0;
	k = rest / c5;
	int i = 0;
	do
	{
		numC2(rest % c5 + i * c5, var, 2);
		k--;
		i++;
	} while (k != 0);
	numC2(rest % c5 + i * c5, var, 2);
}

void numC10(int rest, int *var, int c10)
{
	if (rest < c10)
	{
		numC5(rest, var, 5);
		return;
	}
	int k = 0;
	k = rest / c10;
	int i = 0;
	do
	{
		numC5(rest % c10 + i * c10, var, 5);
		k--;
		i++;
	} while (k != 0);
	numC5(rest % c10 + i * c10, var, 5);
}

void numC20(int rest, int *var, int c20)
{
	if (rest < c20)
	{
		numC10(rest, var, 10);
		return;
	}
	int k = 0;
	k = rest / c20;
	int i = 0;
	do
	{
		numC10(rest % c20 + i * c20, var, 10);
		k--;
		i++;
	} while (k != 0);
	numC10(rest % c20 + i * c20, var, 10);
}

void numC50(int rest, int *var, int c50)
{
	if (rest < c50)
	{
		numC20(rest, var, 20);
		return;
	}
	int k = 0;
	k = rest / c50;
	int i = 0;
	do
	{
		numC20(rest % c50 + i * c50, var, 20);
		k--;
		i++;
	} while (k != 0);
	numC20(rest % c50 + i * c50, var, 20);
}

void numC100(int rest, int *var, int c100)
{
	if (rest < c100)
	{
		numC50(rest, var, 50);
		return;
	}
	int k = 0;
	k = rest / c100;
	int i = 0;
	do
	{
		numC50(rest % c100 + i * c100, var, 50);
		k--;
		i++;
	} while (k != 0);
	numC50(rest % c100 + i * c100, var, 50);
}

void numC200(int rest, int *var, int c200)
{
	if (rest < c200)
	{
		numC100(rest, var, 100);
		return;
	}
	int k = 0;
	k = rest / c200;
	int i = 0;
	do
	{
		numC100(rest % c200 + i * c200, var, 100);
		k--;
		i++;
	} while (k != 0);
	numC100(rest % c200 + i * c200, var, 100);
}

int main()
{
	int c1 = 1, c2 = 2, c5 = 5, c10 = 10, c20 = 20, c50 = 50, c100 = 100, c200 = 200;
	int var;
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

	if (N < c200)
	{
		if (N < c100)
		{
			if (N < c50)
			{
				if (N < c20)
				{
					if (N < c10)
					{
						if (N < c5)
						{
							if (N < c2)
							{
								var = 1;
							}
							else
							{
								numC2(N, &var, c2);
							}
						}
						else
						{
							numC5(N, &var, c5);
						}
					}
					else
					{
						numC10(N, &var, c10);
					}
				}
				else
				{
					numC20(N, &var, c20);
				}
			}
			else
			{
				numC50(N, &var, c50);
			}
		}
		else
		{
			numC100(N, &var, c100);
		}
	}
	else
	{
		numC200(N, &var, c200);
	}

	printf("All variations: %d", var);

	_getch();

	return 0;
}