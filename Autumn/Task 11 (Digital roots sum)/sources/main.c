#include <stdio.h>

#define MAX_BOUND 1000000 // exclusive

#define max(a, b) (((a) > (b)) ? (a) : (b))


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


int main()
{
    printf(
        "#---------------------------- BEGIN OF USAGE ----------------------------#\n"
        "| Program prints sum of maximal by factorizations digital roots of       |\n"
        "| numbers from 2 to 999999 (inclusive).                                  |\n"
        "#---------------------------- END OF USAGE ------------------------------#\n\n"
    );

    int digitalRoot[MAX_BOUND];
    int mdrs[MAX_BOUND];

    // Bases of dynamic programming
    for (int i = 0; i < 10; ++i)
        digitalRoot[i] = i;
    mdrs[0] = digitalRoot[0];
    mdrs[1] = digitalRoot[1];

    // Computing all values
    for (int i = 2; i < MAX_BOUND; ++i)
    {
        mdrs[i] = digitalRoot[i] = digitalRoot[digitSum(i)];
        for (int j = 2; j * j <= i; ++j)
            if (i % j == 0)
                mdrs[i] = max(mdrs[i], mdrs[j] + mdrs[i / j]);
    }

    int result = 0;
    for (int i = 2; i < MAX_BOUND; ++i)
        result += mdrs[i];

    printf("The requested sum is: %d.\n", result);

    return 0;
}