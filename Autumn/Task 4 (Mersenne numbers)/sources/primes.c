//
// Created by rinsler on 29.10.17.
//

#include "../headers/primes.h"


int is_prime(int n)
{
    if (n <= 1)
        return 0;

    // i < 46340 is check on not to overflow int type
    for (int i = 2; i < 46340 && i * i <= n; ++i) {
        if (n % i == 0)
            return 0;
    }

    return 1;
}