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

PIXEL  *pixelNew(UBYTE, UBYTE, UBYTE);
PIXEL *pixelNewSame(UBYTE);
UBYTE pixelGrayscaled(PIXEL);
UBYTE clampToUByte(short);

void gauss3x3(int, int, float**, PIXEL**);
void sobel(int, int, char[3][3], PIXEL**);
void grayscale(int, int, PIXEL**);
void average3x3(int, int, PIXEL**);

void closeFiles(FILE*, FILE*);

PIXEL *pixelNew(UBYTE r, UBYTE g, UBYTE b)
{
	PIXEL* p = (PIXEL*)malloc(sizeof(PIXEL));
	p->red = r;
	p->green = g;
	p->blue = b;
	return p;
}

PIXEL *pixelNewSame(UBYTE v)
{
	PIXEL* p = (PIXEL*)malloc(sizeof(PIXEL));
	p->red = v;
	p->green = v;
	p->blue = v;
	return p;
}

UBYTE pixelGrayscaled(PIXEL p)
{
	return (UBYTE)((p.blue + p.green + p.red) / 3);
}

UBYTE clampToUByte(short value)
{
	UBYTE clamped =
		value < 0 ? 0 : 
		value > 255 ? 255 : 
		(UBYTE)value;

	return clamped;
}

UBYTE roundUBYTE(float f)
{
	UBYTE rounded = 
		f - (float)((int)f) >= 0.5f ? (int)f + 1 : 
		(int)f;

	return rounded;
}

void gauss3x3(int width, int height, float **kernel, PIXEL **newImage)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			float sum = 0;
			float r = 0, g = 0, b = 0;

			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (x + i >= 0 && x + i < width && y + j >= 0 && y + j < height)
					{
						PIXEL pix = newImage[x + i][y + j];

						r += pix.red * kernel[i + 1][j + 1];
						g += pix.green * kernel[i + 1][j + 1];
						b += pix.blue * kernel[i + 1][j + 1];

						sum += kernel[i + 1][j + 1];
					}
				}
			}

			if (sum != 0)
			{
				newImage[x][y].red = roundUBYTE(r / sum);
				newImage[x][y].green = roundUBYTE(g / sum);
				newImage[x][y].blue = roundUBYTE(b / sum);
			}
		}
	}
}

void sobel(int width, int height, char mask[3][3], PIXEL **newImage)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			short sum = 0;

			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (x + i >= 0 && x + i < width && y + j >= 0 && y + j < height)
					{
						UBYTE cur = pixelGrayscaled(newImage[x + i][y + j]);
						sum += cur * mask[i + 1][j + 1];
					}
				}
			}

			UBYTE clamped = clampToUByte(sum);
			newImage[x][y] = *(pixelNewSame(clamped));
		}
	}
}

void grayscale(int width, int height, PIXEL **newImage)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			UBYTE grayscale = pixelGrayscaled(newImage[x][y]);
			newImage[x][y] = *(pixelNewSame(grayscale));
		}
	}
}

void average3x3(int width, int height, PIXEL **newImage)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			USHORT r = 0, g = 0, b = 0; // USHORT used, because 255*9 > 255
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (x + i >= 0 && x + i < width && y + j >= 0 && y + j < height)
					{
						r += newImage[x + i][y + j].red;
						g += newImage[x + i][y + j].green;
						b += newImage[x + i][y + j].blue;
					}
				}
			}
			newImage[x][y] = *(pixelNew(r / 9, g / 9, b / 9));
		}
	}
}

void closeFiles(FILE *file1, FILE *file2)
{
	fclose(file1);
	fclose(file2);
}