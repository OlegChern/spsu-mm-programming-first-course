#include <stdio.h>
#include <math.h>

int input()
{
    int x;

    while(1)
    {
        if ((scanf("%d", &x) != 1) || ((int)sqrt(x)*(int)sqrt(x) == x))
        {
            printf("%s", "INPUT ERROR! Please, try again: ");
            while(getchar() != '\n');
        }
        else
        {
            return x;
        }
    }
}

int continuedFraction(int ideal, double n, int t)
{

    int k, i = 0;
    double num = 1, den = 1, delta = ideal;

    printf("%d ", ideal);

    do
    {
        num = (n + delta);
        den = (t - delta*delta)/den;

        k = (int) (num/den);
        delta = den*k - delta;

        printf("%d ", k);
        i++;
    }while ((num/den != (n + ideal)));

    return i;
}

int main()
{

    double t;

    printf("%s", "Please, enter a non-square integer and the program will print the continued fraction of it: ");

    t = input();


    printf("\n%s%d", "Period = ", continuedFraction((int) sqrt(t), sqrt(t),(int) t));


    return 0;
}






/* This is an alternative way of printing the continued fraction. It is quite inaccurate but works fine for small numbers

int contFrac (long double num)
{
    int i = 0;
    long double ideal = num - (int) num;
    long double chk = 1;


    while ((chk >= 0.0001) || (i == 1))
    {
        int temp;
        temp = (int)num;
        //if ((num - temp) > 0.99) temp = (int)round(num);
        printf("%d ", temp);

        num = 1/(num - (int) num);
        i++;

        chk = 1/num - ideal;
        if (chk < 0) chk *= -1;

    }

    return i;
}

int main() {

    long double num;
    unsigned int temp;

    printf("%s", "Please, enter a non-square integer and the program will print the continued fraction of it: ");
    scanf("%u", &temp);

    num = sqrt(temp);

    printf("\n%s%d", "Period = ", contFrac(num)-1);


    return 0;
}

 */