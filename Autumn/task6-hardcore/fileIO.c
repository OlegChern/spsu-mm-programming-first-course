#include <malloc.h>
#include <stdio.h>
#include <mem.h>
#include "fileIO.h"

/// @private
void swap(char **a, char **b)
{
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}

// TODO: test on small buffer sizes
/// @private
/// @param buf buffer as part of string to be analyzed
/// @param length max number of characters to be processed
unsigned int getStringLengthDelta(const char *buf, unsigned int length)
{
    unsigned int result = 0;
    while (1)
    {
        if (result >= length || buf[result] == '\n')
            return result;
        result++;
    }
}

int fillTable(HashTable *table, char *path)
{
    FILE *fileStreamIn = fopen(path, "r");
    if (fileStreamIn == NULL)
    {
        perror("fopen");
        return 1;
    }

    char *prevBuf = (char *) malloc(sizeof(char) * BUFFER_SIZE);
    char *buf = (char *) malloc(sizeof(char) * BUFFER_SIZE);
    if (prevBuf == NULL || buf == NULL)
    {
        perror("malloc");
        return 1;
    }

    int result = 0;
    char *currentLine = NULL;
    unsigned int currentLineLength = 0;
    do
    {
        result = fread(buf, sizeof(char), BUFFER_SIZE, fileStreamIn);
        unsigned int offset = 0;
        do
        {
            unsigned int lengthDelta = getStringLengthDelta(buf, BUFFER_SIZE - offset);
            if (lengthDelta != 0)
            {
                if (currentLine == NULL)
                {
                    currentLine = malloc(sizeof(char) * lengthDelta);
                    currentLineLength = lengthDelta;
                }
                else
                {
                    currentLineLength += lengthDelta;
                    realloc(currentLine, currentLineLength);
                }
                // TODO: debug this
                memcpy(currentLine + currentLineLength - lengthDelta, buf + offset, sizeof(char) * lengthDelta);
            }
            else if (currentLine != NULL)
            {
                currentLineLength++;
                realloc(currentLine, currentLineLength);
                currentLine[currentLineLength - 1] = '\0';
                incElementAt(table, currentLine);
            }
        }
        while (condition);
    }
    while (result == BUFFER_SIZE);

    fclose(fileStreamIn);
    free(prevBuf);
    free(buf);
    return 0;
}
