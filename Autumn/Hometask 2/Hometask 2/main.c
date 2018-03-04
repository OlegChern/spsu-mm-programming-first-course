#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WRNINGS

int pythagoreanTriple(int x, int y, int z)
{
	if (pow(x, 2) == pow(y, 2) + pow(z, 2)
		|| pow(y, 2) == pow(x, 2) + pow(z, 2)
		|| pow(z, 2) == pow(x, 2) + pow(y, 2))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int nod(int x, int y)
{
	if (x == 0 || y == 0)
	{
		return 0;
	}
	while (x > 0 && y > 0)
	{
		if (x > y)
		{
			x %= y;
		}
		else
		{
			y %= x;
		}
	}
	return x + y;
}

int main()
{

	int x, y, z;
	do
	{
		printf("enter x y z\n");
		int count = scanf_s("%d%d%d", &x, &y, &z);
		if (count == 3 && x > 0 && y > 0 && z > 0)
			break;
	} while (1);

	if (pythagoreanTriple(x, y, z) == 1)
	{
		printf("Pythagorean triple\n");
		if (nod(nod(x, y), z) == 1)
		{
			printf("Primitive pythagorean triple\n");
		}
		else
		{
			printf("This not Primitive triple\n");
		}
	}
	else
	{
		printf("This not Pythagorean triple\n");
	}

	return 0;
}