//
// Created by rinsler on 25.10.17.
//

#include <memory.h>
#include <ctype.h>


int starts_with(char *s1, char *s2)
{
    size_t s1_len = strlen(s1);
    size_t s2_len = strlen(s2);

    return s1_len < s2_len ? 0 : !strncmp(s1, s2, s2_len);
}

int parse_int(char *s, int *error)
{
    while (!isdigit(*s))
        s++;

    if (*s == '\0')
    {
        *error = 1;
        return 0;
    }

    int v = 0;
    while (isdigit(*s))
        v = v * 10 + (*s - '0');

    *error = 0;
    return v;
}


#include "str_funcs.h"
