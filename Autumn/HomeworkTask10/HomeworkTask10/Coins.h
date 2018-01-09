#pragma once

#include <stdlib.h>
#include <stdio.h>

#define FALSE				0
#define TRUE				1

#define CHUNK				8

#define NUMBEROFCOINS		8

typedef int					WORD;

WORD	count(int, int, int*, WORD**);
int		getNearestCoinIndex(int, int*);
int		getInt(int*);