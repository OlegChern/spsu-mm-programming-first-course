#include "util.h"

_Static_assert(sizeof(unsigned int) == 4,
               "Code relies on unsigned int being exactly 4 bytes.");

_Static_assert(sizeof(unsigned long long int) > sizeof(unsigned int),
               "Code relies on unsigned long long int being strictly greater than unsigned int.");

const unsigned long long int INT_MOD = 1ull << 32;

int xor(int first, int second)
{
    return (first || second) && !(first && second);
}
