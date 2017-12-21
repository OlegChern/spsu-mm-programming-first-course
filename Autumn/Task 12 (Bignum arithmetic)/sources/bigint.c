//
// Created by rinsl_000 on 24.11.2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/bigint.h"
#include "../headers/errors.h"

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) > (b)) ? (b) : (a))


/* Helper-function. Initialize BigInt pointer without stating his fields */
void bigintPointerInit(BigInt **num)
{
    if ((*num = malloc(sizeof(**num))) == NULL)
        die(NOT_ENOUGH_MEMORY);
}

void bigintInit(BigInt **num, size_t digitsCnt)
{
    bigintPointerInit(num);

    if (((*num)->digits = calloc(digitsCnt, sizeof(*(*num)->digits))) == NULL)
        die(NOT_ENOUGH_MEMORY);

    (*num)->length = digitsCnt;
    (*num)->isNegative = 0;
}

BigInt *bigint(int val)
{
    BigInt *n;

    bigintInit(&n, 1);

    n->isNegative = (char) (val < 0 ? 1 : 0);
    setDigit(n, 0, (digit) (n->isNegative ? -val : val));

    return n;
}

void bigintFree(BigInt **num)
{
    free((*num)->digits);
    free(*num);
    *num = NULL;
}

BigInt *bigintClone(BigInt *n)
{
    BigInt *clone;
    bigintInit(&clone, n->length);
    for (int i = 0; i < clone->length; ++i)
        clone->digits[i] = n->digits[i];
    clone->isNegative = n->isNegative;

    return clone;
}

void setDigit(BigInt *num, int pos, digit val)
{
    if (0 <= pos && pos < num->length)
        num->digits[pos] = val;
    else
        die(INCORRECT_PARAMS);
}

/* Suppose that all unstated digits are 0 */
digit getDigit(BigInt *num, int pos)
{
    if (0 <= pos && pos < num->length)
        return num->digits[pos];
    else
        return 0;
}

/* Comparison with ignoring of signs */
int absoluteCompare(BigInt *a, BigInt *b)
{
    if (a->length != b->length)
        return (a->length > b->length ? 1 : -1);

    for (int i = (int) (a->length - 1); i >= 0; --i)
    {
        digit aDigit = getDigit(a, i);
        digit bDigit = getDigit(b, i);

        if (aDigit != bDigit)
            return aDigit > bDigit ? 1 : -1;
    }

    return 0;
}

int compare(BigInt *a, BigInt *b)
{
    if (a->isNegative != b->isNegative)
        return a->isNegative ? -1 : 1;

    int sign = a->isNegative ? 1 : -1;

    return sign * absoluteCompare(a, b);
}


/*  Some of the functions below contains param doArgsFree.
 * It has been created for the convenient work with dynamic memory.
 * For example, when you have a big formula you usually do not need in
 * saving all intermediate values so you can specify to free them in
 * arithmetic function and not to concern about them yourself.
 *  For instance:
 *      a, b, c
 *      x = (a * b - c * c + a * b * c) * a;
 * Here you want to save just values a, b, c, and final x.
 * So you can write it in code like:
 *      x = prd(
 *            sum(
 *               sbt(prd(a, b, 0), prd(c, c, 0), 3),
 *               prd(a, prd(b, c, 0), 2),
 *               3),
 *            a,
 *            1)
 * Here you manually specified which values you want to free after every arithmetic operation:
 *   @ none  - doArgsFree must be set as 0
 *   @ left  - doArgsFree must be set as 1
 *   @ right - doArgsFree must be set as 2
 *   @ both  - doArgsFree must be set as 3
 *
 * So this way you will free all intermediate values like a * b, c * c, (a * b - c * c + a * b * c) and so on
 * and save just a, b, c, and the result in x.
 *
 * I am hope you enjoy this kind of work.
 * */

/* Helper-function. Checks whether the sum of three digits bigger than MAX_DIGIT_VALUE or not */
char isOverflow(digit a, digit b, digit c)
{
    return (char) ((a > MAX_DIGIT_VALUE - b || a + b > MAX_DIGIT_VALUE - c) ? 1 : 0);
}

/* Sees which arguments should be 'freed' and deleted them. */
void freeArgs(BigInt *a, BigInt *b, char doArgsFree)
{
    if (a == b)
    {
        if (doArgsFree)
            bigintFree(&a);
        return;
    }

    if (doArgsFree & 1)
        bigintFree(&a);
    if (doArgsFree & 2)
        bigintFree(&b);
}

/* Adds up two BigInts with ignoring of their signs (using their absolute value)
 * and returns the BigInt of their sum */
BigInt *positivesSum(BigInt *a, BigInt *b, char doArgsFree)
{
    BigInt *r;

    // A followed snippet calculates how many digits the result will contain
    digit carry = 0;
    for (int i = 0; i < max(a->length, b->length); ++i)
        carry = (digit) isOverflow(getDigit(a, i), getDigit(b, i), carry);

    bigintInit(&r, max(a->length, b->length) + (carry ? 1 : 0));

    carry = 0;
    for (int i = 0; i < r->length; ++i)
    {
        setDigit(r, i, getDigit(a, i) + getDigit(b, i) + carry); // Overflow automatically cuts excess
        carry = (digit) isOverflow(getDigit(a, i), getDigit(b, i), carry);
    }

    r->isNegative = 0;

    freeArgs(a, b, doArgsFree);

    return r;
}

/* Helper-function. Checks whether the expression 'a - b - c' is bigger than 0 or not */
char isUnderflow(digit a, digit b, digit c)
{
    return (char) ((a < b || a - b < c) ? 1 : 0);
}

/* Subtracts two BigInts with ignoring of their signs (using their absolute value)
 * where first is BIGGER than second and returns the BigInt of their difference */
BigInt *positivesDif(BigInt *a, BigInt *b, char doArgsFree)
{
    BigInt *r;

    // A followed snippet calculates how many digits the result will contain
    digit carry = 0;
    size_t lastUnZero = 0;
    for (int i = 0; i < max(a->length, b->length); ++i)
    {
        digit curr;

        if (isUnderflow(getDigit(a, i), getDigit(b, i), carry))
        {
            // MAX_DIGIT_VALUE = BASE - 1, so we must add 1 in the appropriate place of the expression
            if (getDigit(b, i) == 0)
                curr = MAX_DIGIT_VALUE - getDigit(b, i) - carry + 1 + getDigit(a, i);
            else
                curr = MAX_DIGIT_VALUE - getDigit(b, i) + 1 - carry + getDigit(a, i);
        }
        else
            curr = getDigit(a, i) - getDigit(b, i) - carry;

        if (curr != 0)
            lastUnZero = (size_t) i;

        carry = (digit) isUnderflow(getDigit(a, i), getDigit(b, i), carry);
    }

    bigintInit(&r, lastUnZero + 1);

    carry = 0;
    for (int i = 0; i < r->length; ++i)
    {
        if (isUnderflow(getDigit(a, i), getDigit(b, i), carry))
        {
            // MAX_DIGIT_VALUE = BASE - 1, so we must add 1 in the appropriate place of the expression
            if (getDigit(b, i) == 0)
                setDigit(r, i, MAX_DIGIT_VALUE - getDigit(b, i) - carry + 1 + getDigit(a, i));
            else
                setDigit(r, i, MAX_DIGIT_VALUE - getDigit(b, i) + 1 - carry + getDigit(a, i));

            carry = 1;
        }
        else
        {
            setDigit(r, i, getDigit(a, i) - getDigit(b, i) - carry);
            carry = 0;
        }
    }

    r->isNegative = 0;

    freeArgs(a, b, doArgsFree);

    return r;
}

/* Calculates a sum of two BigInts */
BigInt *sum(BigInt *a, BigInt *b, char doArgsFree)
{
    if (a->isNegative == b->isNegative)
    {
        char tmp = a->isNegative;
        BigInt *res = positivesSum(a, b, doArgsFree);

        res->isNegative = tmp;
        return res;
    }

    // After this we can assert that a is positive, b is negative
    if (a->isNegative)
    {
        BigInt *c = a;
        a = b;
        b = c;
    }

    if (absoluteCompare(a, b) >= 0)
        return positivesDif(a, b, doArgsFree);
    else
    {
        BigInt *res = positivesSum(b, a, doArgsFree);

        res->isNegative = 1;
        return res;
    }
}

/* Calculates a difference of two BigInts */
BigInt *sbt(BigInt *a, BigInt *b, char doArgsFree)
{

    /* sbt(a, b) = sum(a, -b)
     * so we must just choose sign of b and call sum
     * but to do it safely we have to clone var b */
    BigInt *tmp;
    bigintInit(&tmp, b->length);
    tmp->digits = b->digits;
    tmp->isNegative = !b->isNegative;

    BigInt *r = sum(a, tmp, 0);
    free(tmp);

    freeArgs(a, b, doArgsFree);

    return r;
}

/* Shifts BigInt. If param shift is positive the shift is left else the shift is right */
BigInt *shift(BigInt *a, int shift, char doArgsFree)
{
    // we do not want to have leading zeros so if the number is 0 we return just 0
    if (a->length == 1 && a->digits[0] == 0)
        return bigint(0);

    if (a->length + shift <= 0)
        return bigint(0);

    BigInt *r;
    bigintInit(&r, a->length + shift);

    if (shift >= 0)
    {
        memset(r->digits, 0, shift * sizeof(digit));
        memcpy(r->digits + shift, a->digits, a->length * sizeof(digit));
    }
    else
        memcpy(r->digits, a->digits - shift, a->length + shift); // here shift is negative

    if (doArgsFree)
        bigintFree(&a);

    return r;
}

/* Calculates product of two BigInts by Karatsuba algorithm */
BigInt *prd(BigInt *a, BigInt *b, char doArgsFree)
{
    BigInt *res;

    // to increase performance
    if (a->length == 1 && getDigit(a, 0) == 0 || b->length == 1 && getDigit(b, 0) == 0)
    {
        freeArgs(a, b, doArgsFree);
        return bigint(0);
    }

    if (a->length == 1 && b->length == 1)
    {
        unsigned long long tmp = 1ULL * getDigit(a, 0) * getDigit(b, 0);

//        digit aDigit = getDigit(a, 0);
//        digit bDigit = getDigit(b, 0);
//        unsigned long long tmp = 1ULL * aDigit *bDigit;

        bigintInit(&res, tmp > MAX_DIGIT_VALUE ? 2 : 1);
        setDigit(res, 0, (digit) tmp);
        if (tmp > MAX_DIGIT_VALUE)
            setDigit(res, 1, (digit) (tmp >> 32));
        res->isNegative = (char) (a->isNegative == b->isNegative ? 0 : 1);

        freeArgs(a, b, doArgsFree);

        return res;
    }

    // equivalent to ceil(max(a->length, b->length) / 2)
    size_t len = (size_t) (max(a->length, b->length) / 2 + max(a->length, b->length) % 2);

    /* Karatsuba algorithm:
     * a = a1 * len + a2
     * b = b1 * len + b2
     * where a1, a2, b1, b2 have len digits maybe with leading zeros */

    /* Using vars with structures instead of pointers will extremely load the program stack so
     * we should avoid this by using heap */
    BigInt *a1, *a2, *b1, *b2;
    bigintInit(&a1, len), bigintInit(&a2, len), bigintInit(&b1, len), bigintInit(&b2, len);

    if (len < a->length)
        memcpy(a1->digits, a->digits + len, (a->length - len) * sizeof(digit));
    if (len < b->length)
        memcpy(b1->digits, b->digits + len, (b->length - len) * sizeof(digit));
    memcpy(a2->digits, a->digits, min(len, a->length) * sizeof(digit));
    memcpy(b2->digits, b->digits, min(len, b->length) * sizeof(digit));

    BigInt *c0 = prd(a2, b2, 0);
    BigInt *c2 = prd(a1, b1, 0);

    // (a1 + a2) * (b1 + b2) - c2 - c0
    BigInt *t1 = sum(a1, a2, 0);
    BigInt *t2 = sum(b1, b2, 0);
    BigInt *c1 = prd(t1, t2, 3);
    c1 = sbt(c1, c2, 1);
    c1 = sbt(c1, c0, 1);

    // res = c2 * len ^ 2 + c1 * len + c0
    // c times len equal to shift(c, len)
    c1 = shift(c1, (int) len, 1);
    c2 = shift(c2, (int) (len * 2), 1);

    BigInt *s = sum(c1, c0, 3);
    res = sum(c2, s, 3);
    res->isNegative = (char) (a->isNegative == b->isNegative ? 0 : 1);

    bigintFree(&a1), bigintFree(&a2), bigintFree(&b1), bigintFree(&b2);
    freeArgs(a, b, doArgsFree);

    return res;
}

/* BigInt pow function by Binary algorithm.
 * Of course, it is silly to make exponent more than int because even 2 ^ n where n > INT_MAX
 * is impossible to be calculated in usual machine in any sane time. */
BigInt *powRec(BigInt *a, int n)
{
    if (n == 0)
        return bigint(1);

    if (n == 1)
    {
        return bigintClone(a);
    }

    if (n % 2 == 0)
    {
        BigInt *t = powRec(a, n / 2);
        return prd(t, t, 3);
    }
    else
    {

        BigInt *tmp = powRec(a, n - 1);

        return prd(tmp, a, 1);
    }
}

/* BigInt pow function. Wrapper for the powRec function. */
BigInt *power(BigInt *a, int n, char doArgsFree)
{
    BigInt *r = powRec(a, n);

    if (doArgsFree)
        bigintFree(&a);

    return r;
}

char toHex(char n)
{
    if ('0' <= n && n <= '9')
        return n;

    switch (n)
    {
        case 58:
            return 'a';
        case 59:
            return 'b';
        case 60:
            return 'c';
        case 61:
            return 'd';
        case 62:
            return 'e';
        case 63:
            return 'f';
        default:
            die(INCORRECT_PARAMS);
    }
}

void digitToHex(digit d, char *buf)
{
    for (int i = 7; i >= 0; --i)
    {
        buf[i] = toHex((char) ('0' + (d & 15))); // d & 15 equivalent to d % 16
        d >>= 4; // equivalent to d /= 16
    }
}

char *bigintToHex(BigInt *a)
{
    char *s;
    if ((s = malloc((a->length * 8 + 1) * sizeof(*s))) == NULL)
        die(NOT_ENOUGH_MEMORY);

    int sIter = 0;

    char buf[8];

    if (a->length == 1 && a->digits[0] == 0)
    {
        s[sIter++] = '0';
        s[sIter] = 0;
        return s;
    }

    // Delete leading zeros from first digit
    digitToHex(getDigit(a, (int) (a->length - 1)), buf);
    for (int i = 0; i < 8; ++i)
        if (!(buf[i] == '0' && sIter == 0))
            s[sIter++] = buf[i];

    for (int i = (int) (a->length - 2); i >= 0; --i)
    {
        digitToHex(getDigit(a, i), buf);
        strncpy(s + sIter, buf, 8);
        sIter += 8;
    }

    s[sIter] = 0;

    return s;
}