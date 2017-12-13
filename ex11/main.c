#include <stdio.h>
#include <stdlib.h>

const int final = 999999;

unsigned int isPrime(unsigned int num)
{
    for (unsigned int i = 2; i * i <= num; i++)
    {
        if (num % i == 0) return i;
    }

    return 0;
}

unsigned int digitalRoot(unsigned int num)
{
    return num - 9 * ((num - 1) / 9);
}

int main()
{
    unsigned int *MDRS = calloc(sizeof(unsigned int), final + 1);

    unsigned int result = 0;

    for (unsigned int i = 2; i < 10; i++)
    {
        MDRS[i] = i;
        result += i;
    }

    for (unsigned int i = 10; i <= final; i++)
    {
        MDRS[i] = digitalRoot(i);

        unsigned int start = isPrime(i);

        if (start)
        {
            for (unsigned int j = start; j * j <= i; j++)
            {
                if (i % j == 0)
                {
                    unsigned int check = MDRS[i / j] + MDRS[j];
                    if (check > MDRS[i]) MDRS[i] = check;
                }
            }

        }

        result += MDRS[i];
    }

    printf("The result is %u", result);

    free(MDRS);

    return 0;
}