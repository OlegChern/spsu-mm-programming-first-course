#pragma once

#include <stdlib.h>
#include <stdio.h>

#define BASE			16
#define SIMPLEMULTIP	4				// when we can use simple multiplication

#define MAX(a, b) ( ( (a) > (b) ) ? (a) : (b) )

typedef int 			WORD;
typedef unsigned int	UINT;

typedef struct ArbitraryPrecisionNumber
{
	UINT		count;			// count of parts
	WORD		*values;
} APN;

void			printHex(APN*);

APN				*APNPower(APN*, UINT);

APN				*APNSum(APN*, APN*);
APN				*APNSubtract(APN*, APN*);

				// simple multiplication
APN				*APNMultiply(APN*, APN*);

				// karatsuba multiplication
APN				*APNKaratsubaMultiply(APN*, APN*);

				// take care of carry
void			APNNormalize(APN*);

				// constructors
APN				*APNCreateWithValue(WORD);
APN				*APNCreateWithCount(UINT);

				// creates a copy of source from one index to another
APN				*copyNumber(APN*, UINT, UINT);

				// free memory
void			APNFree(APN*);

				// resize
void			resizeNumber(APN*, UINT);