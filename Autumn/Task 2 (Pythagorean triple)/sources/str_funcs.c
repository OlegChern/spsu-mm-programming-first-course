#include <stdio.h>
#include <stdlib.h>


int getline(char **line, size_t *n, FILE *stream)
{
    if (line == NULL)
        return -1;

    if (*line == NULL && *n == 0)
    {
        *n = 8;
        if ((*line = malloc(*n)) == NULL)
            return 1;
    }

    int c, cnt;
    for (c = fgetc(stream), cnt = 0; c != '\n' && c != EOF; c = fgetc(stream), cnt++)
    {
        if (cnt == *n)
        {
            if ((*line = realloc(*line, *n * 2)) == NULL)
                return -1;
            *n *= 2;
        }

        (*line)[cnt] = (char) c;
    }

    if (c == EOF)
        return -1;

    if (cnt == *n)
    {
        if ((*line = realloc(*line, *n + 1)) == NULL)
            return -1;
        (*n)++;
    }

    (*line)[cnt] = '\0';

    return cnt;
}