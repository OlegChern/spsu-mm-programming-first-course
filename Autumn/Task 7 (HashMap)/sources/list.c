//
// Created by rinsler on 25.10.17.
//

#include <stdlib.h>
#include <string.h>

#include "../headers/list.h"
#include "../headers/pair.h"


int put_in_list(List **head, Pair *p)
{
    if (*head == NULL)
    {
        if ((*head = malloc(sizeof(List))) == NULL)
            return 0;

        (*head)->p = p;
        (*head)->next = NULL;

        return 1;
    }

    List *l = *head;

    if (strcmp(l->p->k, p->k) == 0)
    {
        l->p->v = p->v;
        return 1;
    }

    while (l->next != NULL)
    {
        if (strcmp(l->p->k, p->k) == 0)
        {
            l->p->v = p->v;
            return 1;
        }

        l = l->next;
    }

    if ((l->next = malloc(sizeof(List))) == NULL)
        return 0;

    l = l->next;
    l->p = p;
    l->next = NULL;

    return 1;
}

int get_from_list(List *l, char *s, int *result)
{
    if (l == NULL)
        return 0;

    while (l != NULL)
    {
        if (strcmp(l->p->k, s) == 0)
        {
            *result = l->p->v;
            return 1;
        }

        l = l->next;
    }

    return 0;
}

int pop_from_list(List **head, char *s, int *result)
{
    if (*head == NULL)
        return 0;

    if (strcmp((*head)->p->k, s) == 0)
    {
        List *tmp = *head;
        *head = (*head)->next;
        *result = tmp->p->v;
        free(tmp);

        return 1;
    }

    List *l = *head;

    while (l->next != NULL)
    {
        if (strcmp(l->next->p->k, s) == 0)
        {
            List *tmp = l->next;
            l->next = l->next->next;
            *result = tmp->p->v;
            free(tmp);

            return 1;
        }

        l = l->next;
    }

    return 0;
}

void print_list(List *l)
{
    if (l == NULL)
        printf("<empty list>");
    else
    {
        while (l != NULL)
        {
            printf("    ");
            print_pair(l->p);
            if (l->next != NULL)
                printf(",\n");

            l = l->next;
        }
    }
}
