//
// Created by rinsl_000 on 10.11.2017.
//

#include <stdlib.h>
#include <limits.h>
#include <memory.h>

#include "../headers/array_utils.h"


int filter(
        void **arr,
        size_t size,
        size_t *len,
        int (*condition)(const void *a),
        void (*free_elem)(void *a)
)
{
    int cnt = 0;

    for (int i = 0; i < *len; ++i)
        if (condition(*arr + size * i))
            cnt++;

    if (cnt == 0)
    {
        for (int i = 0; i < *len; ++i)
            free_elem(*arr + size * i);
        free(*arr);
        *arr = NULL;
        *len = 0;
        return 1;
    }

    void *res = malloc(size * cnt);
    if (!res)
        return 0;

    for (int i = 0, res_i = 0; i < *len; ++i) {
        if (condition(*arr + size * i)) {
            memcpy(res + size * res_i, *arr + size * i, size);
            res_i++;
        }
        else
            free_elem(*arr + size * i);
    }

    free(*arr);
    *arr = res;
    *len = (size_t) cnt;

    return 1;
}