#ifndef __MY_MEMORY_MANAGER_H__
#define __MY_MEMORY_MANAGER_H__

void* myMalloc(size_t size); // – àíàëîã ôóíêöèè malloc
void myFree(void* ptr); // – àíàëîã ôóíêöèè free
void* myRealloc(void* ptr, size_t newSize); // – àíàëîã ôóíêöèè realloc
void init();


#endif // __MY_MEMORY_MANAGER_H__INCLUDED

