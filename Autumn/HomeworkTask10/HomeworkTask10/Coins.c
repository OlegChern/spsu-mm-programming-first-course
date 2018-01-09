#include "Coins.h"

int main()
{
	printf("This program counts ways to make change.\n");
	printf("Coins: 1, 2, 5, 10, 20, 50 pennies.\n");
	printf("       1, 2 pounds.\n\n");
	printf("Enter amount of money (in pennies, only one number): ");

	int amount;

	// init coins array
	int* coins = (int*)malloc(NUMBEROFCOINS * sizeof(int));
	coins[0] = 1;
	coins[1] = 2;
	coins[2] = 5;
	coins[3] = 10;
	coins[4] = 20;
	coins[5] = 50;
	coins[6] = 100;
	coins[7] = 200;

	// read int
	while (!getInt(&amount))
	{
		printf("Please enter again: ");
	}

	// init memoization
	WORD **memoization = (WORD**)malloc((amount + 1) * sizeof(WORD*));

	
	for (int i = 0; i <= amount; i++)
	{
		memoization[i] = (WORD*)malloc(NUMBEROFCOINS * sizeof(WORD));

		memoization[i][0] = 1;

		for (int j = 1; j < NUMBEROFCOINS; j++)
		{
			memoization[i][j] = -1;
		}
	}

	// count

	int nearestCoinIndex = getNearestCoinIndex(amount, coins);
	WORD a = count(amount, nearestCoinIndex, coins, memoization);

	// print
	if (a != 1)
	{
		printf("There are %d ways to make change.", a);
	}
	else
	{
		printf("There is 1 way to make change.");
	}

	for (int i = 0; i <= amount; i++)
	{
		free(memoization[i]);
	}

	free(memoization);
	free(coins);

	return 0;
}

WORD count(int amount, int coinIndex, int* coins, WORD** memoization)
{
	if (memoization[amount][coinIndex] != -1)
	{
		return memoization[amount][coinIndex];
	}

	int		currentCoinNumber = 0,
			nextCoinIndex = coinIndex - 1;

	WORD	compos,
			sum = 0;

	while ((compos = currentCoinNumber * coins[coinIndex]) <= amount)
	{
		sum += count(amount - compos, nextCoinIndex, coins, memoization);
		currentCoinNumber++;
	}

	memoization[amount][coinIndex] = sum;
	return sum;
}

int getNearestCoinIndex(int amount, int* coins)
{
	for (int i = 0; i < NUMBEROFCOINS; i++)
	{
		if (coins[i] >= amount)
		{
			return i;
		}
	}

	return NUMBEROFCOINS - 1;
}

int getInt(int *target)
{
	while (TRUE)
	{
		char current;
		size_t length = 0, size = CHUNK;

		char *source = (char*)malloc(sizeof(char) * size);
		if (!*source)
		{
			printf("Can't allocate!\n");
			return FALSE;
		}

		while (TRUE)
		{
			current = getchar();

			if (current == '\n' || current == ' ')
			{
				if (length > 0)
				{
					source[length] = '\0';
					(*target) = atoi(source);

					if (*target != 0)
					{
						return TRUE;
					}
					else
					{
						return FALSE;
					}
				}

				return FALSE;
			}

			if (current < '0' || current > '9') // just ignore
			{
				continue;
			}

			source[length++] = current;

			if (size <= length) // if allocated size <= length of char array
			{
				size += CHUNK;
				source = realloc(source, sizeof(char) * size); // new size of char array

				if (!*source)
				{
					printf("Can't reallocate!\n");
					free(source);
					return FALSE;
				}
			}
		}
	}

	return FALSE;
}