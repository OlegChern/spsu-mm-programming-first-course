#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

int main()
{
	BigInteger *a;
	int b;
	BigInteger *z;

	a = create(3);
	b = 5000;
	z = create(1);

	while (b)
	{
		if (b & 1)
		{
			BigInteger *oldZ = z;
			z = multiply(z, a);
			destroy(oldZ);
		}
		if (b > 1)
		{
			BigInteger *oldA = a;
			a = multiply(a, a);
			destroy(oldA);
		}
		b >>= 1;
	}
	destroy(a);

	char *result = toString(z);
	destroy(z);
	printf("Result = %s\n", result);
	free(result);

	system("pause");
	return 0;
}
