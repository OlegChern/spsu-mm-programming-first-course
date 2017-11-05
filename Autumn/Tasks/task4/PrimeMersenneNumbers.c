#include <stdio.h>
#include <math.h>

int main()
{
    // Calculate primes up to 31
    int primes[20];
    int pIndex = 0;
    int i = 2;
    while (i <= 31)
    {
        int isPrime = 1;
        for (int j = 0; j < pIndex; ++j)
        {
            if (i % primes[j] == 0)
            {
                isPrime = 0;
                break;
            }
        }

        if (isPrime)
        {
            primes[pIndex] = i;
            pIndex++;
        }

        i++;
    }
    int pN = pIndex;


    printf("Prime Mersenne numbers:\n");

    int degree = 0;
    int x = 1; // x = 2^degree
    pIndex = 0;

    // (2^i - 1) - prime  =>  i - prime
    while (pIndex < pN && primes[pIndex] <= 31)
    {
        int p = primes[pIndex];

        while (degree < p)
        {
            degree++;
            x *= 2;
        }

        // (2^p - 1) - prime  <=>  (2^p - 1) % (2 * p * j + 1) != 0 (j - natural, p - prime)
        int isPrime = 1;
        int j = 1;
        while ((2 * p * j + 1) <= sqrt(x - 1))
        {
            if ((x - 1) % (2 * p * j + 1) == 0)
            {
                isPrime = 0;
                break;
            }
            j++;
        }

        if (isPrime) printf("2^%d - 1 = %d\n", p, (x - 1));

        pIndex++;
    }


    return 0;
}
