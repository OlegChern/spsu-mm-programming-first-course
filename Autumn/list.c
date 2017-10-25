//
// Created by rinsler on 25.10.17.
//

#include <stdlib.h>
#include <stdio.h>
#include "list.h"


void print_list(List *l)
{
    if (l == NULL)
        printf("<empty list>");
    else
    {
        printf("[");
        while (l != NULL)
        {
            for (int i = 0; i < l->sz; i++)
            {
                printf("%d", l->arr[i]);
                printf(i == l->sz + 1 && l->next == NULL ? "" : ", ");
            }

            l = l->next;
        }
        printf("]");
    }
}

int append(List **s, int v)
{
    if (*s == NULL)
    {
        if ((*s = malloc(sizeof(List))) == NULL)
            return -1;

        (*s)->arr[0] = v;
        (*s)->sz = 1;
        (*s)->next = NULL;

        return 0;
    }

    List *l = *s;

    while (l->sz == PARTITION_SIZE && l->next != NULL)
        l = l->next;

    if (l->sz == PARTITION_SIZE && l->next == NULL)
    {
        if ((l->next = malloc(sizeof(List))) == NULL)
            return -1;

        l = l->next;
        l->sz = 0;
    }

    l->arr[l->sz] = v;
    l->sz++;

    return 0;
}


int at(List *l, int p, int *error)
{
    if (l == NULL || p < 0)
    {
        *error = 1;
        return 0;
    }

    while (l->sz <= p && l->next != NULL)
    {
        p -= l->sz; // l->sz <=> PARTITION_SIZE
        l = l->next;
    }

    if (l->sz <= p && l->next == NULL)
    {
        *error = 1;
        return 0;
    }

    return l->arr[p];
}