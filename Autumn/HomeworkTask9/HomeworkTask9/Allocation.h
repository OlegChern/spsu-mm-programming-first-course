#pragma once

#define TRUE			1
#define FALSE			0
#define MAXLISTCOUNT	16
#define MAXCHUNKCOUNT	16

typedef unsigned char UCHAR;

typedef struct
{
	char		isFree;
	UCHAR		listIndex;
} CHUNK;

typedef struct
{
	CHUNK**		chunks;
	size_t		size;
} CHUNKLIST;

typedef struct
{
	CHUNKLIST**	lists;
	size_t		availableSize;
} MEMORY;

void*	myMalloc(size_t);
void	myFree(void*);
void*	myRealloc(void*, size_t);

void	init();
void	close(); // free all allocated memory
CHUNK*	findFreeChunk(CHUNKLIST*);

MEMORY	memory;