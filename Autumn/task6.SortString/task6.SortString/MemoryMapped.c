#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "MemoryMapped.h"


FileMapping *createFileMaping(char *nameOfFile)
{
	HANDLE hFile = CreateFileA(nameOfFile, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}
	DWORD temp;
	DWORD dwFileSize = GetFileSize(hFile, &temp);
	if (dwFileSize == INVALID_FILE_SIZE)
	{
		CloseHandle(hFile);
		return NULL;
	}

	HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);
	if (hMapping == NULL)
	{
		CloseHandle(hFile);
		return NULL;
	}

	unsigned char* dataPtr = (unsigned char*)MapViewOfFile(hMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, dwFileSize);
	if (dataPtr == NULL)
	{
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return NULL;
	}

	FileMapping* mapping = (FileMapping*)malloc(sizeof(FileMapping));
	if (mapping == NULL)
	{
		UnmapViewOfFile(dataPtr);
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return NULL;
	}

	mapping->hFile = hFile;
	mapping->hMapping = hMapping;
	mapping->dataPtr = dataPtr;
	mapping->fsize = (size_t)dwFileSize;
	return mapping;
}

void closeMapping(FileMapping *mapping)
{
	UnmapViewOfFile(mapping->dataPtr);
	CloseHandle(mapping->hMapping);
	CloseHandle(mapping->hFile);
	free(mapping);
}