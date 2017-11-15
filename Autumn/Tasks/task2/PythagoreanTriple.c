#include <stdio.h>
#include "scan_pos_nums.h"


unsigned int gcd(unsigned int x, unsigned int y)
{
    // x, y > 0
    while (x != 0 && y != 0)
    {
        if (x > y) x %= y;
        else y %= x;
    }
    return y == 0 ? x : y;
}

int main()
{
    unsigned int x, y, z;
    scanPositiveDecimal(3, &x, &y, &z);

    // Sorting
    unsigned int t;
    if (z < y)
    {
        t = z;
        z = y;
        y = t;
    }
    if (z < x)
    {
        t = z;
        z = x;
        x = t;
    }
    if (y < x)
    {
        t = y;
        y = x;
        x = t;
    }

    if (z * z - x * x == y * y)
    {
        printf("%u, %u, %u - Pythagorean triple\n", x, y, z);

        // if gcd(x, y) == 1 then gcd(x, y, z) == 1
        if (gcd(x, y) == 1)
        {
            printf("%u, %u, %u - primitive Pythagorean triple\n", x, y, z);
        }
    }
    else
    {
        printf("%u, %u, %u - not Pythagorean triple\n", x, y, z);
    }


    return 0;
}