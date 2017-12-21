#pragma once

#include <stdlib.h>
#include <stdio.h>

#define BASE			16		// 16 because then we must print hex
//#define SIMPLEMULTIP	4		// when we can use simple multiplication

#define TRUE			1	

#define MAX(a, b) ( ( (a) > (b) ) ? (a) : (b) )

typedef int 			WORD;	// for values, must contain at least number (BASE ^ 2)
typedef unsigned int	UINT;

typedef struct ArbitraryPrecisionNumber
{
	UINT		amount;			// amount of parts
	WORD		*values;
} APN;

void			printHex(APN*);

APN				*APNPower(APN*, UINT);

APN				*APNSum(APN*, APN*);
APN				*APNSubtract(APN*, APN*);

				// simple multiplication
APN				*APNMultiply(APN*, APN*);

				// take care of carry
void			APNNormalize(APN*);

				// constructors
APN				*APNCreateWithValue(WORD);
APN				*APNCreateWithAmount(UINT);


				// free memory
void			APNFree(APN*);

				// creates a copy of source from one index to another
APN				*APNCopy(APN*, UINT, UINT);

				// resize
void			APNResize(APN*, UINT);