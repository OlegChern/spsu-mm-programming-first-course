//
// Created by rinsl_000 on 06.11.2017.
//

#include <stdio.h>

#include "../headers/pair.h"

void print_pair(Pair *p)
{
    printf("    {%s: %d}", p->k, p->v);
}
