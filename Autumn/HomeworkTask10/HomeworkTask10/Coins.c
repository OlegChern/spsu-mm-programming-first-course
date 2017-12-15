#include "Coins.h"

int main()
{
	printf("This program counts ways to make change.\n");
	printf("Coins: 1, 2, 5, 10, 20, 50 pennies.\n");
	printf("       1, 2 pounds.\n\n");
	printf("Enter amount of money (in pennies, only one number): ");

	int amount;

	// init coins array
	int* coins = (int*)malloc(8 * sizeof(int));
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
	int* memoization = (int*)malloc((amount + 1) * sizeof(int));

	memoization[0] = 1;
	for (int i = 1; i < amount + 1; i++)
	{
		memoization[i] = -1;
	}

	// count
	int a = count(amount, coins, memoization);

	// print
	if (a != 1)
	{
		printf("There are %d ways to make change.", a);
	}
	else
	{
		printf("There is 1 way to make change.");
	}

	return 0;
}

int count(int n, int* coins, int* memoization)
{
	if (memoization[n] != -1)
	{
		return memoization[n];
	}

	int sum = 0, i = 0;

	while (n >= coins[i])
	{
		sum += count(n - coins[i], coins, memoization);
		i++;
	}

	memoization[n] = sum;
	return sum;
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