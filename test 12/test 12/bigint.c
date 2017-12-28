#include <memory.h>
#include "bigint.h"

#define _CRT_SECURE_NO_WARNINGS

BigInteger *allocate(size_t);
void add(unsigned short*, unsigned int);
void truncate(BigInteger *);

BigInteger *allocate(size_t len)
{
	BigInteger *res = malloc(sizeof(BigInteger));
	res->chunks = calloc(sizeof(unsigned short), len);
	res->length = len;
	return res;
}

void truncate(BigInteger *a)
{
	size_t oldLen = a->length;
	while (a->length > 1 && a->chunks[a->length - 1] == 0) a->length--;
	if (a->length < oldLen)
	{
		realloc(a->chunks, sizeof(unsigned short) * a->length);
	}
}

void add(unsigned short *chunks, unsigned int digit)
{
	while (digit)
	{
		unsigned int less = *chunks + (digit & 0xFFFFu);
		*chunks = less & 0xFFFF;
		digit >>= 16;
		digit += less >> 16;
		chunks++;
	}
}

BigInteger *multiply(BigInteger *a, BigInteger *b)
{
	size_t resLen;
	BigInteger *res = allocate(resLen = a->length + b->length);
	int i, j;
	for (i = 0; i < resLen; i++)
	{
		for (j = 0; j <= i; j++)
		{
			if (j < a->length && i - j < b->length)
			{
				unsigned int digit = a->chunks[j] * b->chunks[i - j];
				add(res->chunks + i, digit);
			}
		}
	}
	truncate(res);
	return res;
}

BigInteger *create(unsigned short v)
{
	BigInteger *res = allocate(1);
	res->chunks[0] = v;
	return res;
}

void destroy(BigInteger *a)
{
	free(a->chunks);
	free(a);
}

char *toString(BigInteger *a)
{
	char *res = malloc(5 * a->length);
	char *ptr = res;
	int i;
	for (i = a->length - 1; i >= 0; i--)
	{
		sprintf_s(ptr, "%04x ", a->chunks[i]);
		ptr += 5;
	}
	return res;
}

