#include <stdio.h>
#include <stdbool.h>

int input(int k)
{
    int x;

    while(true)
    {
        if ((scanf("%d", &x) != 1) || (x < 0))
        {
            printf("%s%d%s%d%s", "INPUT ERROR! Received ", k, " numbers, ", 3-k, " more are(is) required: ");
            while(getchar() != '\n');
        }
        else
        {
            return x;
        }
    }
}

long long prim(long long x,long long y) // finding the greatest common divisor
{
    if (x == 0 || y == 0)
    {
        return -1;
    }

    if (y > x)
    {
        long long temp = y;
        y = x;
        x = temp;
    }

    if ((x % y) == 0)
    {
        return y;
    }
    else
    {
        return prim(y, x % y);
    }
}

int main() {

    long long x,y,z;
    bool mark = false;

    printf("%s", "Please, enter 3 numbers (integers) in order to find out if they are a pythagorean triple: ");
    x = input(0);
    y = input(1);
    z = input(2);

    printf("The numbers are %lld, %lld, %lld\n", x, y, z);

    if ((x*x + y*y == z*z) || (x*x + z*z == y*y) || (y*y + z*z == x*x)) // finding out if the numbers are a pythagorean triple
    {
        mark = true;
    }

    if (mark == true)
    {
        if (prim(prim(x,z),y) == 1)
        {
            printf("%s", "These numbers are a primitive pythagorean triple");
        }
        else
        {
            printf("%s", "These numbers are a pythagorean triple but not a primitive one");
        }
    }
    else
    {
        printf("%s", "These numbers are not a pythagorean triple");
    }


    return 0;
}
