#include<stdio.h>
#include<malloc.h>
#include "long.h"

int main()
{
    int base = 3;
    int power = 5000;
    BigInt *Base = BigIntFrmInt(base);
    BigInt *res = BigIntPow(Base, power);
    BigIntOutput(res);
    BigIntDelete(&Base);
    BigIntDelete(&res);
    return 0;
}
