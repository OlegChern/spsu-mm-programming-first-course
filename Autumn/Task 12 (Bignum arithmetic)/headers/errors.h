//
// Created by rinsl_000 on 24.11.2017.
//

#ifndef TASK_12_BIGNUM_ARITHMETIC_ERRORS_H
#define TASK_12_BIGNUM_ARITHMETIC_ERRORS_H

extern int error;

enum ERRORS_LIST {
    NOT_ENOUGH_MEMORY = 1,
    NULL_PTR = 2,
    INCORRECT_PARAMS = 3
};

void withError(int code);

#endif //TASK_12_BIGNUM_ARITHMETIC_ERRORS_H
