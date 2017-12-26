#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include "Header.h"

int compare(void * x, void * y)
{
	char *x1, *y1;
	x1 = *(char**)x;
	y1 = *(char**)y;

	while ((*x1 != '\n') && (*y1 != '\n'))
	{
		if (*x1 != *y1)
		{
			return *x1 - *y1;
		}
		x1++;
		y1++;
	}
	return ((*x1 == '\n') && (*y1 != '\n')) ? -1 : ((*x1 != '\n') && (*y1 == '\n')) ? 1 : 0;
}


int main()
{
	HANDLE hFile, hMapping;

	char fName[100];
	unsigned char* dataPtr;
	DWORD half;
	DWORD fSize;

	while (1)
	{
		printf("Please enter input file name:\nExample: \"D:\\text.txt\"\n");

		scanf("%s", fName);

		hFile = CreateFile(fName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			printf("Error create file");
			continue;
		}

		half = 0;

		fSize = GetFileSize(hFile, &half);

		if (fSize == INVALID_FILE_SIZE)
		{
			printf("Error fileSize\n");
			continue;
		}

		hMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);

		if (hMapping == NULL)
		{
			printf("Error create mapping\n");
			continue;
		}

		dataPtr = (unsigned char*)MapViewOfFile(hMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

		if (dataPtr == NULL)
		{
			printf("Error array\n");
			continue;
		}
		break;
	}

	fileMap* mapping = (fileMap*)malloc(sizeof(fileMap));

	mapping->dataPtr = dataPtr;
	mapping->fSizeHigh = half;
	mapping->fSize = fSize;
	mapping->hFile = hFile;
	mapping->hMapping = hMapping;

	int numStr = 0;
	char* ptr = dataPtr;

	while (*dataPtr != 0)
	{
		while (*dataPtr != 10)
		{
			dataPtr++;
			if (*dataPtr == 0)
			{
				dataPtr--;
				break;
			}
		}
		numStr++;
		dataPtr++;
	}
	dataPtr = ptr;

	char** array = (char**)malloc(sizeof(char*) * numStr);
	int i = 0;
	while (*dataPtr != 0)
	{
		array[i] = dataPtr;
		i++;
		while (*dataPtr != 10)
		{
			dataPtr++;
			if (*dataPtr == 0)
			{
				dataPtr--;
				break;
			}
		}
		dataPtr++;
	}
	dataPtr = ptr;

	qsort(array, numStr, sizeof(char*), compare);

	HANDLE buff, buffMap;
	unsigned char * buffPtr;

	buff = CreateFile("buff.txt", GENERIC_READ | GENERIC_WRITE | FILE_DELETE_CHILD, 0, NULL, CREATE_ALWAYS, 0, NULL);
	buffMap = CreateFileMapping(buff, NULL, PAGE_READWRITE, 0, mapping->fSize, NULL);
	buffPtr = (unsigned char*)MapViewOfFile(buffMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, mapping->fSize);

	char* g = buffPtr;

	for (i = 0; i < numStr; i++)
	{
		while (*array[i] != '\n')
		{
			*buffPtr++ = *array[i]++;
			if (*array[i] == 0)
			{
				break;
			}
		}
		*buffPtr++ = *array[i];
	}

	buffPtr = g;

	for (i = 0; i < mapping->fSize; i++)
	{
		*dataPtr++ = *buffPtr++;
	}
	buffPtr = g;

	UnmapViewOfFile(buffPtr);
	CloseHandle(buffMap);
	CloseHandle(buff);
	DeleteFile("buff.txt");

	UnmapViewOfFile(mapping->dataPtr);
	CloseHandle(mapping->hMapping);
	CloseHandle(mapping->hFile);
	free(mapping);
	free(array);

	_getch();
	return 0;
}