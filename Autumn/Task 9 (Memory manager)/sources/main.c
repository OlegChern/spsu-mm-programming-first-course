#include <stdio.h>

#include "../headers/memory_manager.h"

#include "../bigint/headers/bigint.h"

int main()
{
    printf(
            "#---------------------------- BEGIN OF USAGE ----------------------------#\n"
            "| The program uses an external memory manager written personally by me   |\n"
            "| instead of standard one. For the demonstration of its work here is     |\n"
            "| used my another program \"Task 12 (Bignum arithmetics)\".                |\n"
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

    /* Uncomment to check a simple example of a myRealloc() work. */
    /*int *a = myMalloc(5 * sizeof(int));
    for (int i = 0; i < 5; ++i)
        a[i] = i;

    printf("Array a:\n");
    for (int i = 0; i < 5; ++i)
        printf("a[%d] = %d\n", i, a[i]);
    printf("\n");

    myRealloc(a, 6);
    a[5] = 5;

    printf("Array a after realloc on one byte more:\n");
    for (int i = 0; i < 6; ++i)
        printf("a[%d] = %d\n", i, a[i]);
    printf("\n");

    myRealloc(a, 4);
    a[5] = 6;

    printf("Array a after realloc on two bytes less:\n");
    for (int i = 0; i < 4; ++i)
        printf("a[%d] = %d\n", i, a[i]);

    myFree(a);*/

    terminate();

    return 0;
}
