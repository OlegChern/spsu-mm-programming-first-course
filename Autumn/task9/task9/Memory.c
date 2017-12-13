#include <stdlib.h>
#include "Memory.h"


int sizeOfMemory = 1024;

char *firstMemory;
int *arrayOfMemory;

void init()
{
	int sizeOfArray = sizeOfMemory;
	arrayOfMemory = calloc(sizeOfArray, sizeof(int));
	firstMemory = malloc(sizeOfMemory * sizeof(char));
}

int enoughMemory(int index, size_t size)
{
	for (int i = index; i <= index + size; i++)
	{
		if (arrayOfMemory[i] == 1)
		{
			return 0;
		}
	}
	return 1;
}

void takeMemory(int index, size_t size)
{
	for (int i = index; i < index + size; i++)
	{
		arrayOfMemory[i] = 1;
	}
	arrayOfMemory[size] = 0;
}

void* findFreeMemory(size_t size)
{
	int index = -1;
	while (index < sizeOfMemory - 1)
	{
		index++;
		if (arrayOfMemory[index] == 0)
		{
			if (index < sizeOfMemory - 1)
			{
				index++;
				if (arrayOfMemory[index] == 0)
				{
					if (enoughMemory(index, size))
					{
						takeMemory(index, size);
						return firstMemory + index;
					}
				}
			}
		}
	}
	return NULL;
}

void freeUpMemory(int index)
{
	int i = index;
	while (arrayOfMemory[i] != 0)
	{
		arrayOfMemory[i] = 0;
		i++;
	}
}

int getSize(int index)
{
	int i = index;
	while (arrayOfMemory[i] != 0)
	{
		i++;
	}
	return i - index;
}

void* myMalloc(size_t size)
{
	void *findMemory = findFreeMemory(size);
	if (findMemory == NULL)
	{
		printf("Error! Memory is not enough\n");
		return;
	}
	return findMemory;
}

void myFree(void* ptr)
{
	int firstIndex = (int)((char*)ptr - firstMemory);
	freeUpMemory(firstIndex);
}

void* myRealloc(void* ptr, size_t newSize)
{
	int index = (int)((char*)ptr - firstMemory);
	int oldSize = getSize(index);
	
	if (oldSize == newSize)
	{
		return ptr;
	}

	if (oldSize > newSize)
	{
		freeUpMemory(newSize + 1);
		return ptr;
	}
	
	if (enoughMemory(index + oldSize, newSize - oldSize))
	{
		takeMemory(index + oldSize, newSize - oldSize);
		return ptr;
	}

	char *newPtr = myMalloc(newSize);
	for (int i = 0; i < newSize; i++)
	{
		newPtr[i] = ((char*)ptr)[i];
	}
	myFree(ptr);
	return newPtr;
}

void memoryEnd()
{
	free(arrayOfMemory);
	free(firstMemory);
}
