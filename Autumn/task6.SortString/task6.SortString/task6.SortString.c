// task6.SortString.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "SortStrings.h"
#include "MemoryMapped.h"


int main()
{
	printf("Please enter name of file\n");
	char nameOfFile[100];
	scanf("%s", nameOfFile);
	FileMapping *mapping = createFileMaping(nameOfFile);
	if (mapping == NULL)
	{
		printf("Error!");
		return 0;
	}

	int numberOfStrings = getNumberOfStrings(mapping->dataPtr, mapping->fsize);
	char **strings = sortString(mapping->dataPtr, mapping->fsize, numberOfStrings);
	writeStringsInFile(mapping->dataPtr, strings, numberOfStrings);

	closeMapping(mapping);
	
	return 0;
}

