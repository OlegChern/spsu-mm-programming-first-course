//
// Created by rinsl_000 on 12.11.2017.
//

#ifndef TASK_8_INSTA_FILTERS_C_H
#define TASK_8_INSTA_FILTERS_C_H

#include <cstdio>
#include "bgr_map.h"

enum Filter {
    MEDIAN_3_X_3,
    MEDIAN_5_X_5,
    GAUSSIAN_3_X_3,
    GAUSSIAN_5_X_5,
    SOBEL,
    SOBEL_X,
    SOBEL_Y,
    SCHARR,
    SCHARR_X,
    SCHARR_Y,
    WHITE_BLACK_MODE
};

int applyFilter(BGRMap *input, BGRMap *output, Filter filter);

#endif //TASK_8_INSTA_FILTERS_C_H
