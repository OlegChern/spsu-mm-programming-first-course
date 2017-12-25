//
// Created by rinsler on 23.12.17.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../headers/memory_manager.h"

#define min(a, b) (((a) > (b)) ? (b) : (a))

/* States how many free blocks can be isolated from each other at the same time.
 * In other words shows the maximum fragmentation of the memory system.
 * 10000000 by the default. So the list of free blocks will take ~ 150 Mb. */
#define MAX_FREE_BLOCK_COUNT 10000000

/* States how many memory blocks can be given at the same time.
 * 10000000 by the default. So the list of taken blocks will take ~ 150 Mb. */
#define MAX_TAKEN_BLOCK_COUNT 10000000


void *memory;

/* Free list is used to search blocks with enough space to allocate new piece in myMalloc.
 * FreeList is ordered by sizes. Adjacent blocks are merged in one if they lie successively
 * in virtual memory. */
Block *freeList;
size_t freeListSize;

/* Taken list is used to store records in format (ptr, size), where for every previously
 * allocated by myAlloc ptr matched requested size. That records are used by myFree to
 * determine memory block which must be freed. TakenList is ordered by pointers. */
Block *takenList;
size_t takenListSize;


void init(size_t size)
{
    freeList = malloc(MAX_FREE_BLOCK_COUNT * sizeof(Block));
    if (!freeList)
        exit(1);

    memory = malloc(size);

    if (!memory)
    {
        free(freeList);
        exit(1);
    }

    freeList[0].ptr = memory;
    freeList[0].size = size;
    freeListSize = 1;

    takenList = malloc(MAX_TAKEN_BLOCK_COUNT * sizeof(Block));
    if (!takenList)
    {
        free(freeList);
        free(memory);
        exit(1);
    }

    takenListSize = 0;
}

void terminate()
{
    free(takenList);
    free(freeList);
    free(memory);
}

/* Return position in the takenList of the first block which ptr is not lower than given.
 * If there is not such block returns takenListSize.*/
size_t findInTaken(void *ptr)
{
    ssize_t l = -1;
    ssize_t r = takenListSize;

    while (r - l > 1)
    {
        ssize_t m = (l + r) / 2;

        if (takenList[m].ptr >= ptr)
            r = m;
        else
            l = m;
    }

    return (size_t) r;
}

/* Return position in the freeList of the first block which size is not lower than given.
 * If there is not such block returns freeListSize.*/
size_t findInFree(size_t size)
{
    ssize_t l = -1;
    ssize_t r = freeListSize;

    while (r - l > 1)
    {
        ssize_t m = (l + r) / 2;

        if (freeList[m].size >= size)
            r = m;
        else
            l = m;
    }

    return (size_t) r;
}

void removeFrom(Block *lst, size_t *len, size_t p)
{
    memmove(lst + p, lst + p + 1, (*len - p - 1) * sizeof(Block));
    (*len)--;
}

void insertInto(Block *lst, size_t *len, Block b, size_t p)
{
    if (*len + 1 > (lst == freeList ? MAX_FREE_BLOCK_COUNT : MAX_TAKEN_BLOCK_COUNT))
    {
        terminate();
        exit(1);
    }

    memmove(lst + p + 1, lst + p, (*len - p) * sizeof(Block));
    lst[p] = b;
    (*len)++;
}

/* Adds freed memory block into the freeList according to the size ordering and with attempts to merge
 * new block by pointers with other blocks. */
void addToFree(Block b)
{
    // attempt to merge with the left block
    int l = -1;
    for (int i = 0; i < freeListSize; ++i)
        if (freeList[i].ptr + freeList[i].size == b.ptr)
        {
            l = i;
            break;
        }
    if (l != -1)
    {
        b.ptr = freeList[l].ptr;
        b.size += freeList[l].size;
        removeFrom(freeList, &freeListSize, (size_t) l);
    }

    // attempt to merge with the right block
    int r = -1;
    for (int i = 0; i < freeListSize; ++i)
        if (b.ptr + b.size == freeList[i].ptr)
        {
            r = i;
            break;
        }
    if (r != -1)
    {
        b.size += freeList[r].size;
        removeFrom(freeList, &freeListSize, (size_t) r);
    }

    insertInto(freeList, &freeListSize, b, findInFree(b.size));
}

void addToTaken(Block b)
{
    insertInto(takenList, &takenListSize, b, findInTaken(b.ptr));
}

void *myMalloc(size_t size)
{
    size_t p = findInFree(size);
    if (p == freeListSize)
        return NULL;

    Block taken = {freeList[p].ptr, size};
    Block leftover = {freeList[p].ptr + size, freeList[p].size - size};

    removeFrom(freeList, &freeListSize, p);

    if (leftover.size)
        addToFree(leftover);

    addToTaken(taken);

    return taken.ptr;
}

void *myCalloc(size_t cnt, size_t size)
{
    void *r = myMalloc(cnt * size);
    if (!r)
        return r;

    memset(r, 0, cnt * size);
    return r;
}

void myFree(void *ptr)
{
    size_t p = findInTaken(ptr);
    if (p == takenListSize)
    {
        terminate();
        exit(1);
    }

    Block freed = takenList[p];
    removeFrom(takenList, &takenListSize, p);

    addToFree(freed);
}

void *myRealloc(void *ptr, size_t size)
{
    size_t p = findInTaken(ptr);
    if (p == takenListSize)
    {
        terminate();
        exit(1);
    }

    void* res = myMalloc(size);

    if (res)
        memmove(res, ptr, min(size, takenList[p].size));

    myFree(ptr);
    return res;
}

void printFree()
{
    printf("freeList:\nsize: %zu\n", freeListSize);
    for (int i = 0; i < freeListSize; ++i)
        printf("%llu %zu | ", (unsigned long long) freeList[i].ptr % 10000, freeList[i].size);

    printf("\n\n");
}

void printTaken()
{
    printf("takenList:\nsize: %zu\n", takenListSize);
    for (int i = 0; i < takenListSize; ++i)
        printf("%llu %zu | ", (unsigned long long) takenList[i].ptr % 10000, takenList[i].size);

    printf("\n\n");
}