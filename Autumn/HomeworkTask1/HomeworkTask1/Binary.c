#include <stdlib.h>
#include <stdio.h>

#define SURNAME 11
#define NAME 7
#define MIDDLENAME 11
#define CHUNK 8

void printBinary(char*, int);

int main()
{
	int compos = SURNAME * NAME * MIDDLENAME;

	__int32 a = (__int32)-compos;
	float b = (float)compos;
	double c = (double)-compos;

	printf("A: ");
	printBinary((char*)&a, sizeof(__int32));

	printf("B: ");
	printBinary((char*)&b, sizeof(float));

	printf("C: ");
	printBinary((char*)&c, sizeof(double));

	return 0;
}

void printBinary(char *number, int size)
{
	char bit;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			bit = number[i] >> j;
			printf("%d %d\n", bit, bit & 1);
		}
	}

	printf("\n");
}

