#include <memory.h>
#include <string.h>
#include <stdio.h>
#include "bigint.h"
#define _CRT_SECURE_NO_WARNINGS

BigInteger *allocate(size_t);
void add(UINT16 *, UINT32);
void truncate(BigInteger *);
void divmod(BigInteger *, BigInteger *, UINT16, UINT16 *);

void divmod(BigInteger *a, BigInteger *res, UINT16 d, UINT16 *mod)
{
	UINT32 pass = 0;
	int i;
	UINT16 *c = a->chunks;
	UINT16 *rc = res->chunks;
	for (i = a->length - 1; i >= 0; i--)
	{
		pass <<= 16;
		pass += c[i];
		rc[i] = pass / d;
		pass %= d;
	}
	*mod = pass;
	truncate(res);
}

BigInteger *allocate(size_t len)
{
	BigInteger *res = malloc(sizeof(BigInteger));
	res->chunks = calloc(sizeof(UINT16), len);
	res->length = len;
	return res;
}

void truncate(BigInteger *a)
{
	size_t oldLen = a->length;
	while (a->length > 1 && a->chunks[a->length - 1] == 0) a->length--;
	if (a->length < oldLen)
	{
		realloc(a->chunks, sizeof(UINT16) * a->length);
	}
}

void add(UINT16 *chunks, UINT32 digit)
{
	while (digit)
	{
		UINT32 less = *chunks + (digit & 0xFFFFu);
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
	unsigned int i, j;
	for (i = 0; i < resLen; i++)
	{
		for (j = 0; j <= i; j++)
		{
			if (j < a->length && i - j < b->length)
			{
				UINT32 digit = a->chunks[j] * b->chunks[i - j];
				add(res->chunks + i, digit);
			}
		}
	}
	truncate(res);
	return res;
}

BigInteger *create(UINT16 v)
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
	char *res = calloc(5 * a->length + 1, 1);
	memset(res, '0', 5 * a->length);
	char *ptr = res + 5 * a->length;
	BigInteger *oldA = a;
	while (a->length > 1 || a->chunks[0])
	{
		UINT16 digit;
		divmod(a, a, 10, &digit);
		*--ptr = '0' + digit;
	}
	ptr = res;
	while (ptr[0] == '0' && ptr[1] != 0) ptr++;
	char *allRes = malloc(strlen(ptr) + 1);
	strcpy_s(allRes, strlen(ptr) + 1, ptr);
	free(res);
	return allRes;
}

char *toStringHex(BigInteger *a)
{
	char *res = malloc(5 * a->length+1);
	char *ptr = res;
	int i;
	for (i = a->length - 1; i >= 0; i--)
	{
		sprintf(ptr, "%04x ", a->chunks[i]);
		ptr += 5;
	}
	return res;
}

