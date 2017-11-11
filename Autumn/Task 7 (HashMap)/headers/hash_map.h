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

int init_map(Hash_map **map, int len);
int put_in_map(Hash_map **map, char *k, int v);
int get_from_map(Hash_map *map, char *k, int *result);
int pop_from_map(Hash_map *map, char *k, int *result);
void free_map(Hash_map **map);
void print_map(Hash_map *map);

#endif //TEST_HASH_MAP_H
