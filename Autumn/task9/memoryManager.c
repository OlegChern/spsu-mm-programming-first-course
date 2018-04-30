#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int kIntSize = sizeof(int);
static const int kCharSize = sizeof(char);
static const int kMemBlockSize = 1024 * 1024 * 1024;

typedef struct MemBlock
{
    unsigned int sz;
    char arr[];
}MemBlock;

void *memoryBuff;

void initializeBuff()
{
    memoryBuff = calloc(kMemBlockSize, 1);
}

int isSufficientSpace(size_t size, char *begin)
{
    if (!size)
        return 1;
    int k;
    for (k = (int)size; (*begin == 0) && (k > 0); k--)
    {
        begin++;
    }
    if (!k)
        return 0;

    return k;
}

unsigned int *findMemoryPos(size_t size, char *begin)
{
    if (begin >= memoryBuff + kMemBlockSize)
        return 0;
    char *memPos;
    for (memPos = begin; *memPos != 0; memPos += *((int *)memPos) + kIntSize + memPos != memoryBuff){}
    if (!isSufficientSpace(size, memPos))
        return (unsigned int *)memPos;
    else
        findMemoryPos(size, memPos + size - 1);
}

void *myMalloc(size_t size)
{
    MemBlock *memoryChunk = (MemBlock *) findMemoryPos(size + kCharSize + kIntSize, memoryBuff);
    if (memoryChunk == 0)
        return 0;
    memoryChunk->sz = (unsigned int)size;
    char *end = memoryChunk->arr + size;
    *end = 0;
    return memoryChunk->arr;
}

void myFree(void *pointer)
{
    unsigned int *freePointer = pointer - kIntSize;
    memset(freePointer, 0, *freePointer + kIntSize);
}

void *myRealloc(void *pointer, size_t newSize)
{
    char *newPointer = pointer - kIntSize;
    unsigned int oldSize = *((unsigned int *)newPointer);
    if (oldSize > newSize)
        return pointer;
    unsigned int difference = (unsigned int)newSize - oldSize;
    unsigned  int size = difference + kCharSize;
    newPointer += oldSize + kIntSize;
    if (!isSufficientSpace(size, newPointer))
    {
        *(newPointer + difference) = 0;
        *((unsigned int *)(pointer - kIntSize)) = (unsigned int)newSize;
        return pointer;
    }
    else
    {
        newPointer = myMalloc(newSize);
        memcpy(newPointer, pointer, oldSize);
        myFree(pointer);
        return newPointer;
    }
}

void freeBuff()
{
    free(memoryBuff);
}

int main()
{
    initializeBuff();
    int *variable = myMalloc(kIntSize * 10);
    int i;
    printf("Let's test our program and allocate memory for a 10 elements array.\nSo here it is:\n");
    for (i = 0; i < 10; i++)
    {
        variable[i] = i;
        printf("%d ", variable[i]);
    }
    freeBuff();

    return 0;
}
