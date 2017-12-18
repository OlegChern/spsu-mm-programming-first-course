//
// Created by rinsl_000 on 24.11.2017.
//

#ifndef TASK_12_BIGNUM_ARITHMETIC_BIGINT_H
#define TASK_12_BIGNUM_ARITHMETIC_BIGINT_H

#include <limits.h>

typedef unsigned int digit;
#define MAX_DIGIT_VALUE UINT_MAX

typedef struct tagBigInt {
    digit *digits;
    size_t length;
    char isNegative;
} BigInt;

#endif //TASK_12_BIGNUM_ARITHMETIC_BIGINT_H
