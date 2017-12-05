#include <stdio.h>

#include "endlessInteger.h"
#include "util.h"

int main()
{
    if (init())
    {
        printf("Initialization error.\n");
        return 1;
    }

    EndlessInteger *a = buildEndlessInteger(0xFFFFFFFF);
    EndlessInteger *b = buildEndlessInteger(0x1);

    addEndlessInteger(a, b);
    printf("structure: ");
    printList(a);
    printf("\nas integer: ");
    printEndlessInteger(a);
    printf("\nas hex endless ineger: ");
    printHexEndlessInteger(a);
    printf("\nis positive: %d\n", endlessIntegerIsPositive(a));

    freeEndlessInteger(a);
    finish();
    return 0;
}
