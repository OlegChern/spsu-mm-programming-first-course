//
// Created by rinsl_000 on 24.11.2017.
//

#include <stdlib.h>
#include <assert.h>
#include "../headers/bigint.h"
#include "../headers/errors.h"

#define max(a, b) (((a) > (b)) ? (a) : (b))


void bigintInit(BigInt **num, size_t digitsCnt) {
    if ((*num = malloc(sizeof(*num))) == NULL)
        return withError(NOT_ENOUGH_MEMORY);

    if (((*num)->digits = malloc(sizeof(*(*num)->digits) * digitsCnt)) == NULL)
        return withError(NOT_ENOUGH_MEMORY);

    (*num)->length = digitsCnt;
    (*num)->isNegative = 0;
}

void setDigit(BigInt *num, int pos, digit val) {
    if (0 <= pos && pos < num->length)
        num->digits[pos] = val;
    else
        return withError(INCORRECT_PARAMS);
}

/* Suppose that all unstated digits are 0 */
digit getDigit(BigInt *num, int pos) {
    if (0 <= pos && pos < num->length)
        return num->digits[pos];
    else
        return 0;
}

void bigint(BigInt **num, int val) {
    bigintInit(num, 1);
    if (error)
        return withError(error);

    (*num)->length = 1;
    (*num)->isNegative = (char) (val < 0 ? 1 : 0);
    setDigit(*num, 0, (digit) ((*num)->isNegative ? -val : val));
}

/* Comparison with ignoring of signs */
int absoluteCompare(BigInt *a, BigInt *b) {
    if (a->length != b->length)
        return (a->length > b->length ? 1 : -1);

    for (int i = (int) (a->length - 1); i >= 0; ++i) {
        int aDigit = getDigit(a, i);
        int bDigit = getDigit(b, i);

        if (aDigit != bDigit)
            return aDigit > bDigit ? 1 : -1;
    }

    return 0;
}

int compare(BigInt *a, BigInt *b) {
    if (a->isNegative != b->isNegative)
        return a->isNegative ? -1 : 1;

    int sign = a->isNegative ? 1 : -1;

    return sign * absoluteCompare(a, b);
}

/* Helper-function. Checks whether the sum of three digits bigger than MAX_DIGIT_VALUE or not */
char isOverflow(digit a, digit b, digit c) {
    return (char) ((a > MAX_DIGIT_VALUE - b || a + b > MAX_DIGIT_VALUE - c) ? 1 : 0);
}

/* Adds up two BigInts with ignoring of their signs (using their absolute value)
 * and returns the BigInt of their sum */
BigInt *positivesSum(BigInt *a, BigInt *b) {
    BigInt *r;

    // A followed snippet calculates how many digits the result will contain
    digit carry = 0;
    for (int i = 0; i < max(a->length, b->length); ++i)
        carry = (digit) isOverflow(getDigit(a, i), getDigit(b, i), carry);

    bigintInit(&r, max(a->length, b->length) + (carry ? 1 : 0));
    if (error)
        return withError(NOT_ENOUGH_MEMORY), NULL;

    carry = 0;
    for (int i = 0; i < r->length; ++i) {
        setDigit(r, i, getDigit(a, i) + getDigit(b, i) + carry); // Overflow automatically cuts excess
        carry = (digit) isOverflow(getDigit(a, i), getDigit(b, i), carry);
    }

    r->isNegative = 0;

    return r;
}

/* Helper-function. Checks whether the expression 'a - b - c' is bigger than 0 or not */
char isUnderflow(digit a, digit b, digit c) {
    return (char) ((a < b || a - b < c) ? 1 : 0);
}

/* Subtracts two BigInts with ignoring of their signs (using their absolute value)
 * where first is BIGGER than second and returns the BigInt of their difference */
BigInt *positivesDif(BigInt *a, BigInt *b) {
    BigInt *r;

    // A followed snippet calculates how many digits the result will contain
    digit carry = 0;
    int lastUnZero = 0;
    for (int i = 0; i < max(a->length, b->length); ++i) {
        digit tmp = (getDigit(b, i) == 0) ?
                    MAX_DIGIT_VALUE - getDigit(b, i) - carry + 1 + getDigit(a, i) :
                    MAX_DIGIT_VALUE - getDigit(b, i) + 1 - carry + getDigit(a, i);

        if (tmp != 0)
            lastUnZero = i;

        carry = (digit) isUnderflow(getDigit(a, i), getDigit(b, i), carry);
    }

    bigintInit(&r, (size_t) (lastUnZero + 1));
    if (error)
        return withError(NOT_ENOUGH_MEMORY), NULL;

    carry = 0;
    for (int i = 0; i < r->length; ++i) {
        if (isUnderflow(getDigit(a, i), getDigit(b, i), carry)) {
            // MAX_DIGIT_VALUE = BASE - 1, so we must add 1 in the appropriate place of the expression
            if (getDigit(b, i) == 0)
                setDigit(r, i, MAX_DIGIT_VALUE - getDigit(b, i) - carry + 1 + getDigit(a, i));
            else
                setDigit(r, i, MAX_DIGIT_VALUE - getDigit(b, i) + 1 - carry + getDigit(a, i));

            carry = 1;
        } else {
            setDigit(r, i, getDigit(a, i) - getDigit(b, i)  - carry);
            carry = 0;
        }
    }

    r->isNegative = 0;

    return r;
}

/* Calculates a sum of two BigInts */
BigInt *sum(BigInt *a, BigInt *b) {
    if (a->isNegative == b->isNegative) {
        BigInt *res = positivesSum(a, b);
        if (error)
            return withError(error), NULL;

        res->isNegative = a->isNegative;
        return res;
    }

    /* Swap in the sake of simplicity */
    if (a->isNegative) {
        BigInt *c = a;
        a = b;
        b = c;
    }

    /* Now we can assert that a is positive, b is negative */
    if (absoluteCompare(a, b) >= 0)
        return positivesDif(a, b);
    else {
        BigInt *res = positivesSum(b, a);
        if (error)
            return withError(error), NULL;

        res->isNegative = 1;
        return res;
    }
}