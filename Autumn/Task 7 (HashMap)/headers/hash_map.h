//
// Created by rinsl_000 on 06.11.2017.
//

#ifndef TEST_HASH_MAP_H
#define TEST_HASH_MAP_H

#include "list.h"

struct tagHash_map
{
    List** h;
    int size;
    int length;
};

typedef struct tagHash_map Hash_map;

int init(Hash_map **map);
int put(Hash_map *hash_map, int v, char *k);
int get(Hash_map *hash_map, char *k, int *result);
int pop(Hash_map *hash_map, char *k, int *result);

void print(Hash_map *hash_map);

#endif //TEST_HASH_MAP_H
