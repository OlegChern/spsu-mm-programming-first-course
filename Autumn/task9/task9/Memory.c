#include "Memory.h"


int sizeOfMemory = 1024;
void *memory;


typedef struct blockOfMemory
{
	size_t sizeOfBlock;
	struct blockOfMemory *next;
	struct blockOfMemory *previous;
} blockOfMemory;

blockOfMemory *firstBlock = NULL;


void init()
{
	memory = malloc(sizeOfMemory);
	blockOfMemory *block = (blockOfMemory *)memory;
	block->sizeOfBlock = sizeOfMemory;
	block->next = NULL;
	block->previous = NULL;
	firstBlock = block;
}

int enoughMemory(blockOfMemory *block, size_t size)
{
	return (block->sizeOfBlock >= size + sizeof(size_t));
}

blockOfMemory *findFreeMemory(size_t size)
{
	blockOfMemory *tmp = firstBlock;
	while (tmp != NULL)
	{
		if (enoughMemory(tmp, size))
		{
			return tmp;
		}
		tmp = tmp->next;
	}
	
	return NULL;
}

void deleteBlock(blockOfMemory *block)
{
	if (block = firstBlock)
	{
		firstBlock = block->next;
		return;
	}

	if (block->next == NULL)
	{
		block->previous->next = NULL;
		return;
	}
	block->previous->next = block->next;
	block->next->previous = block->previous;
}

void *myMalloc(size_t size)
{
	blockOfMemory *block = findFreeMemory(size);
	if (block == NULL)
	{
		return NULL;
	}

	if (size == block->sizeOfBlock)
	{
		deleteBlock(block);
		return (char *)block + sizeof(size_t);
	}

	block->sizeOfBlock = block->sizeOfBlock - sizeof(size_t) - size;
	blockOfMemory *newBlock = (blockOfMemory *)((char *)block + block->sizeOfBlock);
	newBlock->sizeOfBlock = size + sizeof(size_t);
	return (char *)newBlock + sizeof(size_t);
}

blockOfMemory *findNearestBlock(blockOfMemory *block)
{
	blockOfMemory *tmp = firstBlock;
	while ((tmp->next != NULL) && (tmp->next < block))
	{
		tmp = tmp->next;
	}
	return tmp;
}

void unite(blockOfMemory **first, blockOfMemory **second)
{
	(*first)->next = (*second)->next;
	if ((*second)->next != NULL)
	{
		(*second)->next->previous = (*first);
	}
	(*first)->sizeOfBlock = (*first)->sizeOfBlock + (*second)->sizeOfBlock;
}

void myFree(void *ptr)
{
	blockOfMemory *block = (blockOfMemory*)((char*)ptr - sizeof(size_t));
	
	if (firstBlock == NULL)
	{
		block->previous = NULL;
		block->next = NULL;
		firstBlock = block;
		return;
	}

	blockOfMemory *nearestBlock = findNearestBlock(block);
	if ((nearestBlock->previous != NULL) && (nearestBlock->next != NULL))
	{
		nearestBlock->previous->next = block;
		nearestBlock->next->previous = block;
	}
	else if (nearestBlock->previous != NULL)
	{
		nearestBlock->previous->next = block;
	}
	else if (nearestBlock->next != NULL)
	{
		nearestBlock->next->previous = block;
	}

	if ((block->next != NULL) && (block->next == (char *)block + sizeof(block)))
	{
		unite(&block, &(block->next));
	}
	if ((block->previous != NULL) && (block->previous == (char *)block - sizeof(block)))
	{
		unite((&block->previous), &block);
	}
}

void *myRealloc(void *ptr, size_t newSize)
{
	blockOfMemory *block = (char *)ptr - sizeof(size_t);
	
	if (block->sizeOfBlock - sizeof(size_t) >= newSize)
	{
		return ptr;
	}
	
	blockOfMemory *newPtr = myMalloc(newSize);
	if (newPtr == NULL)
	{
		return NULL;
	}
	memcpy(newPtr, ptr, block->sizeOfBlock - sizeof(size_t));
	myFree(ptr);
	return newPtr;
}

void memoryEnd()
{
	free(memory);
}
