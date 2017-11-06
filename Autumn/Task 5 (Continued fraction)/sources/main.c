#include <stdio.h>
#include <math.h>

#include "../headers/fractions.h"
#include "../headers/str_funcs.h"

#define MAX_COMPUTING_COUNT 1000000


/*
 * Based on algorithm: http://www.maths.surrey.ac.uk/hosted-sites/R.Knott/Fibonacci/cfINTRO.html#section6.2.2
 * (section 6.2.2)
 * Yes, I took that link from Kirill (╥﹏╥), because my stupid algorithm of calculation ahead
 * was losing precision with enormous speed, so it was impossible to calculate correctly any test
 * which was bigger than 100.
 */

int main()
{
    int n;

    printf(
            "#---------------------------- BEGIN OF USAGE ----------------------------#\n"
            "| Program gets n non-negative integer number and returns representation  |\n"
            "| of his square root as continued fraction in format:                    |\n"
            "|  *  [a0; a1, ..., an] if square root is NOT integer                    |\n"
            "|     where 'a0' is a preperiod and 'a1, ..., an' is a period of that    |\n"
            "|     representation.                                                    |\n"
            "|  *  [a0] if square root IS integer                                     |\n"
            "|     where 'a0' integer square root                                     |\n"
            "#----------------------------- END OF USAGE -----------------------------#\n\n"
    );

    printf("Please, input an integer number :\n");

    while (1)
    {
        char *s = NULL;
        size_t sz = 0;
        int gl_res = getline(&s, &sz, stdin);
        int sc_res = sscanf(s, "%d", &n);

        if (gl_res == -1)
            printf("Can't read n line: check that your input stream is correct. Try again:\n");
        else if (sc_res != 1)
            printf("Can't read number: number must be an non-negative integer. Try again:\n");
        else if (n < 0)
            printf("Number is incorrect: number must be non-negative. Try again:\n");
        else
            break;
    }

    int sqrt_of_n = (int) sqrt(n);

    if (sqrt_of_n * sqrt_of_n == n)
        printf("Representation has been computed successfully:\n[%d]\n", sqrt_of_n);
    else
    {
        int first[3], second[3];

        int x[2][3];

        first[0] = 0;
        first[1] = 1;
        first[2] = sqrt_of_n;

        get_next_repr(n, sqrt_of_n, first, second);

        x[0][0] = second[0];
        x[0][1] = second[1];
        x[0][2] = second[2];

        printf("Representation has been computed successfully:\n");
        printf("[%d; %d", first[2], second[2]);

        int period = -1;
        for (int i = 2, st = 1; i < MAX_COMPUTING_COUNT; ++i, st = 1 - st)
        {
            get_next_repr(n, sqrt_of_n, x[1 - st], x[st]);

            if (x[st][0] == second[0] && x[st][1] == second[1])
            {
                period = i - 1;
                break;
            }

            printf(", %d", x[st][2]);
        }
        printf("]\n");

        printf("where period length is %d\n", period);
    }

    return 0;
}