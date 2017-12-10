#include <stdio.h>
#include <stdlib.h>
#define _CRT_NO_WARNINGS

int v[] = { 200, 100, 50, 20, 10, 5, 2, 1 };
int len = sizeof(v) / sizeof(int);
int count(int n, int i)
{
	int j;
	if (n == 0) return 1;
	if (i == len - 1) return 1;
	int s = 0;
	int k = n / v[i];
	for (j = 0; j <= k; j++)
	{
		s += count(n - j*v[i], i + 1);
	}
	return s;
}

int main()
{
	int n;
	do {
		printf("Enter a sum : ");
		int count = scanf_s("%d", &n);
		if (count == 1 && n > 0) break;
	} while (1);
	printf("Variants: %d\n", count(n, 0));
	system("pause");
	return 0;
}
