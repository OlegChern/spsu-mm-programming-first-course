#include <stdio.h>
#include <stdlib.h>

const int coins[] = {1, 2, 5, 10, 20, 50, 100, 200};

int input()
{
    int x;

    while (1)
    {
        if ((scanf("%d", &x) != 1) || (x <= 0))
        {
            printf("%s ", "INPUT ERROR! Please, try again: ");
            while (getchar() != '\n');
        } else
        {
            return x;
        }
    }
}


int main()
{

    int amount;

    printf("%s ", "Please, enter the amount of money you want to exchange (number is a positive integer):");

    amount = input() + 1;

    if (amount == 2)
    {
        printf("%s", "There is only 1 variant to present 1 penny (obviously)");

        return 0;
    }


    // That's where a two-dimensional array is initialized

    long int **vars = calloc((size_t) amount, sizeof(*vars));

    for (int i = 0; i < amount; i++)
    {
        vars[i] = calloc(8, sizeof(long int));

        vars[i][0] = 1; // There's only one way to present the sum using only 1 penny coins

        for (int j = 1; j < 8; j++)
        {
            vars[i][j] = 0;
        }
    }

    for (int j = 1; j < 8; j++) // That's where the variants are counted
        for (int i = 0; i < amount; i++)
            for (int k = 0; k <= i; k += coins[j])
            {
                vars[i][j] += vars[i - k][j - 1];
            }

    printf("There are %ld variants to present %d pence", vars[amount - 1][7], amount - 1);

    for (int i = 0; i < amount; i++)
    {
        free(vars[i]);
    }

    free(vars);


    return 0;

}



