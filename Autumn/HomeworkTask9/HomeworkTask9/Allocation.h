#pragma once

#include <stdlib.h>
#include <stdio.h>

#define TRUE			1
#define FALSE			0

#define MEMORYSIZE		1024			// count of WORDs

typedef char			BOOL;
typedef unsigned short	USHORT;

typedef int				WORD;
typedef unsigned int	UINT;

#pragma pack(1)

typedef struct
{
	USHORT		isFree		: 1;		// sizeof(CHUNK) = 2
	USHORT		wordCount	: 15;		// size of chunk in sizeof(WORD)
} CHUNK;

typedef struct
{
	WORD		*info;
	CHUNK		*chunks;
	UINT		availableCount;
} MEMORY;

#pragma pack()

void*			myMalloc	(UINT);
void			myFree		(void*);
void*			myRealloc	(void*, UINT);

void			init();		// initialize 
void			close();	// free all allocated memory

MEMORY			memory;