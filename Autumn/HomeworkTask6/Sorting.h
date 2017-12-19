#pragma once

#include <stdlib.h>
#include <cstdlib.h> // TRY IT
#include <stdio.h>
#include <sys/stat.h>   // for file size
#include <fcntl.h>      // control options for open()
#include <time.h>

// mman.h from here https://code.google.com/archive/p/mman-win32/source
#include "mman.h"

#define TRUE            1

typedef struct stat     STAT;

int sortWithMMap(char*, char*);
int cmpStr(const void*, const void*);
