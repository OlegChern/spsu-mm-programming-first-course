#include <stdio.h>
#include "Allocation.h"

int main()
{
	init();

	return 0;
}

void *myMalloc(size_t size)
{
	for (int i = 0; i < MAXLISTCOUNT; i++)
	{
		if (memory.lists[i].size > size)
		{
			CHUNK *chunk = findFreeChunk(&memory.lists[i]);
			if (chunk != NULL)
			{
				chunk->isFree = FALSE;
				return (void*)chunk;
			}
			else
			{
				printf("Not enough memory!");
				return NULL;
			}
			break;
		}
	}

	return NULL;
}

void myFree(void* ptr)
{
	CHUNK *chunk = ptr;
	chunk->isFree = TRUE;
}

void *myRealloc(void* ptr, size_t newSize)
{
	CHUNK *chunk = (CHUNK*)ptr;

	if (chunk->isFree)
	{
		printf("Wasn't allocated!");
		return NULL;
	}

	size_t over = sizeof(char) + sizeof(UCHAR);
	size_t size = memory.lists[chunk->listIndex].size - over; // size of chunk without variables

	//CHUNK *newChunk = (CHUNK*)myMalloc(newSize);

	char* charChunk = (char*)ptr;
	//char* newCharChunk = (char*)newChunk;
	char* newCharChunk = (char*)myMalloc(newSize);
	
	for (size_t i = over; i < size; i++)
	{
		newCharChunk[i] = charChunk[i];
	}

	//return (void*)newChunk;
	return (void*)newCharChunk;
}