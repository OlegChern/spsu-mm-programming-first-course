//I'm making massives (of "1" and "0") for 32-bit precision and 64-bit
#include<stdio.h>
#include<malloc.h>

int length(int n)
{
    int i;
    for (i = 0; n > 0;  n /= 2, ++i)
    {
    }
    return i;
}

void binaryForm (int n, int max, int p)
{
    int i, k = p + length(n) - 1, q, *a;
    if (max == 32)
    {
        q = 8;
        a = malloc(32 * sizeof(int));
    }
    else
    {
        q = 11;
        a = malloc(64 * sizeof(int));
    }
    for (i = q; i > 0; --i)
    {
        a[i] = k % 2;
        k /= 2;
    }
    while (n % 2 == 0)
    {
        n /= 2;
    }
    n /= 2;
    for (i = q + 1; i < max; ++i)
    {
        a[i] = n % 2;
        n /= 2;
    }
    for (i = 1; i < max; ++i)
    {
        printf("%d", a[i]);
    }
    free(a);
}

// here I do ~number + 1

void invertBinaryForm(int n)
{
    int i, k = length(n);
    int *a = malloc(32 * sizeof(int));
    for (i = 0; i < 32 - k; ++i)
    {
        a[i] = 1;
    }
    for (i = 31; i > 31 - k; --i)
    {
        if(n % 2 == 1)
        {
            a[i] = 0;
        }
        else
            a[i] = 1;
        n /= 2;
    }
    int j = 31;
    a[j] += 1;
    while ((a[j] == 2) && (j > 0))
    {
        a[j] = 0;
        a[j-1] += 1;
        --j;
    }
    for (i = 0; i < 32; ++i)
    {
        printf("%d", a[i]);
    }
    free(a);
}

int main()
{
    printf("Hi! I'm Gogina Olesya Yuryevna.\n");
    int lastn = 6, firstn = 6, patronym = 8;
    int proizv = lastn * firstn * patronym;
    printf("A)");
    invertBinaryForm(proizv);
    printf("\nB)0");
    binaryForm(proizv, 32, 127);
    printf("\nC)1");
    binaryForm(proizv, 64, 1023);
    return 0;
}

