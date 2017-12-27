#pragma once

#include <sys/stat.h>   // for file size
#include <fcntl.h>      // control options for open()
#include <time.h>

// mman.h from here https://code.google.com/archive/p/mman-win32/source
#include "mman.h"

#define TRUE            1
#define CHUNK			256

typedef struct stat     STAT;

#pragma pack(1)
typedef struct
{
    char *start;
    char *end;
} STRING;
#pragma pack()

int sortWithMMap(char*);
void qsortStrings(STRING*, int, int);
int compareStrings(STRING*, STRING*);
void swapStrings(STRING*, STRING*);
