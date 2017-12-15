#pragma once

#include <stdlib.h>
#include <stdio.h>

#define BASE			1024 * 1024
#define SIMPLEMULTIP	1				// when we can use simple multiplication

#define MAX(a, b) ( ( (a) > (b) ) ? (a) : (b) )

typedef int				WORD;
typedef unsigned int	UINT;

typedef struct ArbitraryPrecisionNumberPart
{
	WORD		value;
	UINT		index;
} APNPart;

typedef struct ArbitraryPrecisionNumber
{
	UINT		count;			// count of parts
	APNPart		**parts;
} APNumber;


void printHex	(APNumber*);

APNumber		*sum(APNumber*, APNumber*);
APNumber		*subtract(APNumber*, APNumber*);
				// simple multiplication
APNumber		*multiplySimply(APNumber*, APNumber*);
				// karatsuba multiplication
APNumber		*karatsubaMultiply(APNumber*, APNumber*);
				// take care of carry
void			normalize(APNumber*);

APNumber		*createNumber(UINT);
				// creates a copy of source from one index to another
APNumber		*copyNumber(APNumber*, UINT, UINT);

APNPart			*createPart(UINT);
APNPart			*createPartWithValue(UINT, UINT);

				// add part to end
void			addPart(APNumber*, APNPart*);
				// add new part to end
void			addNewPart(APNumber*);
				// add new part with value to end 
APNPart			*addNewPartWithValue(APNumber*, UINT);
				// replace part with index or add new one to number
void			addNewPartWithIndex(APNumber*, UINT);

				// resize
void			resizeNumber(APNumber*, UINT);