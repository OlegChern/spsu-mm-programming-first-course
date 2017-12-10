#include <stdio.h>
#include <math.h>

int primeNumber(int x)
{
	for (int i = 2; i < sqrt(x) + 1; i++)
	{
		if (x % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

int main()
{
	printf("Mersenne primes:\n");
	int x = 2;
	for (int i = 1; i < 31; i++)
	{
		x *= 2;
		if (primeNumber(x - 1))
		{
			printf("%d\n", x - 1);
		}
	}
	return 0;
}