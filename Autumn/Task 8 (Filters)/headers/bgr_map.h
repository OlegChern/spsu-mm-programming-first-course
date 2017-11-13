//
// Created by rinsl_000 on 12.11.2017.
//

#ifndef TASK_8_INSTA_BITMAP_H
#define TASK_8_INSTA_BITMAP_H

#include "win_consts.h"


typedef struct tagBGRA
{
    byte blue;
    byte green;
    byte red;
    byte reserved;
} BGRA;

typedef struct tagBGR
{
    byte channels[3]; // Blue - Green - Red
} BGR;

typedef struct tagBGRMap
{
    BGR **map;
    int w;
    int h;
} BGRMap;

int initBGRMap(int h, int w, BGRMap *bgrMap);
int createBGRMap(int h, int w, BGRMap **bgrMap);
void copyMap(BGR **src, int ySrc, int xSrc, BGR **des, int yDes, int xDes, int h, int w);

#endif //TASK_8_INSTA_BITMAP_H
