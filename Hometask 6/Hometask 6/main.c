#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <memoryapi.h>
#include <string.h>
#include "filesort.h"

int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <file name>\n", argv[0]);
		exit(1);
	}
	size_t bufLen = strlen(argv[1]) + 1;
	WCHAR *fileName = (WCHAR*)malloc(bufLen * sizeof(WCHAR));
	swprintf(fileName, bufLen, L"%hs", argv[1]);
	FileMapParams fileMapParams;
	char* view = getMappedFileView(fileName, &fileMapParams);
	if (view == NULL)
	{
		printf("Cannot map file %s\n", argv[1]);
		exit(2);
	}
	DWORD fileSize = fileMapParams.fileSize;
	free(fileName);
	char *buffer = (char*)malloc(fileSize);
	memcpy(buffer, view, fileSize);
	int strCount;
	replaceAndCount(buffer, fileSize, '\n', 0, &strCount);
	char **ptrs = getStrings(buffer, fileSize, strCount);
	//mergesort(ptrs, strCount);
	qsort(ptrs, strCount, sizeof(char*), compareFunc);
	copyStrings(view, ptrs, strCount);

	free(buffer);
	UnmapViewOfFile(view);
	CloseHandle(fileMapParams.mapHandle);
	CloseHandle(fileMapParams.fileHandle);
	return 0;
}

