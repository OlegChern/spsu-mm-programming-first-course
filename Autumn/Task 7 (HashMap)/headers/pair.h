//
// Created by rinsl_000 on 06.11.2017.
//

#ifndef TEST_PAIR_H
#define TEST_PAIR_H

struct tagPair
{
    int v;
    char *k;
};

typedef struct tagPair Pair;

void print_pair(Pair *p);

#endif //TEST_PAIR_H
