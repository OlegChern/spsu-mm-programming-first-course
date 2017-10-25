#include <stdio.h>
#include <math.h>
#include <stdarg.h>

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

    void setX() // Set next number if it's positive
    {
        if (x1 + x2 > 0 && index < n)
        {
            *va_arg(list, double*) = x1 + x2;
            x[index] = x1 + x2;
            index++;
        }

        x1 = 0;
        x2 = 0;
        k = 1;
    }

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
                            setX();

                            // --shortening--
                            // Skip until not numeric
                            scanf("%c", &c);
                            while ('9' - c >= 0 && c - '0' >= 0) scanf("%c", &c);

                            if (c == '.' || c == ',')
                            {
                                // If found comma, skip until not numeric
                                scanf("%c", &c);
                                while ('9' - c >= 0 && c - '0' >= 0) scanf("%c", &c);

                                // New number was found
                                if (c == '.' || c == ',') scanType = 2;
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
                        setX();
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
                        setX();

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

void printAngleInDegreesMinutesSeconds(double degreeAngle)
{
    int deg, min, sec;

    deg = (int) floor(degreeAngle);

    min = (int) floor((degreeAngle - deg) * 60);

    if (fmod(((degreeAngle - deg) * 60 - min) * 60, 1) > 0.5)
    {
        sec = (int) ceil(((degreeAngle - deg) * 60 - min) * 60);
    }
    else
    {
        sec = (int) floor(((degreeAngle - deg) * 60 - min) * 60);
    }

    printf("%lf* ~ %d* + %d\' + %d\"\n", degreeAngle, deg, min, sec);
}

int main()
{
    double a, b, c;
    scanPositiveReal(3, &a, &b, &c);

    // Sorting
    double t;
    if (c < b)
    {
        t = c;
        c = b;
        b = t;
    }
    if (c < a)
    {
        t = c;
        c = a;
        a = t;
    }
    if (b < a)
    {
        t = b;
        b = a;
        a = t;
    }

    if (c < a + b)
    {
        printf("%lf, %lf, %lf - triangle\n", a, b, c);

        double alpha = 180 * acos((b * b + c * c - a * a) / (2 * b * c)) / M_PI;
        double beta = 180 * acos((a * a + c * c - b * b) / (2 * a * c)) / M_PI;
        double gamma = 180 * acos((b * b + a * a - c * c) / (2 * b * a)) / M_PI;

        printf("Angles:\n");
        printAngleInDegreesMinutesSeconds(alpha);
        printAngleInDegreesMinutesSeconds(beta);
        printAngleInDegreesMinutesSeconds(gamma);
    }
    else printf("%lf, %lf, %lf - not triangle\n", a, b, c);


    return 0;
}
