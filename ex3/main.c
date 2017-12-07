#include <stdio.h>
#include <stdbool.h>
#include <math.h>

double input(int k)
{
    double x;

    while (true)
    {
        if (scanf("%lf", &x) != 1)
        {
            printf("%s%d%s%d%s", "INPUT ERROR! Received ", k, " numbers, ", 3 - k, " more are(is) required: ");
            while (getchar() != '\n');
        } else
        {
            return x;
        }
    }
}

bool isTriangle(double *a, double *b, double *c) // finding out if it's possible to build a triangle
{
    if (a == 0 || b == 0 || c == 0)
    {
        return false;
    }

    if ((*a + *b > *c) && (*a + *c > *b) && (*c + *b > *a))
    {
        return true;
    } else
    {
        return false;
    }
}

double angle(double x, double y, double z) //finding the angles
{
    return ((180 / M_PI) * acos((x * x + y * y - z * z) / (2 * x * y)));
}

void dms(double *deg)  //outputting the angles in the correct form
{
    int d = (int) *deg;
    printf("%d%s", d, " degrees, ");

    int m = (int) ((*deg - (double) d) * 60);
    printf("%d%s", m, " minutes, ");

    int s = (int) (((*deg - (double) d) * 60 - m) * 60);
    printf("%d%s", s, " seconds\n");
}


int main()
{
    double a, b, c;

    printf("%s", "Please, enter three numbers to see if it is possible to build a triangle with such sides: ");
    a = input(0);
    b = input(1);
    c = input(2);

    printf("The numbers are %f, %f, %f\n", a, b, c);

    double q = angle(a, b, c);
    double w = angle(a, c, b);
    double e = angle(c, b, a);


    if (isTriangle(&a, &b, &c))
    {
        printf("%s", "It is possible to build a triangle with angles:\n");
        dms(&q);
        dms(&w);
        dms(&e);
    } else
    {
        printf("%s", "It is impossible to build such a triangle");
    }

    return 0;
}
