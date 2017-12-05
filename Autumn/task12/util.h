#include "linkedList.h"

#ifndef TASK12_UTIL_H
#define TASK12_UTIL_H

_Static_assert(sizeof(int) == 4, "Code relies on int being exactly 4 bytes");

#define INT_MAX 0xFFFFFFFF

int init();

int xor(int, int);

int logicEqual(int, int);

Element *EMPTY_ELEMENT_ZEROS;
Element *EMPTY_ELEMENT_ONES;

void finish();

#endif //TASK12_UTIL_H
