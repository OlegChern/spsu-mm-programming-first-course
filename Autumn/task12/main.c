#include "unsignedBignum.h"

int main(void)
{
    UBN *ubn = buildUBN(1);
    leftShiftUBN(ubn, 2);
    rightShiftUBN(ubn, 1);
    printHexUBN(ubn);
    return 0;
}

/*
int main()
{
    UBN *ubn = buildUBN(3);
    const unsigned int power = 5000;

    powerUBN(ubn, power);
    printHexUBN(ubn);
    printf("\n");

    freeUBN(ubn);
    return 0;
}
*/
