#include <stdio.h>
#include<string.h>
#include<stdlib.h>

int inp(char *s)
{
    int i, k = 0;
    for(i = 0; s[i] != '\0'; ++i)
    {
        if (s[i] >= '0' && s[i] <= '9')
            ++k;
    }
    if (k == i)
        return 1;
    else
        return 0;
}

int gcd(int a,int b)
{
  while (a && b)
       if (a >= b)
         a %= b;
       else
         b %= a;
  return a | b;
}

void order2(int * a, int * b)
{
    if (*a < *b)
    {
        int t = *a;
        *a = *b;
        *b = t;
    }
}

void order(int * a, int * b, int * c)
{
    order2(a, b);
    order2(a, c);
    order2(b, c);
}

int main()
{
    int a[3], i = 0;
    char s[255];
    printf("I need 3 numbers from you\n");
    while (i < 3)
    {
            printf("Please enter a number\n");
            gets(s);
            while (!inp(s))
            {
                    printf("Be attentive!!! I asked you to enter a number\n");
                    gets(s);
            }
            a[i] = atoi(s);
            ++i;
    }
    order(&a[0],&a[1],&a[2]);
    if (a[0]*a[0] == a[1]*a[1] +a[2]*a[2])
    {
        printf("It's a pythagorean triple.\n");
        if (gcd(a[0],gcd(a[1],a[2])) == 1)
        {
            printf("But it's not a usual pythagorean triple. We are lucky to find primitive pythagorean triple!!!\n");
        }
    }
    else
        printf("These are just random numbers:(\n");
    return 0;
}

