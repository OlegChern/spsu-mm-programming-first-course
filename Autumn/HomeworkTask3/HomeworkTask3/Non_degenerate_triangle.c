#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define CHUNK 4

#define PI 3.141592f

void print_degrees(float, float, float);
void getFloat(float*);

int main()
{
	float a, b, c;

	printf("Non-degenerate triangle check. All symbols except numbers will be ignored.\n\n");

	while (TRUE)
	{
		printf("Enter first number: ");
		getFloat(&a);

		printf("Enter second number: ");
		getFloat(&b);

		printf("Enter third number: ");
		getFloat(&c);

		printf("\n");

		if (a == 0 || b == 0 || c == 0)
		{
			printf("Please enter numbers again:\n");
			continue;
		}
		else if (a + b < c || c + a < b || b + c < a)
		{
			printf("Tringle with given sides isn't possible.\n");
			printf("Please enter numbers again:\n");
			continue;
		}
		else
		{
			break;
		}
	}

	printf("(%f, %f, %f) is ", a, b, c);

	if (a + b != c && b + c != a && a + c != b)
	{
		printf("non-degenerate triangle. Angles:\n");
		print_degrees(a, b, c);
		print_degrees(b, c, a);
		print_degrees(c, a, b);
	}
	else
	{
		printf("degenerate triangle.");
	}

	return 0;
}

void print_degrees(float a, float b, float c)
{
	float angle = acosf((b * b + c * c - a * a) / (2 * b * c)); // radians
	angle = angle * 180.f / PI; // decimal degrees

	int degrees = (int)angle;
	int minutes = (int)((angle - degrees) * 60);
	int seconds = (int)(((angle - degrees) - minutes / 60) * 36); // (36 = 3600 / 100) because we want only 2 digits

	printf("%d %d' %d\"\n", degrees, minutes, seconds);
}

void getFloat(float *target)
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
				(*target) = (float)atof(source);
				free(source);

				return;
			}

			if (current != '.' && (current < '0' || current > '9')) // just ignore
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