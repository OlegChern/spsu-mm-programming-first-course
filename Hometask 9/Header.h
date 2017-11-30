#ifndef __HEADER_H__
#define __HEADER_H__

void* myMalloc(size_t size); // – аналог функции malloc
void myFree(void* ptr); // – аналог функции free
void* myRealloc(void* ptr, size_t newSize); // – аналог функции realloc
void init();


#endif // HEADER_H_INCLUDED
