#include "stdlib.h"
#include "stdio.h"
#include "Header.h"

int* multip16(int n, int* a)
{
	int k;
	k = (a[1] * n) / 16;
	a[1] = (a[1] * n) % 16;

	for (int i = 2; i <= a[0]; i++)
	{
		int t = k;
		k = (a[i] * n + t) / 16;
		a[i] = (a[i] * n + t) % 16;
	}
	if (k > 0)
	{
		a[0]++;
		a = (int*)realloc(a, (a[0] + 1) * sizeof(int));
		a[a[0]] = k;
	}

	return a;
}