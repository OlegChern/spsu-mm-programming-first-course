#include <stdio.h>
#include <stdlib.h>
#include "bmpprocessing.h"

BITMAPFILEHEADER header;
BITMAPINFOHEADER info;
DWORD width, height;
DWORD fileSize, imageStart, imageSize;
DWORD paletteSize;
WORD bitCount;

CHAR *palette = NULL, *pictureIn, *pictureOut;

char *methods[] = { "ToGray", "Filter3x3", "Gauss5x5" };
void(*functions[])() = { processToGray, processFilter3x3, processGauss5x5, methodError /*, processCopy */ };
int methodsCount = sizeof(methods) / sizeof(char*);

double simple3x3[] =
{
	1. / 9, 1. / 9, 1. / 9,
    1. / 9, 1. / 9, 1. / 9,
    1. / 9, 1. / 9, 1. / 9
};
double gauss5x5[] =
{
	0.003, 0.013, 0.022, 0.013, 0.003,
	0.013, 0.059, 0.097, 0.059, 0.013,
	0.022, 0.097, 0.159, 0.097, 0.022,
	0.013, 0.059, 0.097, 0.059, 0.013,
	0.003, 0.013, 0.022, 0.013, 0.003
};

void readInput(char *fileName)
{
	FILE *bmpIn = fopen(fileName, "rb");
	if (bmpIn == NULL)
	{
		printf("%s file not found\n", fileName);
		exit(2);
	}
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, bmpIn) == 0)
	{
		printf("Format error: %s\n", fileName);
		exit(1);
	}
	if ((header.bfType & 0xFF) != 'B' || (header.bfType >> 8) != 'M')
	{
		printf("Format error: %s\n", fileName);
		exit(1);
	}
	fread(&info, sizeof(BITMAPINFOHEADER), 1, bmpIn);

	fileSize = header.bfSize;
	width = info.biWidth;
	height = info.biHeight;
	imageStart = header.bfOffBits;
	imageSize = fileSize - imageStart;
	paletteSize = imageStart - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);
	bitCount = info.biBitCount;

	if (paletteSize)
	{
		palette = malloc(paletteSize);
		fread(palette, paletteSize, 1, bmpIn);
	}
	pictureIn = malloc(imageSize);
	pictureOut = calloc(imageSize, 1);
	fread(pictureIn, 1, imageSize, bmpIn);
	fclose(bmpIn);
}

void writeOutput(char *fileName)
{
	FILE *bmpOut = fopen(fileName, "wb");
	if (bmpOut == NULL)
	{
		printf("%s file cannot be created\n", fileName);
		exit(2);
	}
	fwrite(&header, sizeof(BITMAPFILEHEADER), 1, bmpOut);
	fwrite(&info, sizeof(BITMAPINFOHEADER), 1, bmpOut);
	if (paletteSize)
	{
		fwrite(palette, paletteSize, 1, bmpOut);
	}
	fwrite(pictureOut, 1, imageSize, bmpOut);
	fclose(bmpOut);
}

int checkMethod(char *method)
{
	int methodIndex;
	for (methodIndex = 0; methodIndex < methodsCount; methodIndex++)
	{
		if (strcmp(method, methods[methodIndex]) == 0)
		{
			return methodIndex;
		}
	}
	return methodsCount;
}

void callMethod(char *method)
{
	functions[checkMethod(method)]();
}

void process(char *method)
{
	if (strcmp(method, "xxx") == 0)
	{

	}
	else if (strcmp(method, "yyy") == 0)
	{

	}
	else // just copy
	{
		processCopy();
	}
}

void getPixel(CHAR *pic, int x, int y, RGBTRIPLE *triple)
{
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x >= height) x = height - 1;
	if (y >= width) y = width - 1;
	int rowLength = bitCount == 24 ? 3 * width + width % 4 : 4 * width;
	CHAR *rowStart = pic + (height - 1 - x)*rowLength;
	memcpy(triple, rowStart + y*(bitCount / 8), 3);
}

void setPixel(CHAR *pic, int x, int y, RGBTRIPLE *triple)
{
	int rowLength = bitCount == 24 ? 3 * width + width % 4 : 4 * width;
	CHAR *rowStart = pic + (height - 1 - x)*rowLength;
	memcpy(rowStart + y*(bitCount / 8), triple, 3);
}

// Functions to process bmp image contents

void processToGray()
{
	RGBTRIPLE triple;
	int x, y;
	for (x = 0; x < height; x++)
		for (y = 0; y < width; y++)
		{
			getPixel(pictureIn, x, y, &triple);
			int color = (triple.rgbtRed * 30 + triple.rgbtGreen * 59 + triple.rgbtBlue * 11) / 100;
			triple.rgbtBlue = triple.rgbtGreen = triple.rgbtRed = color & 0xFF;
			setPixel(pictureOut, x, y, &triple);
		}
}

void filterWithMatrix(double *matrix, int n)
{
	int x, y, i, j, nHalf = n / 2;
	for (x = 0; x < height; x++)
		for (y = 0; y < width; y++)
		{
			RGBTRIPLE resPixel;
			resPixel.rgbtBlue = resPixel.rgbtGreen = resPixel.rgbtRed = 0;
			for (i = -nHalf; i <= nHalf; i++)
				for (j = -nHalf; j <= nHalf; j++)
				{
					RGBTRIPLE triple;
					getPixel(pictureIn, x + i, y + j, &triple);
					resPixel.rgbtRed += triple.rgbtRed * matrix[(i + nHalf)*n + j + nHalf];
					resPixel.rgbtGreen += triple.rgbtGreen * matrix[(i + nHalf)*n + j + nHalf];
					resPixel.rgbtBlue += triple.rgbtBlue * matrix[(i + nHalf)*n + j + nHalf];
				}
			setPixel(pictureOut, x, y, &resPixel);
		}
}

void processFilter3x3()
{
	filterWithMatrix(simple3x3, 3);
}

void processGauss5x5()
{
	filterWithMatrix(gauss5x5, 5);
}

void processCopy()
{
	memcpy(pictureOut, pictureIn, imageSize);
}

void methodError()
{
	printf("Wrong method name\n");
	exit(3);
}
