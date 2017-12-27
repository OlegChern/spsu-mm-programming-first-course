//#pragma warning(disable:4996) // to use _open()

#include <stdlib.h>
#include <stdio.h>

#include "Sorting.h"

int main(int argc, char **argv)
{
    char *path;

    if (argc < 2)
    {
        path = (char*)malloc(sizeof(char) * 128);

        printf("Enter path to file:\n");
        scanf("%s", path);
    }
    else
    {
        path = argv[1];
    }

    float startTime = (float)clock() / (float)CLOCKS_PER_SEC;

    if (sortWithMMap(path))
    {
        float endTime = (float)clock() / (float)CLOCKS_PER_SEC;
        printf("Done with %f sec.\n", endTime - startTime);
    }

    free(path);

    /*while(!sortWithMMap(argv[1]))
    {
        printf("Path to source file:\n");
        scanf("%s", argv[1]);

        startTime = (float)clock() / (float)CLOCKS_PER_SEC;
    }*/

    return 0;
}

int sortWithMMap(char *sourceName)
{
    char    *source;
	int		sourceDescriptor;
	size_t	sourceSize;

	// descriptor
    sourceDescriptor = _open(sourceName, O_RDWR);

    if (sourceDescriptor < 0)
	{
		printf("Can't open source file!\n");
		return 0;
	}

	// file size
    {
		STAT sourceStat;
		stat(sourceName, &sourceStat);
		sourceSize = sourceStat.st_size;
	}

	// memory mapping
	source = (char*)mmap(NULL, sourceSize, PROT_WRITE | PROT_READ, MAP_SHARED, sourceDescriptor, 0);

	if (source == MAP_FAILED)
	{
		printf("Can't map source file!\n");
		return 0;
	}

    // strings
	size_t	amount = 0;
	size_t	allocated = 0;

	STRING *strings = (STRING*)malloc(sizeof(STRING) * CHUNK);

	strings[0].start = source;

	for (size_t i = 0; i < sourceSize; i++)
    {
        if (source[i] == '\n')
        {
			strings[amount].end = &source[i];

			amount++;

			if (amount >= allocated)
			{
				STRING *strings = (STRING*)realloc(strings, sizeof(STRING) * CHUNK);
			}

			if (i + 1 < sourceSize)
			{
				strings[amount].start = &source[i + 1];
			}
        }
    }

    // sorting
	qsortStrings(strings, 0, amount);

    for (size_t i = 0; i < amount; i++)
    {
        size_t j = 0;

        char *start = strings[i].start;
        char *end = strings[i].start;

        while (start != end)
        {
            source[i + j] = *start;

            j++;
            start++;
        }
    }

    // memory
	free(strings);
	munmap(source, sourceSize);
    _close(sourceDescriptor);

    return 1;
}

void qsortStrings(STRING *source, int start, int end)
{
	if (start >= end)
	{
		return;
	}

	STRING *pivot = &source[end];

	int index = start;

	for (int i = start; i < end; i++)
	{
		if (compareStrings(&source[i], pivot) < 0)
		{
			swapStrings(&source[i], &source[index]);
			index++;
		}
	}

	if (compareStrings(&source[end], &source[index]) < 0)
	{
		swapStrings(&source[end], &source[index]);
	}

	qsortStrings(source, start, index - 1);
	qsortStrings(source, index + 1, end);
}

int compareStrings(STRING *aStr, STRING *bStr)
{
	char *a = aStr->start;
	char *b = bStr->start;

	while (*a == *b && *a != '\n') // (*b != '\n') is over condition
	{
		a++;
		b++;
	}

	// '\n' is less than other symbols so
	return  *a - *b;
}

void swapStrings(STRING *a, STRING *b)
{
	char *tempStart = a->start;
	char *tempEnd = a->end;

	a->start = b->start;
	a->end = b->end;

	b->start = tempStart;
	b->end = tempEnd;
}

/*int cmpStr(const void *aPtr, const void *bPtr)
{
    char *a = (char*)aPtr;
    char *b = (char*)bPtr;

    while (*a == *b && *a != '\n') // (*b != '\n') is over condition
    {
        a++;
        b++;
    }

    // '\n' is less than other symbols

    return  *a - *b;
}

void quickSort(int arr[], int start, int end)
{
	if (start >= end)
	{
		return;
	}

	int pivot = arr[end];

	int index = start;

	for (int i = start; i < end; i++)
	{
		if (arr[i] < pivot)
		{
			int temp = arr[i];

			arr[i] = arr[index];
			arr[index] = temp;

			index++;
		}
	}

	if (arr[end] < arr[index])
	{
		int temp = arr[end];

		arr[end] = arr[index];
		arr[index] = temp;
	}

	quickSort(arr, start, index - 1);
	quickSort(arr, index + 1, end);
}

void qsortStrings(char *source, char *target, int start, int end)
{
	if (start >= end)
	{
		return;
	}

	char *pivot = source[end];

	int index = start;

	for (int i = start; i < end; i++)
	{
		if (cmpStr(source[i], pivot) < 0)
		{
			int temp = source[i];

			source[i] = source[index];
			source[index] = temp;

			index++;
		}
	}

	if (source[end] < source[index])
	{
		int temp = source[end];

		source[end] = source[index];
		source[index] = temp;
	}

	quickSort(source, target, start, index - 1);
	quickSort(source, target, index + 1, end);
}*/
