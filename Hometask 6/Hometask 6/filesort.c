#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <memoryapi.h>
#include <string.h>
#include "filesort.h"

char *getMappedFileView(const WCHAR *fileName, FileMapParams *fileMapParams)
{
	fileMapParams->fileHandle = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (fileMapParams->fileHandle == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}
	DWORD fileSizeHigh;
	fileMapParams->fileSize = GetFileSize(fileMapParams->fileHandle, &fileSizeHigh);
	fileMapParams->mapHandle = CreateFileMapping(fileMapParams->fileHandle, NULL, PAGE_READWRITE, fileSizeHigh, fileMapParams->fileSize, NULL);
	if (fileMapParams->mapHandle == NULL)
	{
		return NULL;
	}
	char *result = (char*)MapViewOfFile(fileMapParams->mapHandle, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	return result;
}

void replaceAndCount(char *dest, size_t size, char from, char to, int *count)
{
	*count = 0;
	while (size--)
	{
		if (*dest == from)
		{
			*dest = to;
			++*count;
		}
		dest++;
	}
}

int compareFunc(const void *a, const void *b)
{
	return strcmp(*(const char**)a, *(const char**)b);
}

char** getStrings(char *view, size_t size, int count)
{
	char **result = (char**)calloc(count, sizeof(char*));
	char **current = result;
	*current++ = view;
	size--;
	while (size--)
	{
		if (*view++ == 0)
		{
			*current++ = view;
		}
	}
	return result;
}

void copyStrings(char *view, char**ptrs, int strCount)
{
	while (strCount--)
	{
		size_t length = strlen(*ptrs);
		memcpy(view, *ptrs++, length);
		//strcpy_s(view, length, *ptrs++);
		view[length] = '\n';
		view += length + 1;
	}
}

void mergesort(char **ptrsA, int strCount)
{
	if (strCount <= 1) return;
	int halfA = strCount >> 1;
	int halfB = strCount - halfA;
	char **ptrsB = ptrsA + halfA;
	mergesort(ptrsA, halfA);
	mergesort(ptrsB, halfB);
	char **buf = (char**)malloc(halfA * sizeof(char*));
	memcpy(buf, ptrsA, halfA * sizeof(char*));
	char **ptrsAEnd = buf + halfA;
	char **ptrsBEnd = ptrsB + halfB;
	char **ptrA = buf, **ptrB = ptrsB, **ptrC = ptrsA;
	while (ptrA < ptrsAEnd && ptrB < ptrsBEnd)
	{
		if (strcmp(*ptrA, *ptrB) < 0)
		{
			*ptrC++ = *ptrA++;
		}
		else
		{
			*ptrC++ = *ptrB++;
		}
	}
	while (ptrA < ptrsAEnd)
	{
		*ptrC++ = *ptrA++;
	}
	while (ptrB < ptrsBEnd)
	{
		*ptrC++ = *ptrB++;
	}
	free(buf);
}

