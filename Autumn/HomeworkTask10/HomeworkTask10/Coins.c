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