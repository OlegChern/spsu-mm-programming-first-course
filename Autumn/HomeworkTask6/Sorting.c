//#pragma warning(disable:4996) // to use _open()

#include "Sorting.h"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Not enough arguments! Should be:\n");
		printf("  [source path] [target path]\n\n");
        return 0;
    }

    while(!sortWithMMap(argv[1], argv[2]))
    {
        printf("Path to source file:\n");
        scanf("%s", argv[1]);

        printf("Path to target file:\n");
        scanf("%s", argv[2]);
    }

    printf("Done with %ld sec.\n", clock() / CLOCKS_PER_SEC);

    return 0;
}

int sortWithMMap(char *sourceName, char *targetName)
{
    char    *source,
            *target;

	int		sourceDescriptor,
			targetDescriptor;

	size_t	sourceSize,
			targetSize;

	// descriptors
    sourceDescriptor = _open(sourceName, O_RDONLY);
	targetDescriptor = _open(targetName, O_RDWR | O_TRUNC | O_CREAT);

    if (sourceDescriptor < 0)
	{
		printf("Can't open source file!\n");
		return 0;
	}

	if (targetDescriptor < 0)
	{
		printf("Can't open target file!\n");
		return 0;
	}

	// file sizes
    {
		STAT sourceStat, targetStat;

		stat(sourceName, &sourceStat);
		stat(targetName, &targetStat);

		sourceSize = sourceStat.st_size;
		targetSize = targetStat.st_size;
	}

	// memory mapping
	source = (char*)mmap(NULL, sourceSize, PROT_READ, MAP_SHARED, sourceDescriptor, 0);
	target = (char*)mmap(NULL, targetSize, PROT_WRITE | PROT_READ, MAP_SHARED, targetDescriptor, 0);

	if (source == MAP_FAILED)
	{
		printf("Can't map source file!\n");
		return 0;
	}

	if (target == MAP_FAILED)
	{
		munmap(source, sourceSize);

		printf("Can't map target file!\n");
		return 0;
	}

    // strings amount
	size_t amount = 0;

	for (size_t i = 0; i < sourceSize; i++)
    {
        if (source[i] == '\n')
        {
            amount++;
        }
    }

    qsort(source, amount, sizeof(char*), int (*cmpStr)(const void*, const void*));

    _close(sourceDescriptor);
    _close(targetDescriptor);

    return 1;
}

int cmpStr(const void *aPtr, const void *bPtr)
{
    char *a = (char*)aPtr;
    char *b = (char*)bPtr;

    // (*b != '\n') is over condition
    while (*a == *b && *a != '\n') // && *b != '\n')
    {
        a++;
        b++;
    }

    // '\n' is less than other symbols

    return  *a - *b;
}
