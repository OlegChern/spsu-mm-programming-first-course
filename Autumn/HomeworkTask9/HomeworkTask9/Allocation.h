#pragma once

#include <stdlib.h>
#include <stdio.h>

#define TRUE			1
#define FALSE			0

#define MEMORYSIZE		1024 // count of int

typedef char			BOOL;
typedef int				WORD;
typedef unsigned int	UINT;

#pragma pack(1)

typedef struct
{
	BOOL		isFree;
	UINT		wordCount;		// size of chunk in sizeof(WORD)
	//UINT		fieldIndex;
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