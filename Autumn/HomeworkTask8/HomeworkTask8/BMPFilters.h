#pragma once

typedef unsigned char UBYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

#pragma pack(1)
typedef struct
{
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER;
#pragma pack()

#pragma pack(1)
typedef struct
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
} BITMAPINFOHEADER;
#pragma pack()

typedef struct
{
	UBYTE red;
	UBYTE green;
	UBYTE blue;
} PIXEL;

PIXEL* pixelNew(UBYTE, UBYTE, UBYTE);
PIXEL* pixelNewSame(UBYTE);
UBYTE* pixelGrayscaled(PIXEL);
//void pixelMultiply(PIXEL*, UBYTE);
void clampToByte(short*);