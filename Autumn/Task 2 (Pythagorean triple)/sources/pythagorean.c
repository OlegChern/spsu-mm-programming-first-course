//
// Created by rinsler on 28.10.17.
//

#include "../headers/pythagorean.h"


int are_pythagorean_triple(int a, int b, int c)
{
    return
            a * a + b * b == c * c ||
            a * a + c * c == b * b ||
            b * b + c * c == a * a;
}

static int gcd(int a, int b)
{
    while (b != 0)
    {
        int c = a % b;
        a = b;
        b = c;
    }

    return a;
}

int are_relative_prime(int a, int b, int c)
{
    return gcd(gcd(a, b), c) == 1;
}