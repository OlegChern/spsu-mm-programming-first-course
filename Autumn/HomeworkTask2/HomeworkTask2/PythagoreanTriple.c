#include <stdio.h>

#define FALSE 0
#define TRUE 1
#define CHUNK 4

int check_pyth_triple(long, long, long);
int check_prime(int, int, int);
int gcd(int, int);
void getInt(int*);

int main()
{
	int a, b, c;

	printf("Pythagorean triple check. All symbols except numbers will be ignored.\n\n");

	printf("Enter first number: ");
	getInt(&a);

	printf("Enter second number: ");
	getInt(&b);

	printf("Enter third number: ");
	getInt(&c);

	printf("\n(%d, %d, %d) is", a, b, c);

	if (check_pyth_triple(a, b, c))
	{
		if (check_prime(a, b, c))
		{
			printf(" a primitive pythagorean triple\n");
		}
		else
		{
			printf(" a pythagorean triple\n");
		}
	}
	else
	{
		printf("n't a pythagorean triple\n");
	}

	return 0;
}

int check_pyth_triple(long a, long b, long c)
{
	if (a*a + b*b == c*c || a*a + c*c == b*b || b*b + c*c == a*a)
	{
		return 1;
	}

	return 0;
}

int check_prime(int a, int b, int c)
{
	return gcd(gcd(a, b), c) == 1;
}

int gcd(int a, int b)
{
	if (a > b)
	{
		if (b == 0)
		{
			return a;
		}

		return gcd(b, a % b);
	}
	else
	{
		if (a == 0)
		{
			return b;
		}

		return gcd(a, b % a);
	}

	return 0;
}

void getInt(int *target)
{
	while (TRUE)
	{
		int current;
		size_t length = 0, size = CHUNK;

		char *source = (char*)malloc(sizeof(char) * size);
		if (!*source)
		{
			printf("Can't allocate!\n");
			break;
		}

		while (TRUE)
		{
			current = getchar();

			if (current == '\n') // if end of the line
			{
				source[length] = '\0';
				(*target) = atoi(source);

				return;
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
					break;
				}
			}
		}
	}
}