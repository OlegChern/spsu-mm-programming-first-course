#include <stdio.h>
#include <math.h>
#include <stdbool.h>

const int n = 31;

bool isPrime(long long x)
{
    for (int i = 3; i <= sqrt(x); i += 2) //Checking only odd dividers since (2^n - 1) is always odd
    {
        if ((x % i) == 0)
        {
            return false;
        }
    }
    return true;
}


int main()
{

    printf("%s", "Mersenne primes: ");

    for (int i = 2; i <= n; i++)
    {
        long long temp = (long long) (pow(2, i) - 1);
        if (isPrime(temp))
        {
            printf("%llu ", temp);
        }
    }

    return 0;
}
