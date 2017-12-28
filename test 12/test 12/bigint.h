#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED

typedef struct _BigInteger
{
	unsigned short *chunks;
	size_t length;
} BigInteger;

BigInteger *multiply(BigInteger *, BigInteger *);
BigInteger *create(unsigned short);
void destroy(BigInteger *);
char *toString(BigInteger *);

#endif // BIGINT_H_INCLUDED

