#include <stdio.h>
#include <math.h>
#include "scan_pos_nums.h"

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
