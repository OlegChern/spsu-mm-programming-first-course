#include <stdio.h>
#include <stdarg.h>

#include "scan_pos_nums.h"


// Set next number if it's positive
void setX(unsigned int *x1, double *x2, double *k, int *index, va_list *list, double *x, int *n)
{
    if (*x1 + *x2 > 0 && *index < *n)
    {
        *va_arg(*list, double*) = *x1 + *x2;
        x[*index] = *x1 + *x2;
        (*index)++;
    }

    *x1 = 0;
    *x2 = 0;
    *k = 1;
}

void scanPositiveReal(int n, ...)
{
    if (n == 0) return;

    if (n > 1)
        printf("---Enter %d real numbers, please (0..9, '.', ',')\n", n);
    else
        printf("---Enter a real number, please (0..9, '.', ',')\n");
    printf("---Other symbols will not be read\n");
    printf("---If entered numbers are too large, they will be shortened\n");

    va_list list;
    va_start(list, n);

    char c;
    int index = 0;
    int prevIndex = 0;
    double x[n];

    unsigned int x1 = 0;// The integer part of the number
    double x2 = 0;// The fractional part of the number
    double k = 1;// 10^-k - coefficient for x2

    // Flag
    int scanType = 0;
    /* 0 - no type
     * 1 - scanning integer part
     * 2 - scanning fractional part
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
                    else if (c == '.' || c == ',') scanType = 2;

                    break;
                }
                case 1:// Scanning integer part
                {
                    if ('9' - c >= 0 && c - '0' >= 0)
                    {
                        unsigned int tmp = x1 * 10 + (c - '0');
                        // If the number just scanned isn't large
                        if (tmp > x1 && (x1 == 0 || tmp / x1 >= 10)) x1 = tmp;
                        else
                        {// Large number
                            setX(&x1, &x2, &k, &index, &list, x, &n);

                            // --shortening--
                            // Skip until not numeric
                            scanf("%c", &c);
                            while ('9' - c >= 0 && c - '0' >= 0) scanf("%c", &c);

                            if (c == '.' || c == ',')
                            {
                                // If found comma, skip until not numeric
                                scanf("%c", &c);
                                while ('9' - c >= 0 && c - '0' >= 0) scanf("%c", &c);

                                if (c == '.' || c == ',') scanType = 2;// New number was found
                                else scanType = 0;
                            }
                            else scanType = 0;

                            break;
                        }
                    }
                    else if (c == '.' || c == ',')
                    {
                        scanType = 2;
                    }
                    else
                    {
                        setX(&x1, &x2, &k, &index, &list, x, &n);
                        scanType = 0;
                    }

                    break;
                }
                case 2:// Scanning fractional part
                {
                    if ('9' - c >= 0 && c - '0' >= 0)
                    {
                        k /= 10;
                        x2 += (c - '0') * k;
                    }
                    else
                    {
                        setX(&x1, &x2, &k, &index, &list, x, &n);

                        // New number was found
                        if (c == '.' || c == ',') scanType = 2;
                        else scanType = 0;
                    }

                    break;
                }
            }
        } while (c != 10 && index < n);

        // Print info about newly scanned numbers
        if (index > prevIndex)
        {
            printf("---Scanned: ");
            for (int i = prevIndex; i < index - 1; ++i) printf("%lf, ", x[i]);
            printf("%lf\n", x[index - 1]);

            prevIndex = index;
        }
    } while (index < n);

    va_end(list);
}