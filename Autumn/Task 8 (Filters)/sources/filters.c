//
// Created by rinsl_000 on 12.11.2017.
//

#include <stdlib.h>
#include <math.h>
#include "../headers/filters.h"
#include "../headers/bgr_map.h"
#include "../headers/win_consts.h"


typedef int (*pixelFunc)(BGRMap*, BGRMap*, int, int, int);

typedef struct tagFilter {
    int **map;
    int n;
    int alpha;
} Filter;

Filter Gaussian3x3Filter;
Filter Gaussian5x5Filter;
Filter SobelXFilter;
Filter SobelYFilter;
Filter ScharrXFilter;
Filter ScharrYFilter;

int initTable(int ***arr, int h, int w)
{
    if ((*arr = malloc(sizeof(**arr) * h)) == NULL)
        return 0;

    for (int i = 0; i < h; ++i) {
        if (((*arr)[i] = malloc(sizeof(***arr) * w)) == NULL)
            return 0;
    }

    return 1;
}

int initFilter(Filter *filter, int n, const int *table, int alpha)
{
    filter->n = n;
    if (!initTable(&filter->map, n, n))
        return 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            filter->map[i][j] = table[i * n + j];
    filter->alpha = alpha;

    return 1;
}

int initFilters()
{
    int gaussian3x3Table[3][3] = {
            {1, 2, 1},
            {2, 4, 2},
            {1, 2, 1}
    };
    if (!initFilter(&Gaussian3x3Filter, 3, (int *) gaussian3x3Table, 16))
        return 0;

    int gaussian5x5Table[5][5] = {
            {1, 4, 7, 4, 1},
            {4, 16, 26, 16, 4},
            {7, 26, 41, 26, 7},
            {4, 16, 26, 16, 4},
            {1, 4, 7, 4, 1}
    };
    if (!initFilter(&Gaussian5x5Filter, 5, (int *) gaussian5x5Table, 273))
        return 0;

    int sobelXTable[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
    };
    if (!initFilter(&SobelXFilter, 3, (int *) sobelXTable, 1))
        return 0;

    int sobelYTable[3][3] = {
            {-1, -2, -1},
            {0, 0, 0},
            {1, 2, 1}
    };
    if (!initFilter(&SobelYFilter, 3, (int *) sobelYTable, 1))
        return 0;

    int scharrXTable[3][3] = {
            {3, 0, -3},
            {10, 0, -10},
            {3, 0, -3}
    };
    if (!initFilter(&ScharrXFilter, 3, (int *) scharrXTable, 1))
        return 0;

    int scharrYTable[3][3] = {
            {3, 10, 3},
            {0, 0, 0},
            {-3, -10, -3}
    };
    if (!initFilter(&ScharrYFilter, 3, (int *) scharrYTable, 1))
        return 0;

    return 1;
}


int map(BGRMap *input, BGRMap *output, pixelFunc pf, int param)
{
    for (int i = 0; i < input->h; ++i)
        for (int j = 0; j < input->w; ++j)
            if (!pf(input, output, i, j, param))
                return 0;

    return 1;
}

int byteComparator(const void *a, const void *b)
{
    return *(byte*)a - *(byte*)b;
}

byte getAverage(BGRMap *map, int c)
{
    byte *tmp;
    size_t tmpLen = (size_t) (map->h * map->w);
    if ((tmp = malloc(tmpLen)) == NULL)
        exit(1);

    for (int i = 0; i < map->h; ++i)
        for (int j = 0; j < map->w; ++j)
            tmp[i * map->w + j] = map->map[i][j].channels[c];

    qsort(tmp, tmpLen, sizeof(*tmp), byteComparator);

    byte result = (byte) tmp[tmpLen / 2];

    free(tmp);
    return result;
}

int medianMap(BGRMap *input, BGRMap *output, int y, int x, int n)
{
    BGRMap *tmp = NULL;
    if (!createBGRMap(n, n, &tmp))
        return 0;

    if (y - n / 2 >= 0 && y + n / 2 < input->h && x - n / 2 >= 0 && x + n / 2 < input->w)
    {
        copyMap(input->map, y - n / 2, x - n / 2, tmp->map, 0, 0, n, n);
        for (int c = 0; c < 3; ++c)
            output->map[y][x].channels[c] = getAverage(tmp, c);
    }
    else
        output->map[y][x] = input->map[y][x];

    free(tmp);
    return 1;
}

byte clump(int v)
{
    if (v > 255)
        return 255;
    if (v < 0)
        return 0;

    return (byte) v;
}

int filterMap(BGRMap *src, BGRMap *des, int y, int x, Filter *filter)
{
    for (int c = 0; c < 3; ++c)
    {
        long long sum = 0;

        for (int i = y - filter->n / 2; i <= y + filter->n / 2; ++i)
            for (int j = x - filter->n / 2; j <= x + filter->n / 2; ++j)
                if (i >= 0 && i < src->h && j >= 0 && j < src->w)
                    sum += src->map[i][j].channels[c] *
                            filter->map[i - (y - filter->n / 2)][j - (x - filter->n / 2)];

        des->map[y][x].channels[c] = clump((int) round(sum * 1.0 / filter->alpha));
    }

    return 1;
}

int gaussianMap(BGRMap *src, BGRMap *des, int y, int x, int n)
{
    if (n != 3 && n != 5)
        return 0;

    Filter filter = n == 3 ? Gaussian3x3Filter : Gaussian5x5Filter;
    return filterMap(src, des, y, x, &filter);
}

int operatorMap(BGRMap *src, BGRMap *des, int y, int x, int variant)
{
    if (!(-3 <= variant && variant <= 3 && variant != 0))
        return 0;

    if (variant != 3 && variant != -3)
    {
        Filter *filter;
        switch (variant)
        {
            case 1:
                filter = &SobelXFilter;
                break;
            case 2:
                filter = &SobelYFilter;
                break;
            case -1:
                filter = &ScharrXFilter;
                break;
            case -2:
                filter = &ScharrYFilter;
                break;
            default:
                exit(1);
        }

        return filterMap(src, des, y, x, filter);
    }

    Filter *filterX, *filterY;
    if (variant == 3)
        filterX = &SobelXFilter, filterY = &SobelYFilter;
    else
        filterX = &ScharrXFilter, filterY = &ScharrYFilter;

    if (!filterMap(src, des, y, x, filterX))
        return 0;
    int xVal[3];
    for (int c = 0; c < 3; ++c)
        xVal[c] = des->map[y][x].channels[c];

    if (!filterMap(src, des, y, x, filterY))
        return 0;
    int yVal[3];
    for (int c = 0; c < 3; ++c)
        yVal[c] = des->map[y][x].channels[c];

    for (int c = 0; c < 3; ++c)
        des->map[y][x].channels[c] = clump((int) sqrt(xVal[c] * xVal[c] + yVal[c] * yVal[c]));

    return 1;
}



int whiteBlackMap(BGRMap *src, BGRMap *des, int y, int x, int unused)
{
    int res = 0;
    for (int c = 0; c < 3; ++c)
        res += src->map[y][x].channels[c];
    res /= 3;
    for (int c = 0; c < 3; ++c)
        des->map[y][x].channels[c] = (byte) res;

    return 1;
}

int applyFilter(BGRMap *input, BGRMap *output, enum Filter filter)
{
    initFilters();

    if (input == NULL)
        return 0;

    output->h = input->h;
    output->w = input->w;

    pixelFunc pf;
    int param;

    switch (filter)
    {
        case MEDIAN_3_X_3:
            pf = medianMap;
            param = 3;
            break;
        case MEDIAN_5_X_5:
            pf = medianMap;
            param = 5;
            break;
        case GAUSSIAN_3_X_3:
            pf = gaussianMap;
            param = 3;
            break;
        case GAUSSIAN_5_X_5:
            pf = gaussianMap;
            param = 5;
            break;
        case SOBEL_X:
            pf = operatorMap;
            param = 1;
            break;
        case SOBEL_Y:
            pf = operatorMap;
            param = 2;
            break;
        case SOBEL:
            pf = operatorMap;
            param = 3;
            break;
        case SCHARR_X:
            pf = operatorMap;
            param = -1;
            break;
        case SCHARR_Y:
            pf = operatorMap;
            param = -2;
            break;
        case SCHARR:
            pf = operatorMap;
            param = -3;
            break;
        case WHITE_BLACK_MODE:
            pf = whiteBlackMap;
            param = 0;
            break;
        default:
            exit(1);
    }

    return map(input, output, pf, param);
}