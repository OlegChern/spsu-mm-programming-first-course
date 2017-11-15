#include <stdio.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

int main()
{
	int v[8];
	v[0] = 1;
	v[1] = 2;
	v[2] = 5;
	v[3] = 10;
	v[4] = 20;
	v[5] = 50;
	v[6] = 100;
	v[7] = 200;


	int d[8][30001];
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 30001; j++)
		{
			d[i][j] = 0;
		}
	}
	d[0][0] = 1;

	for (int i = 0; i < 30000; i++)
		for (int j = 0; j < 8; j++)
			for (int k = j; k < 8; k++)
				if (i + v[k] <= 30000)
					d[k][i + v[k]] += d[j][i];

	int n;
	scanf_s("%d", &n);
	int ans = 0;
	for (int i = 0; i < 5; i++)
		ans += d[i][n];

	if (ans > 1)
		printf("There are %llu ways to produce %d change.\n", ans, n);
	else
		printf("There is only 1 way to produce %d change.\n", n);


	return 0;
}
