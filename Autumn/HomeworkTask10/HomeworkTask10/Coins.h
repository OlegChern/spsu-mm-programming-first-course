#pragma once

#include <stdlib.h>
#include <stdio.h>

#define FALSE 0
#define TRUE 1
#define CHUNK 8

int getInt(int *target)
{
	while (TRUE)
	{
		char current;
		size_t length = 0, size = CHUNK;

		char *source = (char*)malloc(sizeof(char) * size);
		if (!*source)
		{
			printf("Can't allocate!\n");
			return FALSE;
		}

		while (TRUE)
		{
			current = getchar();

			if (current == '\n') // if end of the line
			{
				if (length > 0)
				{
					source[length] = '\0';
					(*target) = atoi(source);

					if (*target != 0)
					{
						return TRUE;
					}
					else
					{
						return FALSE;
					}
				}

				return FALSE;
			}

			if (current < '0' || current > '9') // just ignore
			{
				continue;
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
					return FALSE;
				}
			}
		}
	}

	return FALSE;
}