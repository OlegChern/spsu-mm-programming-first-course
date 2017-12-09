#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int mem_size = 1024 * 1024 * 1024;

struct MemPart
{
    unsigned int sz;
    char array[];
};

void *mem;

int isEnough(size_t, char *);

unsigned int *searchForMem(size_t, char *);

void initialize();

void *myMalloc(size_t);

void myFree(void *);

void *myRealloc(void *, size_t);


int main()
{
    initialize();

    int *variable = myMalloc(sizeof(int));

    *variable = 42;

    printf("Allocated memory for one integer variable. Its value is %d, its address is %p\n", *variable, variable);

    int *arrayofint = myMalloc(sizeof(int) * 10);

    printf("\nNow allocated memory to an integer array. Size - 10 elements, its address is %p, its elements are: ",
           arrayofint);

    for (int i = 0; i < 10; i++)
    {
        arrayofint[i] = i + 1;
        printf("%d ", arrayofint[i]);
    }

    double *arrayofdouble = myMalloc(sizeof(double) * 5);

    printf("\n\nAllocated memory to an array of double, Size - 5, its address is %p, elements are: ", arrayofdouble);

    for (int j = 0; j < 5; j++)
    {
        arrayofdouble[j] = j + 1;
        printf("%lf ", arrayofdouble[j]);
    }

    arrayofdouble = myRealloc(arrayofdouble, sizeof(double) * 7);

    arrayofdouble[5] = 6;
    arrayofdouble[6] = 7;

    printf("\n\nReallocated memory for the second array, "
                   "its new size is 7 and its adress is %p "
                   "(it has not chaged since there is enough space to expand it), "
                   "Its elements are: ", arrayofdouble);

    for (int i = 0; i < 7; i++)
    {
        printf("%lf ", arrayofdouble[i]);
    }

    arrayofint = myRealloc(arrayofint, sizeof(int) * 15);

    for (int j = 10; j < 15; j++)
    {
        arrayofint[j] = j + 1;
    }

    printf("\n\nReallocated memory for the first array, "
                   "its new size is 15 and its adress is %p "
                   "(it has changed because there was not enough space for reallocation), "
                   "Its elements are: ", arrayofint);

    for (int j = 0; j < 15; j++)
    {
        printf("%d ", arrayofint[j]);
    }

    myFree(arrayofdouble);
    myFree(arrayofint);
    myFree(variable);

    printf("\n\nMemory is free now");

    free(mem);

    return 0;
}


int isEnough(size_t size, char *memstart)
{
    if (size == 0) return 1;

    int k = (int) size;

    while ((*memstart == 0) && (k > 0))
    {
        k--;
        memstart++;
    }

    if (k == 0)
        return 0;
    else
        return k;

}

unsigned int *searchForMem(size_t size, char *start)
{
    if (start >= mem + mem_size) return NULL; // means that we overstepped the bound of initialized memory

    char *memlook = start;

    while (*memlook != 0)
    {
        memlook += *((int *) memlook) + sizeof(int);
        if (memlook != mem) memlook++;
    }


    int available = isEnough(size, memlook);

    if (!available)
    {
        return (unsigned int *) memlook;
    }
    else
    {
        searchForMem(size, memlook + size - available);
    }
}


void initialize()
{
    mem = malloc(mem_size);
}

void *myMalloc(size_t size)
{
    struct MemPart *memory = (struct MemPart *) searchForMem(size + sizeof(char) + sizeof(int),
                                                             mem); // memory for the array and for 5 bytes of overhead

    if (memory == NULL) return NULL; // if it is impossible to allocate memory

    memory->sz = (unsigned int) size;

    char *end = memory->array + size;
    *end = 0; // indicates the end of the array

    return memory->array;
}

void myFree(void *ptr)
{
    unsigned int *frptr = ptr - sizeof(int);

    memset(frptr, 0, *frptr + sizeof(int));
}

void *myRealloc(void *ptr, size_t new_size)
{
    char *new_ptr = ptr - sizeof(int);
    unsigned int old_size = *((unsigned int *) new_ptr);

    if (old_size > new_size) return ptr;

    unsigned int delta = (unsigned int) new_size - old_size;

    new_ptr += old_size + sizeof(int);

    if (!isEnough(delta + sizeof(char), new_ptr))
    {
        *(new_ptr + delta) = 0;
        *((unsigned int *) (ptr - sizeof(int))) = (unsigned int) new_size;

        return ptr;
    }
    else
    {
        new_ptr = myMalloc(new_size);
        memcpy(new_ptr, ptr, old_size);
        myFree(ptr);

        return new_ptr;
    }
}