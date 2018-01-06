#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*allocating a large amount of memory*/
void init();

/*analog of the function Malloc*/
void* myMalloc(size_t size);

/*analog of the function Free*/
void myFree(void* ptr);

/*analog of the function Realloc*/
void* myRealloc(void* ptr, size_t newSize);

/*freeing memory*/
void memoryEnd();