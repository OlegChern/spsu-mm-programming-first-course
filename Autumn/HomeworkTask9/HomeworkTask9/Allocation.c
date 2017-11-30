#include <stdlib.h>
#include <stdio.h>

#include "Allocation.h"

int main()
{
	init();

	int *a = (int*)myMalloc(sizeof(int));
	*a = 4;

	a = myRealloc(a, sizeof(int) * 2);
	*a = 6;

	myFree(a);

	close();
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

				return (void*)(chunk + 1); // return pointer to data (just shift by sizeof(CHUNK))
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
	chunk--; // shift to chunk data

	chunk->isFree = TRUE;

	size_t chunkSize = memory.lists[chunk->listIndex]->size;
	memory.availableSize += chunkSize;
}

void* myRealloc(void* ptr, size_t newSize)
{
	CHUNK* chunk = (CHUNK*)ptr;
	chunk--; // shift to chunk data, ptr is pointer to data area

	if (chunk->isFree)
	{
		printf("Wasn't allocated!");
		return NULL;
	}

	size_t data = sizeof(char) + sizeof(UCHAR); // beginning of data area
	size_t size = memory.lists[chunk->listIndex]->size; // size of source chunk with variables

	if (newSize < size)
	{
		printf("New size must be larger!");
		return NULL;
	}

	if (memory.availableSize < newSize) // check available memory to allocate
	{
		printf("Not enough memory!");
		return NULL;
	}

	char* charChunk = (char*)ptr;
	char* newCharChunk = (char*)myMalloc(newSize);

	for (size_t i = 0; i < size - data; i++) 	// writing data from source, ONLY data
	{
		newCharChunk[i] = charChunk[i];
	}

	memory.availableSize -= newSize - size;

	return (void*)newCharChunk;
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

void init()
{
	memory.availableSize = 0;
	memory.lists = (CHUNKLIST**)malloc(MAXLISTCOUNT * sizeof(CHUNKLIST*));

	for (int i = 0; i < MAXLISTCOUNT; i++)
	{
		memory.lists[i] = (CHUNKLIST*)malloc(sizeof(CHUNKLIST));

		size_t size = (1 << i) * sizeof(int); // chunk size is power of 2 * sizeof(int)

		memory.lists[i]->size = size;
		memory.lists[i]->chunks = (CHUNK**)malloc(MAXCHUNKCOUNT * sizeof(CHUNK*));

		for (int j = 0; j < MAXCHUNKCOUNT; j++)
		{
			memory.lists[i]->chunks[j] = (CHUNK*)malloc(sizeof(CHUNK) + size);

			memory.lists[i]->chunks[j]->isFree = TRUE;
			memory.lists[i]->chunks[j]->listIndex = i;

			memory.availableSize += size;
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