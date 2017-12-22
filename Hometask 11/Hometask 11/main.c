#include <stdio.h>
#include <stdlib.h>


int DR(int v)
{
	int d = v % 9;
	return d ? d : 9;
}

int main()
{
	unsigned *MDRS = (unsigned int *)malloc(sizeof(unsigned int) * 1000000);

	int i, d;

	for (i = 2; i <= 999999; i++)
	{
		MDRS[i] = DR(i);
		unsigned maxDR = 0;
		for (d = 2; d * d <= i; d++)
		{
			if (i % d != 0) continue;
			if (DR(d) + MDRS[i / d] > maxDR)
			{
				maxDR = DR(d) + MDRS[i / d];
			}
		}
		if (maxDR > MDRS[i])
		{
			MDRS[i] = maxDR;
		}
	}

	unsigned sum = 0;
	for (i = 2; i <= 999999; i++)
	{
		sum += MDRS[i];
	}
	free(MDRS);
	printf("result = %u\n", sum);

	system("pause");
	return 0;
}