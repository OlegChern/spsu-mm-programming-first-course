#pragma once

#include <stdlib.h>

#define PI 3.14159
#define FALSE 1
#define TRUE 1
#define CHUNK 8

typedef unsigned char UBYTE;
typedef unsigned short USHORT;
typedef unsigned long ULONG;
typedef long LONG;

#pragma pack(1)
typedef struct
{
	USHORT bfType;
	ULONG bfSize;
	USHORT bfReserved1;
	USHORT bfReserved2;
	ULONG bfOffBits;
} BITMAPFILEHEADER;
#pragma pack()

#pragma pack(1)
typedef struct
{
	ULONG biSize;
	LONG biWidth;
	LONG biHeight;
	USHORT biPlanes;
	USHORT biBitCount;
	ULONG biCompression;
	ULONG biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	ULONG biClrUsed;
	ULONG biClrImportant;
} BITMAPINFOHEADER;
#pragma pack()

typedef struct
{
	UBYTE red;
	UBYTE green;
	UBYTE blue;
} PIXEL;

int		createImage(int, int, PIXEL**);
void	closeImage(int, PIXEL**);

PIXEL	*pixelNew(UBYTE, UBYTE, UBYTE);
PIXEL	*pixelNewSame(UBYTE);
UBYTE	pixelGrayscaled(PIXEL);
UBYTE	clampToUByte(short);

int		gauss3x3(int, int, float**, PIXEL**);
int		sobel(int, int, char[3][3], PIXEL**);
int		grayscale(int, int, PIXEL**);
int		average3x3(int, int, PIXEL**);

int		compare(const char*, const char*);
void	closeFiles(int, ...);