//
// Created by rinsler on 29.10.17.
//

#include "../headers/fractions.h"


void get_next_repr(int n, int sqrt_of_n, const int *prev, int *cur)
{
    cur[0] = prev[1] * prev[2] - prev[0];
    cur[1] = (n - (prev[0] - prev[1] * prev[2]) * (prev[0] - prev[1] * prev[2])) / prev[1];
    cur[2] = (sqrt_of_n + cur[0]) / cur[1];
}