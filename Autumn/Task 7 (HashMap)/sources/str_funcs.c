//
// Created by rinsler on 25.10.17.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../headers/array_utils.h"


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

static int isNotEmpty(const void *s)
{
    return (*(char**)s)[0] != 0;
}

static void free_str(void *s)
{
    free((*(char**)s));
}

int split(const char *s, char ***result, size_t *result_len, char delim, int doFilter)
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

    if (doFilter)
    {
        size_t res_len = (size_t) cnt;
        filter((void **) &res, sizeof(char*), &res_len, isNotEmpty, free_str);

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

