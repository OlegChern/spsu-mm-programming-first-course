#pragma warning(disable:4996) // to use _open()
#pragma warning(disable:4133)

#include <stdlib.h>
#include <stdio.h>

#include "Sorting.h"

int main()
{
	float	startTime, endTime;
	char	*path;

	printf("Program sorts strings in file.");

	do
	{
		printf("\nEnter path to file:\n");
		path = getString();

		startTime = (float)clock() / (float)CLOCKS_PER_SEC;

	} while (!sortWithMemoryMapping(path));

	endTime = (float)clock() / (float)CLOCKS_PER_SEC;

	printf("Done with %f sec.\n", endTime - startTime);

	free(path);
	return 0;
}

int sortWithMemoryMapping(const char *sourceName)
{
	FILEMAPPING *map, 
				*tempMap;

	char		**stringsArray;
	char		*source,
				*temp;

	int			sourceDescriptor, 
				tempDescriptor;

	size_t		sourceSize, 
				amount;

	const char	*tempName = "temp.txt";

	// descriptor
	sourceDescriptor = _open(sourceName, O_RDWR);
	if (sourceDescriptor == -1)
	{
		printf("Can't open source file!\n");
		return 0;
	}

	// memory mapping
	map = mmap(sourceName, OPEN_EXISTING);
	if (map == NULL)
	{
		_close(sourceDescriptor);

		printf("Can't map source file!\n");
		return 0;
	}

	// data
	source = map->dataPtr;
	sourceSize = map->size;

	// count strings
	{
		size_t allocated = LARGECHUNK;

		stringsArray = (char**)malloc(sizeof(char*) * allocated);
		stringsArray[0] = source;

		amount = 1; // precount last string

		for (size_t i = 0; i < sourceSize; i++)
		{
			if (source[i] == '\n')
			{
				size_t next = i + 1;

				if (next < sourceSize)
				{
					stringsArray[amount] = &source[next];
				}

				amount++;

				if (amount >= allocated)
				{
					allocated += LARGECHUNK;
					stringsArray = (char**)realloc(stringsArray, sizeof(char*) * allocated);
				}
			}
		}
	}

	// sorting
	qsort(stringsArray, amount, sizeof(char), compareStrings);

	remove(tempName);

	// temp desciptor
	tempDescriptor = _open(sourceName, O_RDWR | O_CREAT | O_TRUNC);
	if (tempDescriptor == -1)
	{
		free(stringsArray);
		unmap(map);
		_close(sourceDescriptor);

		printf("Can't open temp file!\n");
		return 0;
	}

	// map temp
	tempMap = mmap(sourceName, CREATE_ALWAYS);
	if (tempMap == NULL)
	{
		free(stringsArray);
		unmap(map);
		_close(sourceDescriptor);
		_close(tempDescriptor);

		printf("Can't map temp file!\n");
		return 0;
	}

	// data
	temp = tempMap->dataPtr;

	for (size_t i = 0; i < sourceSize; i++)
	{
		char chr;
		size_t j = 0;

		while ((chr = stringsArray[i][j]) != '\n' && chr != '\0')
		{
			temp[i] = chr;
			j++;
		}
	}

	// copy
	memcpy(source, temp, sourceSize);

	// free memory
	free(stringsArray);

	unmap(tempMap);
	unmap(map);

	_close(tempDescriptor);
	_close(sourceDescriptor);

	remove(tempName);
	
	return 1;
}

int compareStrings(const void *aPtr, const void *bPtr)
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

FILEMAPPING *mmap(const char *name, DWORD disposition)
{
	HANDLE hFile = CreateFile(name, GENERIC_READ | GENERIC_WRITE, 0, NULL, disposition, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile error!\n");
		return NULL;
	}

	DWORD dwFileSize = GetFileSize(hFile, NULL);

	if (dwFileSize == INVALID_FILE_SIZE)
	{
		CloseHandle(hFile);

		printf("GetFileSize failed!\n");
		return NULL;
	}

	HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);

	if (hMapping == NULL)
	{
		CloseHandle(hFile);

		printf("CreateFileMapping failed!\n");
		return NULL;
	}

	char* dataPtr = (char*)MapViewOfFile(hMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, dwFileSize);
	
	if (dataPtr == NULL)
	{
		CloseHandle(hMapping);
		CloseHandle(hFile);

		printf("MapViewOfFile failed!\n");
		return NULL;
	}

	FILEMAPPING* mapping = (FILEMAPPING*)malloc(sizeof(FILEMAPPING));
	
	if (mapping == NULL) 
	{
		UnmapViewOfFile(dataPtr);
		CloseHandle(hMapping);
		CloseHandle(hFile);

		printf("Malloc failed!\n");
		return NULL;
	}

	mapping->hFile = hFile;
	mapping->hMapping = hMapping;
	mapping->dataPtr = dataPtr;
	mapping->size = (size_t)dwFileSize;

	return mapping;
}

void unmap(FILEMAPPING *mapping)
{
	UnmapViewOfFile(mapping->dataPtr);
	CloseHandle(mapping->hMapping);
	CloseHandle(mapping->hFile);

	free(mapping);
}

char *getString()
{
	while (TRUE)
	{
		int current;
		char sign = 1;
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

			if (current == '-' && length == 0)
			{
				sign = -1;
			}

			if (current == '\n')
			{
				source[length] = '\0';
				return source;
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

	return NULL;
}