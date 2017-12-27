#pragma once

#include <stdlib.h>
#include <stdio.h>

#define FALSE			0
#define TRUE			1

#define CHUNK			8

#define NUMBEROFCOINS	8

typedef unsigned long long ULL;

ULL count(int, int*, ULL*);
int getInt(int*);