#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char * firstName = "Bekzat",
		*name = "Alenov",
		*fatherName = "Muratbekovich";
	int p = strlen(firstName) * strlen(name) * strlen(fatherName);

	printf("%d\n", p);
	unsigned int minusP = -p;

	unsigned int mask = 0x80000000l;
	int i;
	for (i = 0; i < 32; i++)
	{
		printf("%c", (mask & minusP) == 0 ? '0' : '1');
		mask >>= 1;
	}
	printf("\n");



	float f = p;
	unsigned int *pf = (unsigned int*)&f;
	mask = 0x80000000l;
	for (i = 0; i < 32; i++)
	{
		printf("%c", (mask & *pf) == 0 ? '0' : '1');
		mask >>= 1;
	}
	printf("\n");



	double df = -p;
	unsigned long long int *pdf = (unsigned long long int*)&df;
	unsigned long long int mask1 = 0x8000000000000000l;
	for (i = 0; i < 64; i++)
	{
		printf("%c", (mask1 & *pdf) == 0 ? '0' : '1');
		mask1 >>= 1;
	}

	printf("\n");
	system("pause");
	return 0;
}
