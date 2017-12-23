#ifndef EX8_BMP_H
#define EX8_BMP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint32_t LONG;

#pragma pack(1)

struct header
{
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
};

struct RGBTRIPLE
{
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
};

struct map
{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
};

#pragma pop()

int checkArguments(char *, int);

struct RGBTRIPLE **cpyArray(struct RGBTRIPLE **, struct map *);

int readFile(struct header *, struct map *, FILE *);

struct RGBTRIPLE **readArrayX24(int *, struct map *, FILE *);

struct RGBTRIPLE **readArrayX32(int *, struct map *, FILE *);

int writeFIleX24(struct RGBTRIPLE **, int *, struct header *, struct map *, char *, FILE *);

int writeFIleX32(struct RGBTRIPLE **, int *, struct header *, struct map *, char *, FILE *);

void applyFilter(char *, struct RGBTRIPLE **, struct RGBTRIPLE **, int, int);


void filterGrey(int, int, struct RGBTRIPLE **, struct RGBTRIPLE **);

void filterMedian(int, int, struct RGBTRIPLE **, struct RGBTRIPLE **);

void applyMedianToPixels(struct RGBTRIPLE **, struct RGBTRIPLE **, int, int);


void filterGauss3x3(int, int, struct RGBTRIPLE **, struct RGBTRIPLE **);

void applyGaussToPixels3x3(struct RGBTRIPLE **, struct RGBTRIPLE **, int, int);

void filterGauss5x5(int, int, struct RGBTRIPLE **, struct RGBTRIPLE **);

void applyGaussToPixels5x5(struct RGBTRIPLE **, struct RGBTRIPLE **, int, int);


void filterSobelX(int, int, struct RGBTRIPLE **, struct RGBTRIPLE **);

void applySobelXToPixels(struct RGBTRIPLE **, struct RGBTRIPLE **, int, int);

void filterSobelY(int, int, struct RGBTRIPLE **, struct RGBTRIPLE **);

void applySobelYToPixels(struct RGBTRIPLE **, struct RGBTRIPLE **, int, int);

void filterSobelXY(int, int, struct RGBTRIPLE **, struct RGBTRIPLE **);

void applySobelXYToPixels(struct RGBTRIPLE **, struct RGBTRIPLE **, int, int);


#endif //EX8_BMP_H
