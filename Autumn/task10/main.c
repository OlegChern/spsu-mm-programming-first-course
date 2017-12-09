#include <stdio.h>
#include "util.h"

#define COIN_TYPES 8

const int ammounts[COIN_TYPES] = {1, 2, 5, 10, 20, 50, 100, 200};

unsigned long long int getOptions(unsigned long long int currentSum, int currentCoinIndex, int limit)
{
    if (currentSum == limit)
        return 1ull;

    if (currentCoinIndex == 0)
    {
        return 1;
        /*
        Following would allow to support cases with ammounts[0] != 1:
        if ((limit - currentSum) % ammounts[0] == 0)
            return 1;
        else
            return 0;
        */
    }

    unsigned long long int result = 0ull;
    unsigned long long int newSum;

    for (int currentCoinsAdded = 0;
         (newSum = currentSum + currentCoinsAdded * ammounts[currentCoinIndex]) <= limit;
         currentCoinsAdded++)
    {
        result += getOptions(newSum, currentCoinIndex - 1, limit);
    }
    return result;
}

int main()
{
    // introduction by Bashkirov Alexandr
    printf(
            "#---------------------------- BEGIN OF USAGE ----------------------------#\n"
            "| Program gets an amount of money in pence and prints a number of ways   |\n"
            "| in which you can take it by using just an any amount of any English    |\n"
            "| coins:                                                                 |\n"
            "|  *   1 pence                                                           |\n"
            "|  *   2 pence                                                           |\n"
            "|  *   5 pence                                                           |\n"
            "|  *  10 pence                                                           |\n"
            "|  *  20 pence                                                           |\n"
            "|  *  50 pence                                                           |\n"
            "|  * 100 pence (1 pound)                                                 |\n"
            "|  * 200 pence (2 pounds)                                                |\n"
            "#---------------------------- END OF USAGE ------------------------------#\n\n"
    );
    int ammount = readInput();
    // Now, we have following equation:
    // ammount = 1*x1 + 2*x2 + 5*x3 + 10*x4 + 20*x5 + 50*x6 + 100*x7 + 200*x8
    // for some non-negative integers x1..x8
    printf("There are %llu ways to present %d pence.", getOptions(0ull, COIN_TYPES - 1, ammount), ammount);
    return 0;
}
