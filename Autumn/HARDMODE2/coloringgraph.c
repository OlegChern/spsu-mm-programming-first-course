#include<stdio.h>
#include<math.h>

/*I realized that I can solve this problem by pure mathematics.
  N(a,b,c) = c * (c - 1) * (function of numbers of ways to paint graph A by c colors) *
               * (function of numbers of ways to paint graph B by c colors) * (number of ways to combine a graphs A and b graphs B)
*/

//finds (a ^ k) % (10 ^ 8) for a long number a

long long degree(long long a, int k)
{
    long long n[9];
    int i, j;
    n[0] = 1;
    for (i = 1; i < 9; i++)
        n[i] = 0;
    for (i = 0; i < k; i++)
    {
        for (j = 0; j < 9; j++)
            n[j] *= a;
        for (j = 0; j < 8; j++)
            if (n[j] >= 10)
            {
                n[j+1] += n[j] / 10;
                n[j] %= 10;
            }
    }
    long long ans = n[0] + 10 * n[1] + 100 * n[2] + 1000 * n[3] + 10000 * n[4] + 100000 * n[5] + 1000000 * n[6] + 10000000 * n[7];
    return ans;

}

/*
    Let's fix the colors of the left side nodes of graph A and the left side of graph B(the same colors).
    With permutations we give numbers to all possible colorings
    that way the ordering of nodes other than the colors of A and B are ignored. Then look at different cases of coloring the center of the graphs and summarize them.
*/

// number of ways to color graph A (How I made this formula is attached to the project)

long long waysA(int c)
{
    long long res = (long long)(pow(c,5) - 9 * pow(c,4) + 34 * pow(c,3) - 69 *pow(c,2) + 77 * c - 38) % 100000000;
    return degree(res, 25);
}

// number of ways to color graph B

long long waysB(int c)
{
   long long res = ((long long)(pow(c,5) - 8 * pow(c,4) + 27 * pow(c,3) - 50 * pow(c,2) + 52 * c - 24)) % 100000000;
   return degree(res, 75);
}

int main()
{
   int config = (1984 * 1983) % 100000000; // number of ways to color the most right last site of the graph
   long long a = waysA(1984);
   long long b = waysB(1984);

   //To make it easier and not to write long arifmetics for this specific problem I chose to multiply numbers step by step

   long long c = (a * b) % 100000000;
   c = (config * c) % 100000000;
   c = (21015504 * c) % 100000000;
   long long comb = 21015504; // C from (a + b) to a (number of combinations of elements a and elements b)
   printf("The last 8 digits of N(25,75,1984) equals %lli", c);
   return 0;
}
