#include <stdio.h>
#include <stdarg.h>

#include "scan_pos_nums.h"

// Set next number if it's positive
void setX(unsigned int *x1, int *index, va_list *list, unsigned int x[], int *n)
{
    if (*x1 > 0 && *index < *n)
    {
        *va_arg(*list, unsigned int*) = *x1;
        x[*index] = *x1;
        (*index)++;
    }

    *x1 = 0;
}

void scanPositiveDecimal(int n, ...)
{
    if (n == 0) return;

    if (n > 1)
        printf("---Enter %d natural numbers, please (0..9)\n", n);
    else
        printf("---Enter a natural number, please (0..9)\n");
    printf("---Other symbols including ',' and '.' will not be read\n");
    printf("---If entered numbers are too large, they will be shortened\n");

    va_list list;
    va_start(list, n);

    char c;
    int index = 0;
    int prevIndex = 0;
    unsigned int x[n];

    unsigned int x1 = 0;

    // Flag
    int scanType = 0;
    /* 0 - no type
     * 1 - scanning number
     * */

    do
    {
        // Amount of scanned numbers (index/n)
        printf("-(%d/%d)->", index, n);

        do
        {
            scanf("%c", &c);

            switch (scanType)
            {
                case 0:
                {
                    if ('9' - c >= 0 && c - '0' > 0)
                    {
                        scanType = 1;
                        x1 = (unsigned int) (c - '0');
                    }

                    break;
                }
                case 1:
                {
                    if ('9' - c >= 0 && c - '0' >= 0)
                    {
                        unsigned int tmp = x1 * 10 + (c - '0');
                        // If the number just scanned isn't large
                        if (tmp > x1 && (x1 == 0 || tmp / x1 >= 10)) x1 = tmp;
                        else
                        {// Large number
                            setX(&x1, &index, &list, x, &n);

                            // --shortening--
                            // Skip until not numeric
                            scanf("%c", &c);
                            while ('9' - c >= 0 && c - '0' >= 0) scanf("%c", &c);

                            scanType = 0;

                            break;
                        }
                    }
                    else
                    {
                        setX(&x1, &index, &list, x, &n);
                        scanType = 0;
                    }

                    break;
                }
            }
        } while (c != 10 && index < n);

        // Print info about newly scanned numbers
        if (index > prevIndex)
        {
            printf("---Scanned: ");
            for (int i = prevIndex; i < index - 1; ++i) printf("%u, ", x[i]);
            printf("%u\n", x[index - 1]);

            prevIndex = index;
        }
    } while (index < n);

    va_end(list);
}