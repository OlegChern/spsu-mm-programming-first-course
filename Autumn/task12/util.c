#include <malloc.h>

#include "util.h"

int init()
{
    EMPTY_ELEMENT_ZEROS = buildElement(0);
    EMPTY_ELEMENT_ZEROS->next = EMPTY_ELEMENT_ZEROS;

    EMPTY_ELEMENT_ONES = buildElement(INT_MAX);
    EMPTY_ELEMENT_ONES->next = EMPTY_ELEMENT_ONES;
    return 1;
}

int xor(int first, int second)
{
    return (first || second) && !(first && second);
}

int logicEqual(int first, int second)
{
    return !xor(first, second);
}

void finish()
{
    free(EMPTY_ELEMENT_ZEROS);
}
