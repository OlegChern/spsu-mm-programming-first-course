#pragma once

#include <stdlib.h>

#define TRUE			1
#define FALSE			0
#define MAXLISTCOUNT	16
#define MAXCHUNKCOUNT	16

typedef unsigned char UCHAR;

#pragma pack(1)
typedef struct
{
	char		isFree;
	UCHAR		listIndex;
} CHUNK;
#pragma pack()

typedef struct
{
	CHUNK		*chunks;
	size_t		size;
} CHUNKLIST;

typedef struct
{
	CHUNKLIST	*lists;
	size_t		availableSize;
} MEMORY;

MEMORY			memory;

void init()
{
	memory.availableSize = 0;

	memory.lists = (CHUNKLIST*)malloc(MAXLISTCOUNT * sizeof(CHUNKLIST));

	for (int i = 0; i < MAXLISTCOUNT; i++)
	{
		size_t size = (1 << i) * sizeof(int);

		memory.lists[i].size = size;
		memory.lists[i].chunks = (CHUNK*)malloc(sizeof(CHUNK) + size);
		for (int j = 0; j < MAXCHUNKCOUNT; j++)
		{
			memory.lists[i].chunks[j].isFree = TRUE;
			memory.lists[i].chunks[j].listIndex = i;
		}
	}
}

CHUNK *findFreeChunk(CHUNKLIST *list)
{
	for (int i = 0; i < MAXCHUNKCOUNT; i++)
	{
		if (list->chunks[i].isFree)
		{
			return &(list->chunks[i]);
		}
	}
	
	return NULL;
}
