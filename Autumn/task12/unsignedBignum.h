#ifndef UNSIGNEDBIGNUM_H
#define UNSIGNEDBIGNUM_H

#include "linkedList.h"

/**
 * Data structure representing a natural number.
 *
 * Digit order is similar to the one
 * on little-endian machines:
 * list->first is the smallest digit,
 * first->next is the second smallest, etc.
 *
 * Note that due to variable length
 * number representation is not unique:
 * booth
 * 00000000 00000000 00000000 00000000
 * and
 * 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
 * represent zero.
 */

/// Beautiful name matters
typedef LinkedList UnsignedBignum;
typedef UnsignedBignum UBN;

UBN *buildUBN(unsigned int);

UBN *cloneUBN(UBN *);

void freeUBN(UBN *ubn);

/// printList() can be used
/// for debugging purposes
void printHexUBN(UBN *);

int isZeroUBN(UBN *);

// Note:
// following methods save their results
// into their first argument

/// Can safely accept two pointers to one UBN
void addUBN(UBN *, UBN *);

void leftShiftUBN(UBN *, unsigned int);

void rightShiftUBN(UBN *, unsigned int);

void multiplyUBN(UBN *, UBN *);

void squareUBN(UBN *);

void powerUBN(UBN *, unsigned int);

#endif // UNSIGNEDBIGNUM_H
