//
// Created by rinsler on 25.10.17.
//

#ifndef TEST_1_STRUCTURES_LIST_H
#define TEST_1_STRUCTURES_LIST_H

#define PARTITION_SIZE 8

struct tagList {
    int arr[PARTITION_SIZE];
    int sz;
    struct tagList *next;
};

typedef struct tagList List;

//
// Created by rinsler on 25.10.17.
//

#include <stdlib.h>
#include <stdio.h>
#include "list.h"


void print_list(List *l);
int append(List **s, int v);
int at(List *l, int p, int *error);

#endif //TEST_1_STRUCTURES_LIST_H
