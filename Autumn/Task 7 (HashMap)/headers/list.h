//
// Created by rinsler on 25.10.17.
//

#ifndef TEST_1_STRUCTURES_LIST_H
#define TEST_1_STRUCTURES_LIST_H

#include <stdlib.h>
#include <stdio.h>

#include "pair.h"

struct tagList {
    Pair *p;
    struct tagList *next;
};

typedef struct tagList List;

int put_in_list(List **head, Pair *p);
int get_from_list(List *l, char *s, int *result);
int pop_from_list(List **head, char *s, int *result);
void free_list(List **head);
void print_list(List *l);

#endif //TEST_1_STRUCTURES_LIST_H
