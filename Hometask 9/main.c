#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main()
{
    void *ptr1 = myMalloc(40);
    void *ptr2 = myMalloc(40);
    void *ptr3 = myMalloc(40);
    system("pause");
    return 0;
}
