//
// Created by rinsl_000 on 24.11.2017.
//

#ifndef TASK_12_BIGNUM_ARITHMETIC_BIGINT_H
#define TASK_12_BIGNUM_ARITHMETIC_BIGINT_H

#include <limits.h>

typedef unsigned int digit;
#define MAX_DIGIT_VALUE UINT_MAX

typedef struct tagBigInt
{
    digit *digits;
    size_t length;
    char isNegative;
} BigInt;


void bigintInit(BigInt **num, size_t digitsCnt);

BigInt *bigint(int val);

void bigintFree(BigInt **num);

void setDigit(BigInt *num, int pos, digit val);

digit getDigit(BigInt *num, int pos);

int absoluteCompare(BigInt *a, BigInt *b);

int compare(BigInt *a, BigInt *b);

BigInt *sum(BigInt *a, BigInt *b, char doArgsFree);

BigInt *sbt(BigInt *a, BigInt *b, char doArgsFree);

BigInt *prd(BigInt *a, BigInt *b, char doArgsFree);

BigInt *power(BigInt *a, int n, char doArgsFree);

char *bigintToHex(BigInt *a);

#endif //TASK_12_BIGNUM_ARITHMETIC_BIGINT_H
