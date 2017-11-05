#include <stdio.h>

#define SURNAME 11
#define NAME 7
#define MIDDLENAME 11
#define CHUNK 8

void printBinary(__int64);

int main()
{
	int compos = SURNAME * NAME * MIDDLENAME;

	__int32 a = (__int32)-compos;
	float b = (float)compos;
	double c = (double)-compos;

	printBinary(a);
	printBinary(b);
	printBinary(c);

	return 0;
}

void printBinary(__int64 source)
{
	char positive = source > 0 ? 1 : 0;
	char* invBinary = (char*)malloc(sizeof(char) * CHUNK); // dynamic array
	size_t chunkSize = 4, index = 0;

	if (!positive)
	{
		printf("-");
		source = -source;
	}

	while (source > 0)
	{
		if (index >= chunkSize)
		{
			chunkSize += CHUNK;
			invBinary = (char*)realloc(invBinary, sizeof(char)*chunkSize);
		}

		invBinary[index++] = (char)(source % 2);
		source /= 2;
	}

	for (int i = index - 1; i >= 0; i--)
	{
		printf("%d", invBinary[i]);
	}

	printf("\n");
}

