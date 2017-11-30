#include <stdlib.h>
#include <windef.h>
#include "Header.h"

#define ALL_SIZE 128 // 0x10000

typedef struct _BLOCK
{
    size_t size;
    struct _BLOCK *pred, *next;
} BLOCK;

BLOCK *myFind(size_t size);

size_t allSize;   // размер всей выделенной памяти
void *allMemory = 0;    // адрес выделенной памяти
BLOCK *freeList;     // список свободных блоков памяти

void* myMalloc(size_t size)
{
    if (allMemory == 0) init();
    size_t search = size + sizeof(size_t);
    if (search < sizeof(BLOCK))
    {
        search = sizeof(BLOCK);
    }
    BLOCK *found = myFind(search);
    if (!found) return 0;
    if (found->size > search + sizeof(BLOCK))
    {
        found->size -= search;
        BLOCK *busy = (BLOCK*)((BYTE*)found + found->size);
        busy->size = search;
        return (BYTE*)busy + sizeof(size_t);
    }
    else
    {
        if (found->pred == 0)
        {
            freeList = found->next;
        }
        else
        {
            found->pred->next = found->next;
        }
        if (!found->next)
        {
            found->next->pred = found->pred;
        }
        return (BYTE*)found + sizeof(size_t);
    }
}

void myFree(void* ptr)
{
    if (allMemory == 0) exit(-1);
    BLOCK *busy = (BLOCK*)(ptr - sizeof(size_t));
    if (freeList == 0)
    {
        freeList = busy;
        busy->pred = busy->next = 0;
    }
    else
    {
        BLOCK *prd = 0, *nxt = freeList;
        while (nxt && nxt->next < busy)
        {
            prd = nxt;
            nxt = nxt->next;
        }
        if (!prd)
        {
            busy->next = freeList;
            freeList = busy;
        }
        else
        {
            prd->next = busy;
            busy->pred = prd;
        }
        if (nxt)
        {
            nxt->pred = busy;
        }
        busy->next = nxt;

        if ((BYTE*)busy + busy->size == (BYTE*)nxt)
        {
            busy->next = nxt->next;
            busy->size += nxt->size;
        }
        if (prd && (BYTE*)prd + prd->size == (BYTE*)busy)
        {
            prd->next = busy->next;
            prd->size += busy->size;
        }
    }
}

void* myRealloc(void* ptr, size_t newSize)
{
    if (allMemory == 0) exit(-1);
    BLOCK *busy = (BLOCK*)(ptr - sizeof(size_t));
    if (busy->size >= newSize + sizeof(size_t))
    {
        return ptr;
    }
    else
    {
        void *newPtr = myMalloc(newSize);
        if (newPtr == 0) return 0;
        memcpy(newPtr, ptr, busy->size - sizeof(size_t));
        return newPtr;
    }
}

void init()
{
    if (allMemory) exit(-1);
    allMemory = malloc(allSize = ALL_SIZE);
    if (allMemory == 0)
    {
        exit(-1);
    }
    freeList = (BLOCK*)allMemory;
    freeList->size = allSize;
    freeList->next = freeList->pred = 0;
}

BLOCK *myFind(size_t size)
{
    BLOCK *ptr = freeList;
    while (ptr && ptr->size < size)
    {
        ptr = ptr->next;
    }
    return ptr;
}
