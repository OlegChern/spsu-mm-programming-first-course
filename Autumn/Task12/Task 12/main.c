#include "stdlib.h"
#include "stdio.h"

int* multip16(int n, int* a)
{
	int k;
	k = (a[1] * n) / 16;
	a[1] = (a[1] * n) % 16;

	for (int i = 2; i <= a[0]; i++)
	{
		int t = k;
		k = (a[i] * n + t) / 16;
		a[i] = (a[i] * n + t) % 16;
	}
	if (k > 0)
	{
		a[0]++;
		a = (int*)realloc(a, (a[0] + 1) * sizeof(int));
		a[a[0]] = k;
	}

	return a;
}

int main()
{
	int* a;

	a = (int*)malloc(2 * sizeof(int));
	a[0] = 1;
	a[1] = 3;

	for (int i = 0; i < 4999; i++)
	{
		a = multip16(3, a);
	}

	printf("This is 3^5000 in hexadecimal system:\n");

	for (int i = a[0]; i > 0; i--)
	{
		switch (a[i])
		{
		    case 10:
			{
				printf("A");
				break;
			}
			case 11:
			{
				printf("B");
				break;
			}
			case 12:
			{
				printf("C");
				break;
			}
			case 13:
			{
				printf("D");
				break;
			}
			case 14:
			{
				printf("E");
				break;
			}
			case 15:
			{
				printf("F");
				break;
			}
			default:
			{
				printf("%d", a[i]);
				break;
			}
		}
	}
	free(a);
	_getch();
	return 0;
}