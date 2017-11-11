//
// Created by rinsler on 25.10.17.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../headers/array_utils.h"
#include "../headers/str_funcs.h"


const int EMPTY = 1;
const int TOO_BIG = 2;
const int NAN = 3;


int parse_int(char *s, int *error)
{
    char *begin = s;

    if (*s == 0)
    {
        *error = EMPTY;
        return 0;
    }

    while (*s != 0)
    {
        if (!isdigit(*s))
        {
            *error = NAN;
            return 0;
        }
        s++;
    }

    s = begin;

    int v = 0;
    int sign = (s > begin && *(s - 1) == '-') ? -1 : 1;

    while (isdigit(*s))
    {
        if (v > INT_MAX / 10 || v * 10 > INT_MAX - (*s - '0'))
        {
            *error = TOO_BIG;
            return 0;
        }

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
            return -1;
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

static int is_not_empty(const void *s)
{
    return (*(char**)s)[0] != 0;
}

static void free_str(void *s)
{
    free((*(char**)s));
}

int split(const char *s, char ***result, size_t *result_len, char delim, int do_filter)
{
    int cnt = 0;

    if (s == NULL)
        return 0;

    if (s[0] == 0)
    {
        *result = malloc(sizeof(char*));
        if (!*result)
            return 0;
        **result = "";
        *result_len = 0;
        return 1;
    }

    for (int i = 0; s[i] != 0; ++i)
        if (s[i] == delim)
            cnt++;

    cnt++;

    char **res = malloc(sizeof(char*) * cnt);
    if (!res)
        return 0;

    int s_i = 0, r_i = 0, prev = -1;
    for (; s[s_i] != 0; ++s_i)
    {
        if (s[s_i] == delim)
        {
            int len = s_i - (prev + 1);
            res[r_i] = malloc(sizeof(char) * (len + 1));
            if (!res[r_i])
                return 0;
            strncpy(res[r_i], &s[s_i - len], (size_t) len);
            res[r_i][len] = 0;

            prev = s_i;
            r_i++;
        }
    }

    int len = s_i - (prev + 1);
    res[r_i] = malloc(sizeof(char) * (len + 1));
    if (!res[r_i])
        return 0;
    strncpy(res[r_i], &s[s_i - len], (size_t) len);
    res[r_i][len] = 0;

    if (do_filter)
    {
        size_t res_len = (size_t) cnt;
        filter((void **) &res, sizeof(char *), &res_len, is_not_empty, free_str);

        *result = res;
        *result_len = res_len;
    }
    else
    {
        *result = res;
        *result_len = (size_t) cnt;
    }

    return 1;
}

int is_consisted_of_letters(const char *s)
{
    if (s == NULL || s[0] == 0)
        return 0;

    for (int i = 0; s[i] != 0; ++i)
        if (!isalpha(s[i]))
            return 0;
    return 1;
}