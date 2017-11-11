//
// Created by rinsl_000 on 06.11.2017.
//

#include "../headers/list.h"
#include "../headers/hash_map.h"

#include "../headers/pair.h"


int init_map(Hash_map **map)
{
    if (*map == NULL)
    {
        if ((map = malloc(sizeof(Hash_map))) == NULL)
            return 0;

        (*map)->length = 16;
        (*map)->size = 0;
        if (((*map)->h = malloc((*map)->length * sizeof(List*))) == NULL)
            return 0;

        for (int i = 0; i < (*map)->length; ++i)
            (*map)->h[i] = NULL;

        return 1;
    }

    return 0;
}

static int get_hash(char *s, int mod)
{
    const int P = 177;
    const int Q = 1000000007;

    long hash = 0;
    for (; *s != '\0'; s++)
        hash = (hash * P % Q + *s) % Q;

    if (hash < 0)
        hash += Q;

    return (int) hash % mod;
}

int put_in_map(Hash_map *map, int v, char *k)
{
    Pair *p;
    if ((p = malloc(sizeof(Pair))) == NULL)
        return 0;

    p->v = v;
    p->k = k;

    if (map == NULL)
        return 0;

    int hash = get_hash(p->k, map->length);

    int r = put_in_list(&map->h[hash], p);
    if (r)
        map->size--;

    return r;
}

int get_from_map(Hash_map *map, char *k, int *result)
{
    if (map == NULL)
        return 0;

    int hash = get_hash(k, map->length);

    return get_from_list(map->h[hash], k, result);
}

int pop_from_map(Hash_map *map, char *k, int *result)
{
    if (map == NULL)
        return 0;

    int hash = get_hash(k, map->length);

    int r = pop_from_list(&map->h[hash], k, result);
    if (r)
        map->size--;

    return r;
}

void print_map(Hash_map *map)
{
    if (map == NULL)
    {
        printf("<empty map>\n");
        return;
    }

    printf("[\n");
    for (int i = 0; i < map->length; ++i) {
        if (map->h[i] != NULL)
            print_list(map->h[i]);

        if (i != map->length - 1)
            printf(",\n");
    }
    printf("\n]\n");
}

void free_map(Hash_map *map)
{
    for (int i = 0; i < map->length; ++i)
        free_list(&map->h[i]);

    free(map);
}