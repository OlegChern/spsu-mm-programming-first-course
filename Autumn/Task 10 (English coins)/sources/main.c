#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../headers/str_funcs.h"


const int coins[] = {1, 2, 5, 10, 20, 50, 100, 200};
const int coinsAmount = 8;

/* The Algorithm
 *
 * Let's take the idea of dynamic programming:
 * Suppose we know the answer for all amounts if we take coins which
 * type is less than type T. Now we want to count an amount of ways to get
 * current sum S where we take exactly one coin of the type T (pseudocode):
 *     dp[S]{type <= T and just one coin of type T} = dp[S - coinOfType(T)]{type < T}
 *                 ^                                                             ^
 *                 |                                                             |
 *        all taken coins types                                       all taken coins types
 *        are not bigger than T                                          are less than T
 * It's easy to expand that idea on bigger than one amount of type T coins
 * (pseudoceode):
 *     iterate i from 1 while S - i * coinOfType(T) >= 0
 *         dp[S]{type <= T} += dp[S - i * coinOfType(T)]{type < T}
 *
 * Let's notice that to count each certain sum we must know just sums that are
 * just less than that, so we can just iterate all sums in cycle.
 *
 * Ok, now know the answer for all possible amounts with coins which type is not biggest than T.
 * Now we can take the next type.
 *
 * So, the final algorithm (pseudocode):
 *     iterate T from the least to the biggest:                   // T is coin type
 *         iterate sum from 0 to N:                               // N is the user input
 *             iterate i from 1 while S - i * coinOfType(T) >= 0: // an amount of taken coins of current coin type
 *                 dp[sum]{type <= T} += dp[sum - i * coinOfType(T)]{type < T}
 *
 * The base of dynamics here will be:
 *     dp[*]{the least type} = 1
 * Because when we have just coins of 1 pence, we can take each amount n just in one way:
 * n coins of 1 pence.
 *
 */


int main() {
    int n;

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

    printf("Please, input an amount of money in pence:\n");

    while (1)
    {
        char *s = NULL;
        size_t sz = 0;
        int gl_res = getline(&s, &sz, stdin);
        int sc_res = sscanf(s, "%d", &n);

        if (gl_res == -1)
            printf("Can't read a line: check that your input stream is correct. Try again:\n");
        else if (sc_res != 1)
            printf("Can't read a number. Try again:\n");
        else if (n < 0)
            printf("Incorrect number. It must be a non-negative integer value. Try again:\n");
        else
            break;
    }

    int dpLen = n + 1;

    // State of the dp
    long long **dp = calloc((size_t) dpLen, sizeof(*dp));
    if (!dp)
        return 1;
    for (int i = 0; i < dpLen; ++i)
    {
        dp[i] = calloc(coinsAmount, sizeof(**dp));
        if (!*dp)
            return 1;
        memset(*dp, 0, sizeof(*dp) * coinsAmount);
    }

    // Base of the dp
    for (int i = 0; i < dpLen; ++i)
        dp[i][0] = 1;

    // Calculating of each state
    for (int c = 1; c < coinsAmount; ++c)
        for (int s = 0; s < dpLen; ++s)
            for (int i = 0; s - i * coins[c] >= 0; ++i)
                dp[s][c] += dp[s - i * coins[c]][c - 1];

    //Printing a result
    printf("You can take that sum by %lli different ways.\n", dp[n][coinsAmount - 1]);

    for (int i = 0; i < dpLen; ++i)
        free(dp[i]);
    free(dp);

    return 0;
}