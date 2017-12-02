#include "Coins.h"

int main()
{
	printf("This program counts ways to make change.\n");
	printf("Coins: 1, 2, 5, 10, 20, 50 pennies.\n");
	printf("       1, 2 pounds.\n\n");
	printf("Enter amount of money (in pennies, only number): ");

	int coins[] = { 1, 2, 5, 10, 20, 50, 100, 200 };
	int amount;

	while (!getInt(&amount))
	{
		printf("Please enter again: ");
	}

	int a = count(amount, coins);
	printf("%d", a);

	return 0;
}

int count(int n, int arr[])
{
	if (n < 0)
	{
		return 0;
	}
	else if (n == 0)
	{
		return 1;
	}

	int sum = 0, i = 0;

	while (n >= arr[i])
	{
		sum += count(n - arr[i], arr);
		i++;
	}

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

			if (current == '\n') // if end of the line
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