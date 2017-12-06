#include<stdio.h>

int input()
{
    printf("Please enter a sum of coins. NB: Input ONLY natural number!!!\n");
    int n;
    while (1)
    {
        if ((scanf("%d", &n) == 1) && (n > 0))
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

int waysOfPaying(int n)
{
  int p1, p2, p5, p10, p20, p50, p100, p200;
  int p = 0;
  for (p200 = 0; p200 <= n / 200; p200++) // repeat this cycle for max amount of "200 pence" coins in the given sum
      for (p100 = 0; p100 <= (n - 200 * p200) / 100; p100++)
           for (p50 = 0; p50 <= (n -200 * p200 - 100 * p100) / 50; p50++)
                for (p20 = 0; p20 <= (n -200 * p200 - 100 * p100 - 50 * p50) / 20; p20++)
                     for (p10 = 0; p10 <= (n -200 * p200 - 100 * p100 - 50 * p50 - 20 * p20) / 10; p10++)
                         for (p5 = 0; p5 <= (n -200 * p200 - 100 * p100 - 50 * p50 - 20 * p20 - 10 * p10) / 5; p5++)
                             for (p2 = 0; p2 <= (n -200 * p200 - 100 * p100 - 50 * p50 - 20 * p20 - 10 * p10 - 5 * p5) / 2; p2++)
                             {
                                  p1 = n -200 * p200 - 100 * p100 - 50 * p50 - 20 * p20 - 10 * p10 - 5 * p5 - 2 * p2;
                                  if (p1 >= 0)
                                      ++p;
                             }
   return p;
}

int main()
{
   int n = input();
   printf("Ways of paying equals %d", waysOfPaying(n));
}


