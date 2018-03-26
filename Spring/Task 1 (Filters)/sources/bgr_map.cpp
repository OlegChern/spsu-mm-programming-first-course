//
// Created by rinsl_000 on 12.11.2017.
//

#include <cstdlib>
#include "../headers/bgr_map.h"


int initBGRMap(int h, int w, BGRMap *bgrMap)
{
    if (bgrMap == nullptr)
        return 0;

    bgrMap->w = w;
    bgrMap->h = h;

    if ((bgrMap->map = static_cast<BGR **>(malloc(sizeof(BGR *) * h))) == nullptr)
        return 0;

    for (int i = 0; i < bgrMap->h; ++i)
        if ((bgrMap->map[i] = static_cast<BGR *>(malloc(sizeof(BGR) * w))) == nullptr)
            return 0;

    return 1;
}

int createBGRMap(int h, int w, BGRMap **bgrMap)
{
    if ((*bgrMap = static_cast<BGRMap *>(malloc(sizeof(BGRMap)))) == nullptr)
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