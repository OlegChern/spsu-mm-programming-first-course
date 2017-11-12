#include <stdio.h>
#include <math.h>

int check_prime(int);

int main()
{
	int a = 2;

	printf("Mersenne primes:\n");

	for (int n = 2; n <= 31; n++)
	{
		a *= 2;
		if (check_prime(a - 1))
			printf("%d\n", a - 1);
	}

	return 0;
}

int check_prime(int a)
{
	if (a % 2 == 0)
	{
		return 0;
	}

	for (int i = 3; i <= sqrtf((float)a); i += 2)
	{
		if (a % i == 0)
		{
			return 0;
		}
	}

	return 1;
}