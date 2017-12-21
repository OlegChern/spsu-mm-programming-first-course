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
	printf("Amount of digits: %d\n\n", number->amount);

	for (int i = number->amount - 1; i >= 0; i--)
	{
		// as BASE == 16, just transform 10->A, 11->B etc

		WORD value = number->values[i];

		if (value >= 10)
		{
			value -= 10;
			value += 'A';
		}
		else
		{
			value += '0';
		}

		printf("%c", value);
	}

	printf("\n\n");
}

APN *APNPower(APN *number, UINT pow)
{
	switch (pow)
	{
		case 2:
		{
			APN *power = APNMultiply(number, number);

			return power;
			break;
		}	
		case 1:
		{
			return number;
			break;
		}
		case 0:
		{
			return APNCreateWithValue(1);
			break;
		}
		default:
		{
			if (pow % 2 == 0)
			{
				APN *temp = APNPower(number, pow / 2);
				APN *power = APNMultiply(temp, temp);

				APNFree(temp);

				//printf("Power: %d\n", pow);
				//printHex(power);

				return power;
			}
			else
			{
				APN *temp = APNPower(number, pow - 1);
				APN *power = APNMultiply(number, temp);

				APNFree(temp);

				//printf("Power: %d\n", pow);
				//printHex(power);

				return power;
			}
			break;
		}
	}

	return NULL;
}

APN *APNMultiply(APN *a, APN *b)
{
	UINT amount = a->amount + b->amount;

	/*if (amount > SIMPLEMULTIP)
	{
		return APNKaratsubaMultiply(a, b);
	}*/

	APN	*result = APNCreateWithAmount(amount);


	for (UINT i = 0; i < a->amount; i++)
	{
		for (UINT j = 0; j < b->amount; j++)
		{
			result->values[i + j] += a->values[i] * b->values[j];
		}
	}

	APNNormalize(result);

	return result;
}

void APNNormalize(APN *number)
{
	WORD carry = 0;

	for (UINT i = 0; i < number->amount; i++)
	{
		number->values[i] += carry;

		carry = number->values[i] / BASE;
		number->values[i] %= BASE;
	}

	if (carry != 0)
	{
		number->values = (WORD*)realloc(number->values, sizeof(WORD) * (number->amount + 1));
		number->values[number->amount] = carry;
		number->amount++;
	}
	else 
	{
		UINT newAmount = number->amount;

		// check zero at the beginning of APN
		for (UINT i = number->amount - 1; i >= 0; i--)
		{
			if (number->values[i] == 0)
			{
				newAmount--;
			}
			else
			{
				break;
			}
		}
		
		if (newAmount != number->amount)
		{
			//number->parts = (APNPart**)realloc(number->parts, sizeof(APNPart*) * newAmount);
			number->values = (WORD*)realloc(number->values, sizeof(WORD) * newAmount);
			
			for (UINT i = number->amount; i < newAmount; i++)
			{
				number->values[i] = 0;
			}

			number->amount = newAmount;
		}
	}
}

APN *APNCreateWithValue(WORD value)
{
	APN *number = (APN*)malloc(sizeof(APN));

	number->values = (WORD*)malloc(sizeof(WORD));
	number->values[0] = value;

	number->amount = 1;

	APNNormalize(number);

	return number;
}

APN *APNCreateWithAmount(UINT amount)
{
	APN *number = (APN*)malloc(sizeof(APN));

	number->amount = amount;
	number->values = (WORD*)malloc(sizeof(WORD) * amount);

	for (UINT i = 0; i < amount; i++)
	{
		number->values[i] = 0;
	}

	return number;
}

void APNFree(APN *number)
{
	free(number);
}

APN *APNCopy(APN* source, UINT from, UINT to)
{
	APN *number = APNCreateWithAmount(to - from);

	for (UINT i = 0, j = from; j < to; i++, j++)
	{
		number->values[i] = source->values[j];
	}

	return number;
}

void APNResize(APN *number, UINT newAmount)
{
	UINT amount = number->amount;

	number->values = (WORD*)realloc(number->values, sizeof(WORD) * newAmount);
	number->amount = newAmount;

	for (UINT i = amount; i < newAmount; i++)
	{
		number->values[i] = 0;
	}
}

APN *APNSum(APN *a, APN *b)
{
	UINT amount = MAX(a->amount, b->amount) + 1; // a->amount + b->amount;
	APN	*result = APNCreateWithAmount(amount);

	for (UINT i = 0; i < amount; i++)
	{
		UINT sum = 0;

		if (i < a->amount)
		{
			sum += a->values[i]; 
		}

		if (i < b->amount)
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
	UINT amount = MAX(a->amount, b->amount) + 1; // a->amount + b->amount;
	APN	*result = APNCreateWithAmount(amount);

	for (UINT i = 0; i < amount; i++)
	{
		UINT sub = 0;

		if (i < a->amount)
		{
			sub += a->values[i];
		}

		if (i < b->amount)
		{
			sub -= b->values[i];
		}

		result->values[i] = sub;
	}

	APNNormalize(result);

	return result;
}

/*APN *APNKaratsubaMultiply(APN *a, APN *b)
{

	// DELETE OR FINISH

	UINT amount = a->amount + b->amount; // MAX(aAmount, bAmount);

	if (amount <= SIMPLEMULTIP)
	{
		return APNMultiply(a, b);
	}

	UINT k = amount / 2;

	APN	*aLeft	= copyNumber(a, k, a->amount);
	APN	*aRight	= copyNumber(a, 0, k);

	APN	*bLeft	= copyNumber(b, k, b->amount);
	APN	*bRight	= copyNumber(b, 0, k);

	APN	*sumA = APNSum(aLeft, aRight);
	APN	*sumB = APNSum(bLeft, bRight);

	APN	*m0 = APNKaratsubaMultiply(aLeft, bLeft);
	APN	*m1 = APNKaratsubaMultiply(aRight, bRight);
	APN	*m2 = APNKaratsubaMultiply(sumA, sumB);


	APN	*result = APNCreateWithAmount(amount);
	// m0 * base^amount + (m2 - m0 - m1) * base^k + m1

	APNNormalize(result);

	return result;
}*/