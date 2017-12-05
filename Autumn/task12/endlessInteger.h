#ifndef ENDLESSINTEGER_H
#define ENDLESSINTEGER_H

/**
 * Long arithmetic based on linked list.
 *
 * Only runs correctly if sizeof(int) == 4.
 *
 * Digit order is similar to the one
 * on little-endian machines:
 * list->first is the smallest digit,
 * first->next is the second smallest, etc.
 *
 * Empty bignum digits do matter in general case:
 * [0xFFFFFFFF] represents a value of -1,
 * since it's binary encoding is
 * 1111 1111 1111 1111 1111 1111 1111 1111,
 * leftmost bit saying number is negative, whilist
 * [0xFFFFFFFF, 0] represents 4294967295,
 * as it's binary encoding is
 * 0000 0000 0000 0000 0000 0000 0000 0000 1111 1111 1111 1111 1111 1111 1111 1111,
 * leftmost bit saying number is positive.
 *
 * This causes an issue of having
 * multiple possible representations of some numbers, however.
 * For example, booth
 * [0xFFFFFFFF] and [0xFFFFFFFF, 0xFFFFFFFF] encode -1.
 * Hence, normalisation functions have to be run from time to time
 * so that to minimize memory usage.
 */

// TODO: implement negative values support

#include "linkedList.h"

#define HEX_FORMAT_FILL "%08X"
#define HEX_FORMAT_FREE "%X"

const unsigned int LEFT_BIT;
const unsigned long long int INT_MOD;

/// Beautiful name matters
typedef LinkedList EndlessInteger;

EndlessInteger *buildEndlessInteger(unsigned int);

void printHexEndlessInteger(EndlessInteger *endlessInteger);

/// printList() can be used
/// for debugging purposes
void printEndlessInteger(EndlessInteger *);

int endlessIntegerIsPositive(EndlessInteger *);

void negateEndlessInteger(EndlessInteger *);

/// means first += second
void addEndlessInteger(EndlessInteger *, EndlessInteger *);

/// means first -= second
void subtractEndlessInteger(EndlessInteger *, EndlessInteger *);

/// means first *= second
void multiplyEndlessInteger(EndlessInteger *, EndlessInteger *);

/// means first /= second
void divideEndlessInteger(EndlessInteger *, EndlessInteger *);

void freeEndlessInteger(EndlessInteger *);

#endif // ENDLESSINTEGER_H
