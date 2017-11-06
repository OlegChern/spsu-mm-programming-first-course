//
// Created by rinsler on 25.10.17.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int starts_with(char *s1, char *s2)
{
    size_t s1_len = strlen(s1);
    size_t s2_len = strlen(s2);

    return s1_len < s2_len ? 0 : !strncmp(s1, s2, s2_len);
}

int parse_int(char *s, int *error)
{
    char *begin = s;
    while (!isdigit(*s))
        s++;

    if (*s == '\0')
    {
        *error = 1;
        return 0;
    }

    int v = 0;
    int sign = (s > begin && *(s - 1) == '-') ? -1 : 1;

    while (isdigit(*s))
    {
        v = v * 10 + (*s - '0');
        s++;
    }

    *error = 0;
    return v * sign;
}

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

char* parse_word(char *s)
{

}