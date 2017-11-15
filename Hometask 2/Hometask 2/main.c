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
	scanf_s("%d %d %d", &x, &y, &z);
	if (pythagoreanTriple(x, y, z) == 1)
	{
		printf("Pythagorean triple\n");
		if (nod(x, y) > 1 && nod(z, y) > 1 && nod(x, z) > 1)
		{
			printf("Primitive pythagorean triple\n");
		}
		else
		{
			printf("This not Pythagorean triple\n");
		}

	}
	else
	{
		printf("This not Pythagorean triple\n");
	}
	//printf("%d %d %d \n", x, y, z);
	return 0;
}
