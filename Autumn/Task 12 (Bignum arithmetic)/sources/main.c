#include <stdio.h>
#include "../headers/bigint.h"


int main()
{
    printf(
            "#---------------------------- BEGIN OF USAGE ----------------------------#\n"
            "|     Program prints hex representation of 3 ^ 5000 by using algorithms  |\n"
            "| of long arithmetic.                                                    |\n"
            "#---------------------------- END OF USAGE ------------------------------#\n\n"
    );

    // you can try even 3 ^ 50000 and it still will work fast
    printf("%s\n", bigintToHex(power(bigint(3), 5000, 1)));

    return 0;
}