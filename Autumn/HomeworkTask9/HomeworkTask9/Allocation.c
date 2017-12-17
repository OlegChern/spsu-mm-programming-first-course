#include "Allocation.h"

void* myMalloc(UINT size)
{
	if (memory.availableCount < size) // check available memory to allocate
	{
		printf("Not enough memory!");
		return NULL;
	}

	UINT wordCount = size % sizeof(WORD) == 0 ?
		size / sizeof(WORD) :
		size / sizeof(WORD) + 1;

	for (UINT i = 0; i < MEMORYSIZE - wordCount; i++)
	{
		BOOL next = FALSE;
		UINT j = i;

		while (j < wordCount) // check free memory
		{
			if (memory.chunks[j].isFree)
			{
				j++;
			}
			else
			{
				next = TRUE;
				break;
			}
		}

		if (next)
		{
			continue;
		}

		memory.availableCount -= wordCount;

		memory.chunks[i].wordCount = wordCount;

		for (UINT k = i; k < i + wordCount; k++)
		{
			memory.chunks[k].isFree = FALSE;
		}

		return (void*)(&memory.info[i]);
	}

	return NULL;
}

void myFree(void* ptr)
{
	WORD *infoPtr = (WORD*)ptr;
	WORD *infoStart = memory.info;

	UINT index = infoPtr - infoStart; // / sizeof(WORD);

	UINT count = memory.chunks[index].wordCount;

	for (UINT i = index; i < count; i++)
	{
		memory.chunks[index].isFree = TRUE;
	}
}

void* myRealloc(void* ptr, UINT newSize)
{
	WORD *infoStart = memory.info;

	WORD *oldInfoPtr = (WORD*)ptr;
	UINT oldIndex = oldInfoPtr - infoStart; // / sizeof(WORD);

	if (memory.chunks[oldIndex].isFree)
	{
		printf("Wasn't allocated!");
		return NULL;
	}
	
	UINT newCount = newSize % sizeof(WORD) == 0 ?
		newSize / sizeof(WORD) :
		newSize / sizeof(WORD) + 1;

	UINT oldCount = memory.chunks[oldIndex].wordCount;

	if (memory.availableCount < newCount) // check available memory to allocate
	{
		printf("Not enough memory!");
		return NULL;
	}

	WORD *newInfoPtr = (WORD*)myMalloc(newSize);
	UINT newIndex = newInfoPtr - infoStart; // / sizeof(WORD);

	UINT count = newCount > oldCount ? oldCount : newCount; // what info must be copied

	for (UINT i = 0; i < count; i++)
	{
		newInfoPtr[i] = oldInfoPtr[i]; // copy info
	}

	memory.availableCount += newCount - oldCount;

	return (void*)newInfoPtr;
}

void init()
{
	memory.availableCount = sizeof(WORD) * MEMORYSIZE;

	memory.info = (WORD*)malloc(sizeof(WORD) * MEMORYSIZE);

	memory.chunks = (CHUNK*)malloc(sizeof(CHUNK) * MEMORYSIZE);

	for (int i = 0; i < MEMORYSIZE; i++)
	{
		memory.chunks[i].isFree = TRUE;
	}
}

void close()
{
	free(memory.chunks);
	free(memory.info);
}