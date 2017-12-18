//
// Created by rinsl_000 on 22.11.2017.
//

#include <stdlib.h>
#include "../headers/vector.h"
#include "../headers/errors.h"


void vectorInit(Vector **v, size_t length)
{
    if ((*v = malloc(sizeof(*v))) == NULL)
        return withError(NOT_ENOUGH_MEMORY);

    if (((*v)->arr = malloc(length * sizeof(*(*v)->arr))) == NULL)
        return withError(NOT_ENOUGH_MEMORY);

    (*v)->length = 0;
    (*v)->maxLength = length;
}

void vectorAppend(Vector **v, elem x)
{
    if (*v == NULL)
        return withError(NULL_PTR);

    if ((*v)->length < (*v)->maxLength)
    {
        (*v)->arr[(*v)->length++] = x;
        return;
    }
    else
    {
        Vector *tmp;
        vectorInit(&tmp, (*v)->maxLength * 2);
        if (error)
            return withError(error); // leaves error the same

        for (int i = 0; i < (*v)->length; ++i)
            tmp->arr[i] = (*v)->arr[i];

        (*v)->arr[(*v)->length] = x;

        tmp->length = (*v)->length + 1;
        tmp->maxLength = (*v)->maxLength * 2;

        free(*v);
        *v = tmp;
    }
}

void vectorSet(Vector *v, int p, elem data)
{
    if (p < 0 || p >= v->length)
        return withError(INCORRECT_PARAMS);

    v->arr[p] = data;
}

elem vectorGet(Vector *v, int p)
{
    if (p < 0 || p >= v->length)
        return withError(INCORRECT_PARAMS), (elem) 0;

    return v->arr[p];
}