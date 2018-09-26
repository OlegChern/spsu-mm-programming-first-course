#include "stdafx.h"
#include "BMP.h"
using namespace std;


BMP::BMP(string inFileName)
{
	FILE *fin;
	fopen_s(&fin, inFileName.c_str(), "rb");
	if (fin == NULL)
	{
		printf("Error! Incorrect name of input file");
		exit(0);
	}

	if (!fin)
	{
		cout << "No such file!!\n";
	}

	//bitmapFileHeader = malloc(sizeof(BITMAPFILEHEADER));
	//BITMAPINFOHEADER *bitmapInfoHeader = malloc(sizeof(BITMAPINFOHEADER));
	bitmapFileHeader = new BITMAPFILEHEADER;
	bitmapInfoHeader = new BITMAPINFOHEADER;
	fread(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fin);
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fin);

	if ((bitmapInfoHeader->biBitCount != 24) && (bitmapInfoHeader->biBitCount != 32))
	{
		cout << "Wrong format!!!\n";
		exit(0);
	}

	rgb = new RGB*[bitmapInfoHeader->biHeight];
	for (int i = 0; i < bitmapInfoHeader->biHeight; i++)
	{
		rgb[i] = new RGB[bitmapInfoHeader->biWidth];
	}

	paletteSize = bitmapFileHeader->bfOffBits - (int)sizeof(BITMAPFILEHEADER) - (int)sizeof(BITMAPINFOHEADER);

	if (paletteSize > 0)
	{
		palette = (char*)malloc(paletteSize);
		fread(palette, paletteSize, 1, fin);
	}

	linePadding = (4 - (bitmapInfoHeader->biWidth * (bitmapInfoHeader->biBitCount / 8)) % 4) & 3;
	char c = 0;
	for (int i = 0; i < bitmapInfoHeader->biHeight; i++)
	{
		for (int j = 0; j < bitmapInfoHeader->biWidth; j++)
		{
			rgb[i][j].rgbBlue = (unsigned char)getc(fin);
			rgb[i][j].rgbGreen = (unsigned char)getc(fin);
			rgb[i][j].rgbRed = (unsigned char)getc(fin);

			//printf("%d %d %d\n", rgb[i][j].rgbBlue, rgb[i][j].rgbGreen, rgb[i][j].rgbRed);

			if (bitmapInfoHeader->biBitCount == 32)
			{
				getc(fin);
			}
		}
		for (int k = 0; k < linePadding; k++)
		{
			getc(fin);
		}
	}
}

void BMP::writeBMP(string outFileName)
{
	FILE *fout;
	fopen_s(&fout, outFileName.c_str(), "wb");
	if (fout == NULL)
	{
		printf("Error! Incorrect name of output file");
		fclose(fout);
		exit(0);
	}	

	fwrite(bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fout);
	fwrite(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fout);

	if (paletteSize > 0)
	{
		fwrite(palette, paletteSize, 1, fout);
	}
	char c = 0;

	//cout << bitmapInfoHeader->biHeight << " " << bitmapInfoHeader->biWidth << "\n";
	for (int i = 0; i < bitmapInfoHeader->biHeight; i++)
	{
		for (int j = 0; j < bitmapInfoHeader->biWidth; j++)
		{
			fwrite(&rgb[i][j], sizeof(RGB), 1, fout);
			//printf("%d %d %d\n", rgb[i][j].rgbBlue, rgb[i][j].rgbGreen, rgb[i][j].rgbRed);

			if (bitmapInfoHeader->biBitCount == 32)
			{
				putc(0, fout);
			}
		}
		for (int k = 0; k < linePadding; k++)
		{
			putc(0, fout);
		}
	}
	fclose(fout);
}

void BMP::useFilter(Filter& filter)
{
	RGB** oldrgb = rgb;
	rgb = filter.run(rgb, bitmapInfoHeader->biWidth, bitmapInfoHeader->biHeight);
	for (int i = 0; i < bitmapInfoHeader->biHeight; i++)
	{
		delete[] oldrgb[i];
	}
	delete[] oldrgb;
}

BMP::~BMP()
{
}
