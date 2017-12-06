#include<stdio.h>
#include<math.h>

int input()
{
    printf("Please enter a number. NB: Don't input random symbols\n");
    int n;
    while (1)
    {
        if ((scanf("%d", &n) == 1) && (n > 0) && ((int) sqrt(n) != sqrt(n)))
        {
            return n;
        }
        else
        {
            while(getchar() != '\n');
        }
        printf("I need a non square number\n");
    }
}


/*The idea is:
  a0 = (int) sqrt (n);
  sqrt(n) = a0 + 1/p0 ;
  ] r = a0;
  p0 = (sqrt(n) + r) / (n - r * r);
  ] d = n - r * r;
  So, p0 = (sqrt(n) + r) / d;
  a1 = (int) sqrt(p0) => a1 = (int) sqrt((sqrt(n) + r) / d);
  p1 = 1 / (p0 - a1) = d / (sqrt(n) + r - a1 * d);
  Let's multiply denominator by conjugated and represent p1 in the form of p0:
  p1 = ((sqrt(n) + (a1 * d - r)) / ((n - (a1 * d - r) * (a1 * d - r)) / d);
  r = a1 * d - r;
  d = (a1 * d - r) * (a1 * d - r) / d;
  that is why p1 = (sqrt(n) + r) / (n - r * r). From that a2 = (int) sqrt(p1)
  repeat this process till d == 1 or r == a0 (that is how we find period of a continued fraction)
*/


int main()
{
   int n = input();
   printf("Here is a number's continued fraction representation\n");
   int a0 = (int) sqrt(n);
   printf("[%d; ", a0);
   int d = n - a0 * a0;
   int period = 1;
   int r = a0;
   while (d != 1 || r != a0)
   {
       int ai = (int) (sqrt(n) + r) / d;
       printf("%d, ", ai);
       r = ai * d - r;
       d = (n - r * r) / d;
       period ++;
   }
   printf("%d]\n", a0 * 2);
   printf("Period is %d", period);
   return 0;
}

