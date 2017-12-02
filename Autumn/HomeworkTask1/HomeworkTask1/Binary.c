#include <stdlib.h>
#include <stdio.h>

#define SURNAME 11
#define NAME 7
#define MIDDLENAME 11

#define LITTLEENDIAN (*(char *)&(int){1})

void printBinary(char*, int);

int main()
{
	int compos = SURNAME * NAME * MIDDLENAME;
	printf("Compostion: %d\n", compos);

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
	unsigned char bit;

#ifdef LITTLEENDIAN

	for (int i = size - 1; i >= 0; i--)
	{
		for (int j = 7; j >= 0; j--)
		{
			bit = (number[i] >> j) & 1;
			printf("%u", bit);
		}
	}

#else

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			bit = (number[i] >> j) & 1;
			printf("%u", bit);
		}
	}

#endif // LITTLEENDIAN

	printf("\n");
}