#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS_

int input()
{
	printf
	(
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
	int x;
	printf("Enter a sum of coins. Input only natural number!\n");

	while (1)
	{
		if ((scanf_s("%d", &x) == 1) && (x > 0))
		{
			return x;
		}
		else
		{
			while (getchar() != '\n');
		}
		printf("please enter a number\n");
	}
}

int NumberOfWays(int sumOfMoney)
{

	int coins[8] = { 200, 100, 50, 20, 10, 5, 2, 1 };
	int *ways[8];
	for (int i = 0; i < 8; i++)
	{
		ways[i] = calloc(sumOfMoney + 1, sizeof(int*));
		ways[i][0] = 1;
	}
	for (int i = 0; i < sumOfMoney + 1; i++)
	{
		ways[0][i] = 1;
	}

	for (int pointerOfMaxCoin = 1; pointerOfMaxCoin < 8; pointerOfMaxCoin++)
	{
		for (int newAmountOfMoney = 1; newAmountOfMoney <= sumOfMoney; newAmountOfMoney++)
		{
			for (int i = 0; i * coins[pointerOfMaxCoin] <= newAmountOfMoney; i++)
			{
				ways[pointerOfMaxCoin][newAmountOfMoney] = ways[pointerOfMaxCoin][newAmountOfMoney] + ways[pointerOfMaxCoin - 1][newAmountOfMoney - i * coins[pointerOfMaxCoin]];
			}
		}
	}

	int result = ways[7][sumOfMoney];
	for (int i = 0; i < 8; i++)
	{
		free(ways[i]);
	}
	return result;
}

int main()
{
	int sumOfMoney = input();
	int ways = NumberOfWays(sumOfMoney);
	printf("Number of ways = %d", ways);
	putchar('\n');
	system("pause");
	return 0;
}