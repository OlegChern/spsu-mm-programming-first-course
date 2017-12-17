#include <stdlib.h>
#include <stdio.h>

#include "DigitalRoot.h"

int main()
{
	printf("Sum of MRDS(n), where n = 2..999999:\n");

	WORD sum = findSumMDRS();

	printf("%d", sum);

	return 0;
}

WORD findSumMDRS()
{
	WORD *MDRS = (WORD*)malloc(sizeof(WORD) * 1000000);
	WORD sum = 0;

	for (WORD n = 2; n <= 10; n++)
	{
		MDRS[n] = n;
		sum += n;
	}

	for (WORD n = 10; n <= 999999; n++)
	{
		MDRS[n] = getDigitalRoot(n);

		DIVIDERS *dividers = getDividers(n);

		for (WORD i = 0; i < dividers->count; i++) // foreach divider
		{
			WORD divider = dividers->arr[i];
			WORD curSum = getDigitalRoot(divider) + MDRS[n / divider];

			if (curSum > MDRS[n])
			{
				MDRS[n] = curSum;
			}
		}

		sum += MDRS[n];
	}

	free(MDRS);
	return sum;
}

WORD getDigitalRoot(WORD n)
{
	return n - 9 * (WORD)((n - 1) / 9);
}

DIVIDERS *getDividers(WORD n)
{
	DIVIDERS *dividers = (DIVIDERS*)malloc(sizeof(DIVIDERS));

	WORD count = 0, allocated = CHUNK;
	WORD *arr = (WORD*)malloc(sizeof(WORD) * CHUNK);

	for (WORD i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
		{
			arr[count] = i;
			count++;

			if (count >= allocated)
			{
				allocated += CHUNK;
				arr = (WORD*)realloc(arr, sizeof(WORD) * allocated);
			}
		}
	}

	dividers->count = count;
	dividers->arr = arr;

	return dividers;
}