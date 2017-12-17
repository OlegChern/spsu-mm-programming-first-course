#include "ArbitraryPrecisionArithmetic.h"

int main()
{
	// hex 3^5000

	APN *three = APNCreateWithValue(3);
	APN *result = APNPower(three, 5000);

	printHex(result);

	APNFree(three);
	APNFree(result);

	return 0;
}

void printHex(APN *number)
{
	printf("%d\n\n", number->count);

	for (int i = number->count - 1; i >= 0; i--)
	{
		printf("%d\n", number->values[i]);
	}
}

APN *APNPower(APN *number, UINT pow)
{
	if (pow == 0)
	{
		return APNCreateWithValue(1);
	}

	if (pow % 2 == 0)
	{
		APN *temp = APNPower(number, pow / 2);
		APN *power = APNMultiply(temp, temp);

		APNFree(temp);
		return power;
	}
	else
	{
		APN *temp = APNPower(number, pow - 1);
		APN *power = APNMultiply(number, temp);

		APNFree(temp);
		return power;
	}
}

APN *APNSum(APN *a, APN *b)
{
	UINT count = MAX(a->count, b->count) + 1; // a->count + b->count;
	APN	*result = APNCreateWithCount(count);

	for (UINT i = 0; i < count; i++)
	{
		UINT sum = 0;

		if (i < a->count)
		{
			sum += a->values[i]; 
		}

		if (i < b->count)
		{
			sum += b->values[i];
		}

		result->values[i] = sum;
	}

	APNNormalize(result);

	return result;
}

APN *APNSubtract(APN *a, APN *b)
{
	UINT count = MAX(a->count, b->count) + 1; // a->count + b->count;
	APN	*result = APNCreateWithCount(count);

	for (UINT i = 0; i < count; i++)
	{
		UINT sub = 0;

		if (i < a->count)
		{
			sub += a->values[i];
		}

		if (i < b->count)
		{
			sub -= b->values[i];
		}

		result->values[i] = sub;
	}

	APNNormalize(result);

	return result;
}

APN *APNMultiply(APN *a, APN *b)
{
	UINT count = a->count + b->count;

	/*if (count > SIMPLEMULTIP)
	{
		return APNKaratsubaMultiply(a, b);
	}*/

	APN	*result = APNCreateWithCount(count);

	for (UINT i = 0; i < count; i++)
	{
		UINT compos;

		if (i < a->count && i < b->count)
		{
			compos = a->values[i] * b->values[i];
		}
		else
		{
			compos = 0;
		}

		result->values[i] = compos;
	}

	APNNormalize(result);

	return result;
}

APN *APNKaratsubaMultiply(APN *a, APN *b)
{
	UINT count = a->count + b->count; // MAX(aCount, bCount);

	if (count <= SIMPLEMULTIP)
	{
		return APNMultiply(a, b);
	}

	UINT k = count / 2;

	APN	*aLeft	= copyNumber(a, k, a->count);
	APN	*aRight	= copyNumber(a, 0, k);

	APN	*bLeft	= copyNumber(b, k, b->count);
	APN	*bRight	= copyNumber(b, 0, k);

	APN	*sumA = APNSum(aLeft, aRight);
	APN	*sumB = APNSum(bLeft, bRight);

	APN	*m0 = APNKaratsubaMultiply(aLeft, bLeft);
	APN	*m1 = APNKaratsubaMultiply(aRight, bRight);
	APN	*m2 = APNKaratsubaMultiply(sumA, sumB);


	APN	*result = APNCreateWithCount(count);
	// m0 * base^count + (m2 - m0 - m1) * base^k + m1

	APNNormalize(result);

	return result;
}

void APNNormalize(APN *number)
{
	WORD carry = 0;

	for (UINT i = 0; i < number->count; i++)
	{
		number->values[i] += carry;

		carry = number->values[i] / BASE;
		number->values[i] %= BASE;
	}

	if (carry != 0)
	{
		number->values = (WORD*)realloc(number->values, sizeof(WORD) * (number->count + 1));
		number->values[number->count] = carry;
		number->count++;
	}
	else 
	{
		UINT newCount = number->count;

		for (UINT i = number->count - 1; i >= 0; i--)
		{
			if (number->values[i] == 0)
			{
				newCount--;
			}
			else
			{
				break;
			}
		}
		
		if (newCount != number->count)
		{
			//number->parts = (APNPart**)realloc(number->parts, sizeof(APNPart*) * newCount);
			number->values = (WORD*)realloc(number->values, sizeof(WORD) * newCount);
			number->count = newCount;
		}
	}
}

APN *APNCreateWithValue(WORD value)
{
	APN *number = (APN*)malloc(sizeof(APN));

	number->values = (WORD*)malloc(sizeof(WORD));
	number->values[0] = value;

	number->count = 1;

	return number;
}

APN *APNCreateWithCount(UINT count)
{
	APN *number = (APN*)malloc(sizeof(APN));

	number->count = count;
	number->values = (WORD*)malloc(sizeof(WORD) * count);

	for (UINT i = 0; i < count; i++)
	{
		number->values[i] = 0;
	}

	return number;
}

void APNFree(APN *number)
{
	free(number);
}

APN *copyNumber(APN* source, UINT from, UINT to)
{
	APN *number = APNCreateWithCount(to - from);

	for (UINT i = 0, j = from; j < to; i++, j++)
	{
		number->values[i] = source->values[j];
	}

	return number;
}

void resizeNumber(APN *number, UINT newCount)
{
	UINT count = number->count;

	number->values = (WORD*)realloc(number->values, sizeof(WORD) * newCount);
	number->count = newCount;

	for (UINT i = count; i < newCount; i++)
	{
		number->values[i] = 0;
	}
}