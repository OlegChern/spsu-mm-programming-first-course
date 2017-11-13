//
// Created by rinsl_000 on 12.11.2017.
//

#include <stdlib.h>
#include "../headers/bgr_map.h"


int initBGRMap(int h, int w, BGRMap *bgrMap)
{
    if (bgrMap == NULL)
        return 0;

    bgrMap->w = w;
    bgrMap->h = h;

    if ((bgrMap->map = malloc(sizeof(BGR *) * h)) == NULL)
        return 0;

    for (int i = 0; i < bgrMap->h; ++i)
        if ((bgrMap->map[i] = malloc(sizeof(BGR) * w)) == NULL)
            return 0;

    return 1;
}

int createBGRMap(int h, int w, BGRMap **bgrMap)
{
    if ((*bgrMap = malloc(sizeof(BGRMap))) == NULL)
        return 0;

    initBGRMap(w, h, *bgrMap);

    return 1;
}

void copyMap(BGR **src, int ySrc, int xSrc, BGR **des, int yDes, int xDes, int h, int w)
{
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            des[yDes + i][xDes + j] = src[ySrc + i][xSrc + j];
        }
    }
}