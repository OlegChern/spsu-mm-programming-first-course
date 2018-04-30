#include <stdio.h>
#include <malloc.h>

/*
    The idea is: sum of values from a[2] to a[999999] is the answer.
    We want to find MDRS(k) : first <= k < last;
                    where first == 2^n and last == 2^(n+1) (n < 20 as at the end we need MDRS(999999) which is < 2^20)
    k == j * (k / j), where j >= 2
    we suppose that we'd  earlier found MDRS(k / j).
    After this we update MDRS(k) if MDRS(k) < MDRS(j) + MDRS(k / j).
    So the sum we need is a sum of MDRS(k).
*/

int main()
{
   int *a;
   a = (int *) malloc(1000000 * sizeof(int));
   int c, n, i, j, k;
   int first, last;
   for(i = 0; i <= 999990; i += 9)
   {
        a[i + 1] = 1;
        a[i + 2] = 2;
        a[i + 3] = 3;
        a[i + 4] = 4;
        a[i + 5] = 5;
        a[i + 6] = 6;
        a[i + 7] = 7;
        a[i + 8] = 8;
        a[i + 9] = 9;
    }
    for (n = 1; n < 20; n++)
    {
        first = 1 << n;
        if (n == 19)
        {
            last = 1000000;
        }
        else
        {
            last = 1 << (n + 1);
        }
        for (j = 2; j * j < last; j++)
        {
            c = j - ((j - 1) / 9) * 9; // it's a standart formula of a digital root
            for (k = j * ((first - 1) / j + 1); k < last; k += j)
            {
                if (a[k] < c + a[k / j])
                {
                    a[k] = c + a[k / j];
                }
            }
        }
    }
    int sum = 0;
    for (i = 2; i < 1000000; i++)
    {
        sum += a[i];
    }
    printf("Here is a sum of MDRS(k) where k is [2..999999]  = %d\n", sum);
    return 0;
}

