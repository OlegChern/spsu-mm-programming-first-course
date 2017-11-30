#ifndef __HEADER_H__
#define __HEADER_H__

void* myMalloc(size_t size); // � ������ ������� malloc
void myFree(void* ptr); // � ������ ������� free
void* myRealloc(void* ptr, size_t newSize); // � ������ ������� realloc
void init();


#endif // HEADER_H_INCLUDED
