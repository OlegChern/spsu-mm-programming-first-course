//
// Created by rinsl_000 on 06.11.2017.
//

#include "../headers/hash_map.h"
#include "../headers/pair.h"


int init(Hash_map **map)
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

int put(Hash_map *hash_map, int v, char *k)
{
    Pair *p;
    if ((p = malloc(sizeof(Pair))) == NULL)
        return 0;

    p->v = v;
    p->k = k;

    if (hash_map == NULL)
        return 0;

    int hash = get_hash(p->k, hash_map->length);

    int r = put_to_list(&hash_map->h[hash], p);
    if (r)
        hash_map->size--;

    return r;
}

int get(Hash_map *hash_map, char *k, int *result)
{
    if (hash_map == NULL)
        return 0;

    int hash = get_hash(k, hash_map->length);

    return get_from_list(hash_map->h[hash], k, result);
}

int pop(Hash_map *hash_map, char *k, int *result)
{
    if (hash_map == NULL)
        return 0;

    int hash = get_hash(k, hash_map->length);

    int r = pop_from_list(&hash_map->h[hash], k, result);
    if (r)
        hash_map->size--;

    return r;
}

void print(Hash_map *hash_map)
{
    if (hash_map == NULL)
    {
        printf("<empty map>\n");
        return;
    }

    printf("[\n");
    for (int i = 0; i < hash_map->length; ++i) {
        if (hash_map->h[i] != NULL)
            print_list(hash_map->h[i]);

        if (i != hash_map->length - 1)
            printf(",\n");
    }
    printf("\n]\n");
}