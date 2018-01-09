#include <stdio.h>
#include <stdlib.h>
#include "MemoryMapped.h"

#include "SortStrings.h"


int compareString(char *str1, char *str2)
{
	char *ptr1 = *(char**)str1;
	char *ptr2 = *(char**)str2;
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

int getNumberOfStrings(unsigned char *filePtr)
{
	unsigned char *temp = filePtr;
	int number = 0;
	/*while(*temp > 0)
	{
		if (*temp == '\n')
		{
			number++;
		}
		temp++;
	}
	number++;*/
	while (*temp > 0)
	{
		while ((*temp != '\n') && (*temp > 0))
		{
			temp++;
		}
		if (*temp <= 0)
		{
			temp--;
		}
		number++;
		temp++;
	}
	return number;
}

char **sortString(char *file, int size, int numberOfString)
{
	char **arrayOfString = malloc(sizeof(char *) * numberOfString);

	int num = 0;
	char *temp = file;
	int i = 0;
	while (*temp > 0)
	{
		arrayOfString[i] = temp;
		i++;
		while ((*temp != '\n') && (*temp > 0))
		{
			temp++;
		}
		if (*temp > 0)
		{
			temp++;
		}
	}
	
	qsort(arrayOfString, numberOfString, sizeof(char*), compareString);

	return arrayOfString;
}

void writeStringsInBuffer(char *file, char** arrayOfString, int numberOfStrings)
{
	for (int i = 0; i < numberOfStrings; i++)
	{
		while ((*arrayOfString[i] != '\n') && (*arrayOfString[i] > 0))
		{
			*file = *arrayOfString[i];
			file++;
			arrayOfString[i]++;
		}
		if (*arrayOfString[i] <= 0)
		{
			*file = '\r';
			file++;
			*file = '\n';
			file++;
		}
		else
		{
			*file = *arrayOfString[i];
			file++;
		}
	}

	free(arrayOfString);
}

void writeStringsInFile(char *file, char** arrayOfString, int numberOfStrings, int size)
{
	HANDLE tempFile, tempMap;
	tempFile = CreateFile("tempFile.txt", GENERIC_READ | GENERIC_WRITE | FILE_DELETE_CHILD, 0, NULL, CREATE_ALWAYS, 0, NULL);
	tempMap = CreateFileMapping(tempFile, NULL, PAGE_READWRITE, 0, size, NULL);
	unsigned char *tempPtr = (unsigned char*)MapViewOfFile(tempMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, size);

	char* temp = tempPtr;
	writeStringsInBuffer(tempPtr, arrayOfString, numberOfStrings);
	tempPtr = temp;
	
	char *dataPtr = file;
	for (int i = 0; i < size; i++)
	{
		*dataPtr = *tempPtr;
		dataPtr++;
		tempPtr++;
	}
	tempPtr = temp;

	UnmapViewOfFile(tempPtr);
	CloseHandle(tempMap);
	CloseHandle(tempFile);
	DeleteFile("tempFile.txt");
}