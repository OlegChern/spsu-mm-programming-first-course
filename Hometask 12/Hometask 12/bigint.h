#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED

#include <windows.h>

typedef struct _BigInteger
{
	UINT16 *chunks;
	size_t length;
} BigInteger;

BigInteger *multiply(BigInteger *, BigInteger *);
BigInteger *create(UINT16);
void destroy(BigInteger *);
char *toString(BigInteger *);
char *toStringHex(BigInteger *);

#endif // BIGINT_H_INCLUDED
