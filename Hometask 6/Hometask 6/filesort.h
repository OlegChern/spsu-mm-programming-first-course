#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <memoryapi.h>
#include <string.h>

typedef struct _FileMapParams {
	DWORD fileSize;
	HANDLE fileHandle;
	HANDLE mapHandle;
} FileMapParams;

char *getMappedFileView(const WCHAR *, FileMapParams *);
void replaceAndCount(char *, size_t, char, char, int *);
int compareFunc(const void *, const void *);
char** getStrings(char *, size_t, int);
void copyStrings(char *, char**, int);
void mergesort(char **, int);