#include<stdio.h>
#include<malloc.h>
#include "long.h"

BigInt *BigIntIni(int size)
{
    BigInt *num = malloc(sizeof(BigInt));
    num->digits = malloc(size * sizeof(int*));
    int i;
    for (i = 0; i < size; ++i)
    {
        num->digits[i] = 0;
    }
    num->digits_count = size;
    return num;
}

BigInt *BigIntFrmInt(int _num)
{
    BigInt *num = malloc(sizeof(BigInt));
    int temp_arr[kIniSize];
    int digits_count = 0;
    int remainder = _num;
    while (remainder / kBase > 0)
    {
        temp_arr[digits_count] = remainder % kBase;
        remainder = remainder / kBase;
        digits_count++;
    }
    temp_arr[digits_count] = remainder;
    digits_count++;
    num->digits = malloc(digits_count * sizeof(int*));
    int i;
    for (i = 0; i < digits_count; ++i)
    {
        num->digits[i] = temp_arr[i];
    }
    num->digits_count = digits_count;
    return num;
}

BigInt* BigIntCopy(BigInt* that)
{
    BigInt* num = BigIntIni(that->digits_count);
    int i;
    int size = that->digits_count;
    for (i = 0; i < size; i++)
    {
        num->digits[i] = that->digits[i];
    }
    return num;
}

int getRealLength(BigInt *num)
{
    if (num->digits[num->digits_count - 1] == 0)
    {
        return num->digits_count - 1;
    }
    int res = num->digits_count;
    return res;
}

char getHexidecimal(int digit)
{
    if (digit<10)
        return digit + '0';
    return digit - 10 + 'A';
}

void BigIntOutput(BigInt *num)
{
    int i;
    for (i = getRealLength(num); i > 0; --i)
    {
        printf("%c", getHexidecimal(num->digits[i - 1]));
    }
}

void BigIntDelete(BigInt **num)
{
    if (*num == 0)
    {
        return;
    }
    free((*num)->digits);
    free(*num);
}

BigInt *addBigInt(BigInt *first, BigInt *second)
{
    BigInt *temp;
    if (getRealLength(first) > getRealLength(second))
    {
        temp = second;
        second = first;
        first = temp;
    }
    BigInt *res = BigIntIni(getRealLength(second) + 1);
    int tmp = 0;
    int i;
    for (i = 0; i < getRealLength(first); ++i)
    {
        res->digits[i] = (first->digits[i] + second->digits[i] + tmp) % kBase;
        tmp = (first->digits[i] + second->digits[i] + tmp) / kBase;
    }
    for (i = getRealLength(first); i < getRealLength(second); ++i)
    {
        res->digits[i] = (second->digits[i] + tmp) % kBase;
        tmp = (second->digits[i] + tmp) / kBase;
    }
    res->digits[getRealLength(second)] = tmp;
    return res;
}

BigInt *MultiplyBigInt(BigInt *first, BigInt *second)
{
    BigInt *res = BigIntIni(getRealLength(first) + getRealLength(second));
    int j;
    int i;
    for (j = 0; j < getRealLength(second); ++j)
    {
        int remainder = 0;
        for (i = 0; i < getRealLength(first); ++i)
        {
            int t = first->digits[i] * second->digits[j] + remainder + res->digits[i + j];
            res->digits[i + j] = t % kBase;
            remainder = t / kBase;
        }
        res->digits[j + getRealLength(first)] = remainder;
    }
    return res;
}

BigInt *BigIntPow(BigInt *num, int pow)
{
    if (pow == 1)
    {
        BigInt *one = BigIntFrmInt(1);
        BigInt *res = MultiplyBigInt(one, num);
        BigIntDelete(&one);
        return res;
    }

    if (pow % 2 == 1)
    {
        BigInt *current = BigIntPow(num, pow - 1);
        BigInt *res = MultiplyBigInt(current, num);
        BigIntDelete(&current);
        return res;
    }

    BigInt *sqrt = BigIntPow(num, pow / 2);
    BigInt *res = MultiplyBigInt(sqrt, sqrt);
    BigIntDelete(&sqrt);
    return res;
}

