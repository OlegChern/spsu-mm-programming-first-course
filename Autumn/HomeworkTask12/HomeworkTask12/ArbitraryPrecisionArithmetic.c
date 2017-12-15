#include "ArbitraryPrecisionArithmetic.h"

int main()
{
	// hex 3^5000

	APNumber *result = createNumber(1);
	APNumber *three = createNumber(1);

	result->parts[0]->value = 3;
	three->parts[0]->value = 3;

	for (int i = 0; i < 5000; i++)
	{
		karatsubaMultiply(result, three);
	}
	
	printHex(result);

	return 0;
}

void printHex(APNumber *number)
{
	for (int i = number->count; i >= 0; i--)
	{
		number->parts[i];
	}
}

APNumber *sum(APNumber *a, APNumber *b)
{
	UINT		count = a->count + b->count;
	APNumber	*result = createNumber(count);

	for (UINT i = 0; i < count; i++)
	{
		result->parts[i]->value = a->parts[i]->value + b->parts[i]->value;
	}

	normalize(result);

	return result;
}

APNumber *subtract(APNumber *a, APNumber *b)
{
	UINT		count = MAX(a->count, b->count);
	APNumber	*result = createNumber(count);

	for (UINT i = 0; i < count; i++)
	{
		result->parts[i]->value = a->parts[i]->value - b->parts[i]->value;
	}

	normalize(result);

	return result;
}

APNumber *multiplySimply(APNumber *a, APNumber *b)
{
	UINT		count = MAX(a->count, b->count);
	APNumber	*result = createNumber(count);

	for (UINT i = 0; i < count; i++)
	{
		result->parts[i]->value = a->parts[i]->value * b->parts[i]->value;
	}

	normalize(result);

	return result;
}

APNumber *karatsubaMultiply(APNumber *a, APNumber *b)
{
	UINT		aCount = a->count;
	UINT		bCount = b->count;

	UINT		count = MAX(aCount, bCount);

	if (count <= SIMPLEMULTIP) 
	{
		return multiplySimply(a, b);
	}

	UINT		k = count / 2;

	APNumber	*aLeft	= copyNumber(a, k, aCount);
	APNumber	*aRight	= copyNumber(a, 0, k);

	APNumber	*bLeft	= copyNumber(a, k, bCount);
	APNumber	*bRight	= copyNumber(a, 0, k);

	APNumber	*sumA = sum(aLeft, aRight);
	APNumber	*sumB = sum(bLeft, bRight);

	APNumber	*m0 = karatsubaMultiply(aLeft, bLeft);
	APNumber	*m1 = karatsubaMultiply(aRight, bRight);
	APNumber	*m2 = karatsubaMultiply(sumA, sumB);


	APNumber	*result = createNumber(count);
	// m0 * base^count + (m2 - m0 - m1) * base^k + m1

	normalize(result);

	return result;
}

void normalize(APNumber *number)
{
	for (UINT i = 0; i < number->count - 1; i++)
	{
		number->parts[i + 1]->value = number->parts[i]->value / BASE;
		number->parts[i]->value %= BASE;
	}

	WORD div;

	while ((div = number->parts[number->count]->value / BASE) > 0)
	{
		number->parts[number->count]->value %= BASE;

		APNPart *newPart = createPartWithValue(number->count + 1, div);
		addPart(number, newPart);

		number->count++;
	}
}

APNumber *createNumber(UINT count)
{
	APNumber *number = (APNumber*)malloc(sizeof(APNumber));
	number->count = 0;

	for (UINT i = 0; i < count; i++)
	{
		addNewPart(number);
	}

	return number;
}

APNumber *copyNumber(APNumber* source, UINT from, UINT to)
{
	APNumber *number = createNumber(to - from);

	for (UINT i = 0, j = from; j < to; i++, j++)
	{
		number->parts[i]->value = source->parts[j]->value;
	}

	return number;
}

APNPart *createPart(UINT index)
{
	APNPart	*part = (APNPart*)malloc(sizeof(APNPart));
	part->index = index;

	return part;
}

APNPart *createPartWithValue(UINT index, UINT value)
{
	APNPart	*part = (APNPart*)malloc(sizeof(APNPart));
	part->index = index;
	part->value = value;

	return part;
}

void addPart(APNumber *number, APNPart *part)
{
	UINT count = number->count;

	part->index = count;

	number->parts[count] = part;
	number->count = count + 1;
}

void addNewPart(APNumber *number)
{
	APNPart *part = createPart(number->count);
	addPart(number, part);
}

APNPart *addNewPartWithValue(APNumber *number, UINT value)
{
	UINT index = number->count;
	APNPart *part = createPartWithValue(index, value);

	number->parts[index] = part;
	number->count = index + 1;

	return part;
}

void addNewPartWithIndex(APNumber *number, UINT index)
{
	APNPart *part = createPart(index);

	number->parts[index] = part;
	number->count++;

	//return part;
}

void resizeNumber(APNumber *number, UINT newCount)
{
	UINT count = number->count;
	number->count = newCount;

	if (count < newCount)
	{
		for (UINT i = count; i < newCount; i++)
		{
			addNewPartWithIndex(number, i);
		}
	}
	else
	{
		for (UINT i = count; i > newCount; i--)
		{
			free(number->parts[i]);
		}
	}

}