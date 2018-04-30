#include<stdio.h>
#include<math.h>

double input()
{
    printf("Please enter a number. NB: Don't input random symbols\n");
    double n;
    while (1)
    {
        if ((scanf("%lf", &n) == 1) && (n > 0))
        {
            return n;
        }
        else
        {
            while(getchar() != '\n');
        }
        printf("I need a number\n");
    }
}

double angle(double a, double b, double c)
{
    return acos((b * b + c * c - a * a) / (2 * b * c)) / M_PI * 180;
}

void result(double a, double b, double c)
{
    double k = angle(a, b, c);
    int degree = (int) k;
    k = (k - degree) * 60;
    int minutes = (int) k;
    k = (k - minutes) * 60;
    int seconds = (int) k;
    if (minutes == 0 && seconds == 0)
        printf("%d degrees\n", degree);
    else if (seconds == 0)
        printf("%d degrees %d minutes\n", degree, minutes);
    else
        printf("%d degrees %d minutes %d seconds\n", degree, minutes, seconds);
}
int main()
{
   double a = input(), b = input(), c = input();
   if ((a < b + c) && (b < a + c) && (c < a + b))
   {
       printf("Here are angles of the tringle:\n");
       printf("Angle opposite side (with length in int) %d equals: ", (int) a);
       result(a, b, c);
       printf("Angle opposite side (with length in int) %d equals: ", (int) b);
       result(b, a, c);
       printf("Angle opposite side (with length in int) %d equals: ", (int) c);
       result(c, b, a);
   }
   else
    printf("I'm sorry, I can't make a nondegenerate triangle :(");
   return 0;
}
