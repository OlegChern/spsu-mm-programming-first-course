//
// Created by rinsler on 29.10.17.
//

#include "../headers/fractions.h"


void get_next_repr(int n, int sqrt_of_n, const int *curr, int *next)
{
    next[0] = curr[1] * curr[2] - curr[0];
    next[1] = (n - (curr[0] - curr[1] * curr[2]) * (curr[0] - curr[1] * curr[2])) / curr[1];
    next[2] = (sqrt_of_n + next[0]) / next[1];
}