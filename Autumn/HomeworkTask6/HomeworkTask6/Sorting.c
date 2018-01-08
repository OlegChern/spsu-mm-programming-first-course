//#pragma warning(disable:4133)

#include	<stdlib.h>
#include	<stdio.h>
#include	<time.h>

#include	"Sorting.h"

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

	size_t		sourceSize, 
				amount;

	const char	*tempName = "D:\\temp.txt";

	// memory mapping
	map = mmap(sourceName, OPEN_EXISTING, 0);
	if (map == NULL)
	{
		printf("Can't map source file!\n");
		return 0;
	}

	// data
	source = map->dataPtr;
	sourceSize = map->size;

	// count strings
	{
		size_t allocated = LARGECHUNK;

		stringsArray = (STRING*)malloc(sizeof(STRING) * allocated);
		stringsArray[0] = source;

		amount = 0;

		for (size_t i = 0; i < sourceSize; i++)
		{
			if (source[i] == '\n')
			{
				amount++;

				if (amount >= allocated)
				{
					allocated += LARGECHUNK;
					stringsArray = (STRING*)realloc(stringsArray, sizeof(STRING) * allocated);
				}

				size_t next = i + 1;

				if (next < sourceSize)
				{
					stringsArray[amount] = &source[next];
				}

			}
		}
	}

	// sorting
	qsort(stringsArray, amount, sizeof(STRING), compareStrings);

	remove(tempName);

	// map temp
	tempMap = mmap(tempName, CREATE_ALWAYS, sourceSize);
	if (tempMap == NULL)
	{
		free(stringsArray);
		unmap(map);

		printf("Can't map temp file!\n");
		return 0;
	}

	// data
	temp = tempMap->dataPtr;

	size_t charIndex = 0;

	for (size_t stringIndex = 0; stringIndex < amount; stringIndex++)
	{
		if (charIndex >= sourceSize)
		{
			break;
		}

		size_t offset = 0;
		char chr;

		do
		{
			chr = stringsArray[stringIndex][offset];

			temp[charIndex] = chr;
			charIndex++;

			offset++;

		} while (chr != '\n' && chr != '\0');
	}

	// copy
	memcpy(source, temp, sourceSize);

	// free memory
	free(stringsArray);

	unmap(tempMap);
	unmap(map);

	remove(tempName);
	
	return 1;
}

int as = 0;

int compareStrings(const void *aPtr, const void *bPtr)
{
	as++;

    char *a = *(char**)aPtr;
    char *b = *(char**)bPtr;

    while (*a == *b && *a != '\n') // (*b != '\n') is over condition
    {
        a++;
        b++;
    }

    // '\n' is less than other symbols

    return  *a - *b;
}

FILEMAPPING *mmap(const char *name, DWORD disposition, DWORD size)
{
	LPCSTR lpcstrName = (LPCSTR)name;

	HANDLE hFile = CreateFileA(lpcstrName, GENERIC_READ | GENERIC_WRITE, 0, NULL, disposition, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		DWORD error = GetLastError();

		if (error == 32)
		{
			printf("File is opened in another program (error %d).\n", error);
		}
		else
		{
			printf("CreateFile error: %d.\n", error);
		}

		return NULL;
	}

	DWORD dwFileSize = GetFileSize(hFile, NULL);

	if (dwFileSize == INVALID_FILE_SIZE)
	{
		CloseHandle(hFile);

		printf("GetFileSize failed!\n");
		return NULL;
	}

	HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, size, NULL);

	if (hMapping == NULL)
	{
		CloseHandle(hFile);

		printf("CreateFileMapping error: %d\n", GetLastError());
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