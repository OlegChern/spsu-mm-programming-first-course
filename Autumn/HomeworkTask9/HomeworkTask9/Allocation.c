#include <stdlib.h>
#include <stdio.h>

#include "Allocation.h"

int main()
{
	init();

	int *a = (int*)myMalloc(sizeof(int));

	return 0;
}

void* myMalloc(size_t size)
{
	if (memory.availableSize < size) // check available memory to allocate
	{
		printf("Not enough memory!");
		return NULL;
	}

	for (int i = 0; i < MAXLISTCOUNT; i++)
	{
		size_t chunkSize = memory.lists[i]->size;

		if (chunkSize > size)
		{
			CHUNK* chunk = findFreeChunk(memory.lists[i]);
			if (chunk != NULL)
			{
				chunk->isFree = FALSE;
				memory.availableSize -= chunkSize;

				return (void*)chunk;
			}
			else
			{
				printf("Not enough memory!");
				return NULL;
			}
		}
	}

	return NULL;
}

void myFree(void* ptr)
{
	CHUNK* chunk = ptr;
	chunk->isFree = TRUE;

	size_t chunkSize = memory.lists[chunk->listIndex]->size;
	memory.availableSize += chunkSize;
}

void* myRealloc(void* ptr, size_t newSize)
{
	CHUNK* chunk = (CHUNK*)ptr;

	if (chunk->isFree)
	{
		printf("Wasn't allocated!");
		return NULL;
	}

	size_t over = sizeof(char) + sizeof(UCHAR); // beginning of data area
	size_t size = memory.lists[chunk->listIndex]->size; // size of source chunk with variables
	size_t delta = newSize - size;

	if (newSize < size)
	{
		printf("New size must be larger!");
		return NULL;
	}

	if (memory.availableSize < delta) // check available memory to allocate
	{
		printf("Not enough memory!");
		return NULL;
	}

	char* charChunk = (char*)ptr;
	char* newCharChunk = (char*)myMalloc(newSize);
	
	for (size_t i = over; i < size; i++)
	{
		newCharChunk[i] = charChunk[i]; // writing data from source
	}

	memory.availableSize -= delta;

	return (void*)newCharChunk;
}

void init()
{
	memory.availableSize = 0;
	memory.lists = (CHUNKLIST**)malloc(MAXLISTCOUNT * sizeof(CHUNKLIST*));

	for (int i = 0; i < MAXLISTCOUNT; i++)
	{
		memory.lists[i] = (CHUNKLIST*)malloc(sizeof(CHUNKLIST));

		size_t size = (1 << i) * sizeof(int);

		memory.lists[i]->size = size;
		memory.lists[i]->chunks = (CHUNK**)malloc(MAXCHUNKCOUNT * sizeof(CHUNK*));

		for (int j = 0; j < MAXCHUNKCOUNT; j++)
		{
			memory.lists[i]->chunks[j] = (CHUNK*)malloc(sizeof(CHUNK) + size);

			memory.lists[i]->chunks[j]->isFree = TRUE;
			memory.lists[i]->chunks[j]->listIndex = i;
		}
	}

	printf("Allocation initialization completed.\n");
}

void close()
{
	for (int i = 0; i < MAXLISTCOUNT; i++)
	{
		for (int j = 0; j < MAXCHUNKCOUNT; j++)
		{
			free(memory.lists[i]->chunks[j]);
		}

		free(memory.lists[i]);
	}

	free(memory.lists);
}

CHUNK* findFreeChunk(CHUNKLIST* list)
{
	for (int i = 0; i < MAXCHUNKCOUNT; i++)
	{
		if (list->chunks[i]->isFree)
		{
			return list->chunks[i];
		}
	}

	return NULL;
}