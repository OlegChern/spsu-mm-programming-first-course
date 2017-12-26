#pragma once

#include "windows.h"

typedef struct
{
	HANDLE hFile;
	HANDLE hMapping;
	DWORD fSizeHigh;
	DWORD fSize;
	unsigned char* dataPtr;
}fileMap;