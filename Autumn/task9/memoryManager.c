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

void *memory_buff;

void initializeBuff()
{
    memory_buff = calloc(kMemBlockSize, 1);
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
    if (begin >= memory_buff + kMemBlockSize)
        return 0;
    char *mem_pos;
    for (mem_pos = begin; *mem_pos != 0; mem_pos += *((int *)mem_pos) + kIntSize + mem_pos != memory_buff){}
    if (!isSufficientSpace(size, mem_pos))
        return (unsigned int *)mem_pos;
    findMemoryPos(size, mem_pos + size - 1);
}

void *myMalloc(size_t size)
{
    MemBlock *memory_chunk = (MemBlock *) findMemoryPos(size + kCharSize + kIntSize, memory_buff);
    if (memory_chunk == 0)
        return 0;
    memory_chunk->sz = (unsigned int)size;
    char *end = memory_chunk->arr + size;
    *end = 0;
    return memory_chunk->arr;
}

void myFree(void *pointer)
{
    unsigned int *free_pointer = pointer - kIntSize;
    memset(free_pointer, 0, *free_pointer + kIntSize);
}

void *myRealloc(void *pointer, size_t new_size)
{
    char *new_pointer = pointer - kIntSize;
    unsigned int old_size = *((unsigned int *)new_pointer);
    if (old_size > new_size)
        return pointer;
    unsigned int difference = (unsigned int)new_size - old_size;
    unsigned  int size = difference + kCharSize;
    new_pointer += old_size + kIntSize;
    if (!isSufficientSpace(size, new_pointer))
    {
        *(new_pointer + difference) = 0;
        *((unsigned int *)(pointer - kIntSize)) = (unsigned int)new_size;
        return pointer;
    }
    new_pointer = myMalloc(new_size);
    memcpy(new_pointer, pointer, old_size);
    myFree(pointer);
    return new_pointer;
}

void freeBuff()
{
    free(memory_buff);
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
