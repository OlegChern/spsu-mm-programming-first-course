// task8.cpp : Defines the entry point for the console application.
//

#include <stdio.h>


int readNumber()
{
	printf("Enter natural number\n");
	
	while (1)
	{
		int value = 0;
		char nextSymbol = '0';
		if ((scanf_s("%d%c", &value, &nextSymbol) == 2) && (value > 0) && (isspace(nextSymbol)))
		{
			return value;
		}
		else
		{
			if (nextSymbol != '\n')
			{
				while (getchar() != '\n');
			}
			printf("You entered an incorrect expression. Please, enter natural number\n");
		}
	}
}

int numberOfWays(int amountOfMoney)
{
	int coins[8] = { 1, 2, 5, 10, 20, 50, 100, 200 };
	return getNumberOfWays(amountOfMoney, coins, 7);
}

int getNumberOfWays(int amountOfMoney, int coins[], int indexOfMaxCoin)
{
	if (amountOfMoney == 0)
	{
		return 1;
	}
	if (amountOfMoney < 0)
	{
		return 0;
	}
	if (coins[indexOfMaxCoin] == 1)
	{
		return 1;
	}

	return getNumberOfWays(amountOfMoney, coins, indexOfMaxCoin - 1) + getNumberOfWays(amountOfMoney - coins[indexOfMaxCoin], coins, indexOfMaxCoin);
}

int main()
{
	int amountOfMoney = readNumber();
	int ways = numberOfWays(amountOfMoney);
	printf("Number of ways = %d", ways);
	putchar('\n');
	
	return 0;
}

