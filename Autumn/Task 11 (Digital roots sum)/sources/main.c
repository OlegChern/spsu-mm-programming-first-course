#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define MAX_BOUND 999999


int digitSum(int n)
{
    int sum = 0;
    while (n != 0)
    {
        sum += n % 10;
        n /= 10;
    }

    return sum;
}

int max(int a, int b)
{
    return a >= b ? a : b;
}


int main()
{
    printf(
        "#---------------------------- BEGIN OF USAGE ----------------------------#\n"
        "| Program prints sum of maximal by factorizations digital roots of       |\n"
        "| numbers from 2 to 999999 (inclusive).                                  |\n"
        "#---------------------------- END OF USAGE ------------------------------#\n\n"
    );

    int digitalRoot[MAX_BOUND + 1];
    int digitalRootLen = MAX_BOUND + 1;

    for (int i = 0; i < 10; ++i)
        digitalRoot[i] = i;

    for (int i = 10; i < digitalRootLen; ++i)
        digitalRoot[i] = digitalRoot[digitSum(i)];

    int primes[MAX_BOUND + 1];
    int primesLen = MAX_BOUND + 1;

    memset(primes, 1, sizeof(primes[0]) * primesLen);
    primes[0] = primes[1] = 0;
    for (int i = 2; i * i <= primesLen; ++i)
        if (primes[i])
            for (int j = i * i; j < primesLen; j += i)
                primes[j] = 0;

    int mdrs[MAX_BOUND + 1];
    int mdrsLen = MAX_BOUND + 1;

    for (int i = 2; i < mdrsLen; ++i)
    {
        if (primes[i])
            mdrs[i] = digitalRoot[i];
        else
        {
            int t = i;
            for (int j = 2; j * j <= i; ++j)
                if (i % j == 0)
                {
                    mdrs[i] = max(mdrs[i], mdrs[i / j] + digitalRoot[j]);
                    while (t % j == 0)
                        t /= j;
                }

            if (t != 1)
                mdrs[i] = max(mdrs[i], mdrs[i / t] + digitalRoot[t]);
        }
    }

    int result = 0;
    for (int i = 2; i < mdrsLen; ++i)
        result += mdrs[i];

    printf("The requested sum is: %d.\n", result);
    
    return 0;
}