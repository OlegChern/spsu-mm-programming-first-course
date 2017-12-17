#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>

#define		TRUE 1
#define		CHUNK 4

int			getInt();
void		continuedFraction(int);

int main()
{
	int x;

	printf("Continued fraction of square root.\n");

	while (TRUE)
	{
		printf("Enter number: ");
		x = getInt();

		int sqrtX = (int)sqrtf((float)x);

		if (x == sqrtX * sqrtX)
		{
			printf("Number mustn't be square of integer!\n");
		}
		else
		{
			break;
		}
	}

	continuedFraction(x);
	return 0;
}

void continuedFraction(int x)
{
	int	period, a0, ai;
	int	numer, denom;

	period = 0;

	a0 = (int)sqrtf((float)x);

	numer = a0;
	denom = x - a0 * a0;

	printf("[ %d ; ", a0);

	while (TRUE)
	{
		ai = (int)((a0 + numer) / denom);

		numer = ai * denom - numer;
		denom = (x - numer * numer) / denom;

		period++;

		if (denom != 1)
		{
			printf("%d, ", ai);
		}
		else
		{
			printf("%d", ai);
			break;
		}
	} 

	printf(" ]\nPeriod: %d", period);
}

int getInt()
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

			if (current == '\n' || current == ' ')
			{
				source[length] = '\0';
				int result = atoi(source);
				free(source);

				return result;
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

	return 0;
}