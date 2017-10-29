#include <stdio.h>
#include <math.h>

#include "../headers/fractions.h"

#define MAX_COMPUTING_LEN  20000


/*
 * Based on algorithm: http://www.maths.surrey.ac.uk/hosted-sites/R.Knott/Fibonacci/cfINTRO.html#section6.2.2
 * (section 6.2.2)
 * Yes, I took that link from Kirill (╥﹏╥), because my stupid algorithm of calculation ahead
 * was losing precision with enormous speed, so it was impossible to calculate any test
 * which is bigger than 100 correctly.
 */

int main()
{
    int n;

    printf(
            "╭---------------------------- BEGIN OF USAGE ----------------------------╮\n"
            "| Program gets n non-negative integer number and returns representation  |\n"
            "| of his square root as continued fraction in format:                    |\n"
            "|  *  [a0; a1, ..., an] if square root is NOT integer                    |\n"
            "|     where 'a0' is a preperiod and 'a1, ..., an' is a period of that    |\n"
            "|     representation.                                                    |\n"
            "|  *  [a0] if square root IS integer                                     |\n"
            "|     where 'a0' integer square root                                     |\n"
            "╰----------------------------- END OF USAGE -----------------------------╯\n\n"
    );

    printf("Please, input an integer number :\n");

    while (1)
    {
        char *s;
        size_t sz = 0;
        int gl_res = (int) getline(&s, &sz, stdin);
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

    double m = sqrt(n);

    if ((int) m * m == n)
        printf("Representation has been computed successfully:\n[%d]\n", (int) m);
    else
    {
        int sqrt_of_n = (int) m;

        int x[MAX_COMPUTING_LEN][3];

        x[0][0] = 0;
        x[0][1] = 1;
        x[0][2] = sqrt_of_n;

        get_next_repr(n, sqrt_of_n, x[0], x[1]);

        int period = -1;
        for (int i = 2; i < MAX_COMPUTING_LEN; ++i)
        {
            get_next_repr(n, sqrt_of_n, x[i - 1], x[i]);

            if (x[i][0] == x[1][0] && x[i][1] == x[1][1])
            {
                period = i - 1;
                break;
            }
        }

        if (period == -1)
            printf("It is not enough MAX_COMPUTING_LEN constant to compute this representation...\n");
        else
        {
            printf("Representation has been computed successfully:\n");
            printf("[%d; ", x[0][2]);
            for (int i = 1; i <= period; ++i)
                printf("%d%s", x[i][2], i == period ? "]\n" : ", ");

            printf("where period length is %d\n", period);
        }
    }

    return 0;
}