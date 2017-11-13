//
// Created by rinsl_000 on 12.11.2017.
//

#include <stdio.h>
#include "../headers/bmp.h"
#include "../headers/bgr_map.h"


size_t readPixel24Bit(FILE *file, BGR *pixel)
{
    return fread(pixel, sizeof(BGR), 1, file);
}

size_t readPixel32Bit(FILE *file, BGR *pixel)
{
    size_t res = fread(pixel, sizeof(BGR), 1, file);
    res += fread(NULL, sizeof(byte), 1, file);

    return res;
}

size_t writePixel24Bit(FILE *file, BGR *pixel)
{
    return fwrite(pixel, sizeof(BGR), 1, file);
}

size_t writePixel32Bit(FILE *file, BGR *pixel)
{
    size_t res = fwrite(pixel, sizeof(BGR), 1, file);
    byte tmp = 0;
    res += fwrite(&tmp, sizeof(byte), 1, file);

    return res;
}