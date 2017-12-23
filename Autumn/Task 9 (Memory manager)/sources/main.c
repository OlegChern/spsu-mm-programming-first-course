#include <stdio.h>

#include "../headers/memory_manager.h"

#include "../bigint/headers/bigint.h"

int main()
{
    printf(
            "#---------------------------- BEGIN OF USAGE ----------------------------#\n"
            "| Program prints sum of maximal by factorizations digital roots of       |\n"
            "| numbers from 2 to 999999 (inclusive).                                  |\n"
            "#---------------------------- END OF USAGE ------------------------------#\n\n"
    );

    init(1024 * 1024); // 1Mb

    /* For the demonstration of my memory manager work I added here my program
     * "Task 12 (Bignum arithmetic)" which uses an enormous amount of memory operations. */

    // you can try even 3 ^ 50000 and it still will work fast
    BigInt *result = power(bigint(3), 5000, 1);
    char *repr = bigintToHex(result);
    printf("%s\n", repr);

    bigintFree(&result);
    myFree(repr);

    terminate();

    return 0;
}
