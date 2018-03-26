//
// Created by rinsl_000 on 12.11.2017.
//

#ifndef TASK_8_INSTA_BMP_C_H
#define TASK_8_INSTA_BMP_C_H

#include "win_consts.h"
#include "bgr_map.h"


#pragma pack(2)
typedef struct tagBitMapFileHeader
{
    word    bfType;
    dword   bfSize;
    word    bfReserved1;
    word    bfReserved2;
    dword   bfOffBits;
} BitMapFileHeader;

#pragma pack(2)
typedef struct tagBitMapInfoHeader
{
    dword   biSize;
    slong   biWidth;
    slong   biHeight;
    word    biPlanes;
    word    biBitCount;
    dword   biCompression;
    dword   biSizeImage;
    slong   biXPelsPerMeter;
    slong   biYPelsPerMeter;
    dword   biClrUsed;
    dword   biClrImportant;
} BitMapInfoHeader;

typedef size_t (*forwardPixel) (FILE *, BGR *);

size_t readPixel24Bit(FILE *file, BGR *pixel);
size_t readPixel32Bit(FILE *file, BGR *pixel);
size_t writePixel24Bit(FILE *file, BGR *pixel);
size_t writePixel32Bit(FILE *file, BGR *pixel);

#endif //TASK_8_INSTA_BMP_C_H
