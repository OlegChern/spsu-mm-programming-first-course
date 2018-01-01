#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "SortStrings.h"


int compareString(char *str1, char *str2)
{
	char *ptr1 = str1;
	char *ptr2 = str2;
	while ((*ptr1 != '\n') && (*ptr2 == *ptr1))
	{
		ptr1++;
		ptr2++;
	}
	if ((*ptr1 == '\n') && (*ptr2 != '\n'))
	{
		return -1;
	}
	if ((*ptr1 != '\n') && (*ptr2 == '\n'))
	{
		return 1;
	}

	if (*ptr1 == *ptr2)
	{
		return 0;
	}
	if (*ptr1 > *ptr2)
	{
		return 1;
	}
	if (*ptr2 > *ptr1)
	{
		return -1;
	}
}

int getNumberOfStrings(char *filePtr, int size)
{
	unsigned char *temp = filePtr;
	int number = 0;
	for (int i = 0; i < size - 1; i++)
	{
		if (*temp == '\n')
		{
			number++;
		}
	}
	number++;

	return number;
}

char **sortString(char *file, int size, int numberOfString)
{
	char **arrayOfString = malloc(sizeof(char *) * numberOfString);

	int num = 0;
	char *temp = file;
	arrayOfString[0] = temp;
	for (int i = 0; i < size; i++)
	{
		temp++;
		if ((*temp == '\n') || (*temp == 'EOF'))
		{
			arrayOfString[num] = temp;
			num++;
		}
	}

	qsort(arrayOfString, numberOfString, sizeof(char), compareString);

	return arrayOfString;
}

void writeStringsInFile(char *file, char** arrayOfString, int numberOfStrings)
{
	char *tempFile = file;
	for (int i = 0; i < numberOfStrings; i++)
	{
		char *tempArray = arrayOfString[i];
		while ((*tempArray != '\n') && (*tempArray != 'EOF'))
		{
			*file = *tempFile;
		}
		*file = *tempFile;
	}

	free(arrayOfString);
}