//
// Created by rinsl_000 on 22.11.2017.
//

#ifndef TASK_12_BIGNUM_ARITHMETIC_VECTOR_H
#define TASK_12_BIGNUM_ARITHMETIC_VECTOR_H

typedef unsigned int elem;
#define MAX_ELEM_VALUE UINT_MAX

typedef struct tagVector {
    elem *arr;
    size_t length;
    size_t maxLength;
} Vector;

void vectorInit(Vector **v, size_t length);
void vectorAppend(Vector **v, elem x);
void vectorSet(Vector *v, int p, elem data);
elem vectorGet(Vector *v, int p);

#endif //TASK_12_BIGNUM_ARITHMETIC_VECTOR_H
