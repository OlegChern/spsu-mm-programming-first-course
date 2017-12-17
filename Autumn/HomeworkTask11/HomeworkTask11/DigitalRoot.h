#pragma once

#define TRUE	1
#define CHUNK	4

#define EPS		1.0f


typedef int WORD;

typedef struct
{
	WORD count;
	WORD *arr;
} DIVIDERS;

WORD		MRDS(WORD);
WORD		getDigitalRoot(WORD);
WORD		findSumMDRS();

// find count of dividers and write them to array 
DIVIDERS	*getDividers(WORD);