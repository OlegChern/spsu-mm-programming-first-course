//
// Created by rinsl_000 on 10.11.2017.
//

#ifndef TEST_ARRAY_UTILS_H
#define TEST_ARRAY_UTILS_H

int filter(
        void **arr,
        size_t size,
        size_t *len,
        int (*condition)(const void *a),
        void (*free_elem)(void *a)
);

#endif //TEST_ARRAY_UTILS_H
