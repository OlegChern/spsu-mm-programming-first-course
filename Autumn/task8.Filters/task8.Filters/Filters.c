#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "Filters.h"

typedef struct
{
	unsigned char rgbBlue;
	unsigned char rgbGreen;
	unsigned char rgbRed;
} RGB;


RGB **input(BITMAPFILEHEADER *fileHeader, BITMAPINFOHEADER *info, FILE *file, int *linePadding, char **palette, unsigned long *paletteSize)
{
	fread(fileHeader, sizeof(BITMAPFILEHEADER), 1, file);
	fread(info, sizeof(BITMAPINFOHEADER), 1, file);

	if (info->biBitCount != 24 && info->biBitCount != 32)
	{
		return NULL;
	}
	
	unsigned long imageStart = fileHeader->bfOffBits;
	*paletteSize = imageStart - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);
	if (*paletteSize)
	{
		*palette = malloc(paletteSize);
		fread(*palette, *paletteSize, 1, file);
	}
	
	RGB **rgb = calloc(sizeof(RGB *), info->biHeight);
	for (int i = 0; i < info->biHeight; i++)
	{
		rgb[i] = calloc(sizeof(RGB *), info->biWidth);
	}
	
	*linePadding = (4 - (info->biWidth * (info->biBitCount / 8)) % 4) & 3;
	
	for (int i = 0; i < info->biHeight; i++)
	{
		for (int j = 0; j < info->biWidth; j++)
		{
			rgb[i][j].rgbBlue = (unsigned char)getc(file);
			rgb[i][j].rgbGreen = (unsigned char)getc(file);
			rgb[i][j].rgbRed = (unsigned char)getc(file);
			if (info->biBitCount == 32)
			{
				getc(file);
			}
		}
		for (int k = 0; k < *linePadding; k++)
		{
			getc(file);
		}
	}

	fclose(file);
	return rgb;
}

void output(RGB **rgb, int linePadding, BITMAPFILEHEADER *fileHeader, BITMAPINFOHEADER *info, FILE *file, char palette, unsigned long paletteSize)
{
	fwrite(fileHeader, sizeof(BITMAPFILEHEADER), 1, file);
	fwrite(info, sizeof(BITMAPINFOHEADER), 1, file);

	if (paletteSize)
	{
		fwrite(palette, paletteSize, 1, file);
	}
	
	for (int i = 0; i < info->biHeight; i++)
	{
		for (int j = 0; j < info->biWidth; j++)
		{
			fwrite(&rgb[i][j], sizeof(RGB), 1, file);
			if (info->biBitCount == 32)
			{
				putc(0, file);
			}
		}

		for (int k = 0; k < linePadding; k++)
		{
			fputc(0, file);
		}
	}

	fclose(file);
}

RGB **copyRGB(RGB **rgb, int row, int column)
{
	RGB **newRgb = calloc(sizeof(RGB *), row);
	for (int i = 0; i < row; i++)
	{
		newRgb[i] = calloc(sizeof(RGB *), column);
		memcpy(newRgb[i], rgb[i], sizeof(RGB) * column);
	}
	
	return newRgb;
}

void greyFilter(RGB **rgb, int row, int column)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			char newColor = (rgb[i][j].rgbBlue + rgb[i][j].rgbRed + rgb[i][j].rgbGreen) / 3;
			rgb[i][j].rgbBlue = newColor;
			rgb[i][j].rgbRed = newColor;
			rgb[i][j].rgbGreen = newColor;
		}
	}
}

void gaussFilter(RGB **rgb, int row, int column, RGB **result)
{
	int matrix[3][3] = { { 1, 2, 1 },{ 2, 4, 2 },{ 1, 2, 1 } };

	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < column - 1; j++)
		{
			int red = 0;
			int blue = 0;
			int green = 0;
			for (int k = 0; k < 3; k++)
			{
				for (int m = 0; m < 3; m++)
				{
					red += rgb[i + k - 1][j + m - 1].rgbRed * matrix[k][m];
					green += rgb[i + k - 1][j + m - 1].rgbGreen * matrix[k][m];
					blue += rgb[i + k - 1][j + m - 1].rgbBlue * matrix[k][m];
				}
			}
			
			result[i][j].rgbRed = (unsigned char)(red / 16);
			result[i][j].rgbGreen = (unsigned char)(green / 16);
			result[i][j].rgbBlue = (unsigned char)(blue / 16);
		}
	}
}

void averageFilter(RGB **rgb, int row, int column, RGB **result)
{
	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < column - 1; j++)
		{
			int red = 0;
			int blue = 0;
			int green = 0;
			for (int k = -1; k < 2; k++)
			{
				for (int m = -1; m < 2; m++)
				{
					red += rgb[i + k][j + m].rgbRed;
					green += rgb[i + k][j + m].rgbGreen;
					blue += rgb[i + k][j + m].rgbBlue;
				}
			}
			
			result[i][j].rgbRed = (unsigned char)(red / 9);
			result[i][j].rgbGreen = (unsigned char)(green / 9);
			result[i][j].rgbBlue = (unsigned char)(blue / 9);
		}
	}
}

void sobel(RGB **rgb, int row, int column, RGB **result, int matrix[3][3])
{
	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < column - 1; j++)
		{
			int red = 0;
			int blue = 0;
			int green = 0;
			
			for (int k = 0; k < 3; k++)
			{
				for (int m = 0; m < 3; m++)
				{
					red += rgb[i + k - 1][j + m - 1].rgbRed * matrix[k][m];
					green += rgb[i + k - 1][j + m - 1].rgbGreen * matrix[k][m];
					blue += rgb[i + k - 1][j + m - 1].rgbBlue * matrix[k][m];
				}
			}
			
			result[i][j].rgbRed = (unsigned char)red;
			result[i][j].rgbGreen = (unsigned char)green;
			result[i][j].rgbBlue = (unsigned char)blue;
		}
	}
}

void sobelFilterX(RGB **rgb, int row, int column, RGB **result)
{
	int matrix[3][3] = { { -1, 0, 1 },{ -2, 0, 2 },{ -1, 0, 1 } };
	sobel(rgb, row, column, result, matrix);
}

void sobelFilterY(RGB **rgb, int row, int column, RGB **result)
{
	int matrix[3][3] = { { -1, -2, -1 },{ 0, 0, 0 },{ 1, 2, 1 } };
	sobel(rgb, row, column, result, matrix);
}

void endOfFilters(RGB ***rgb, int linePadding, BITMAPFILEHEADER **fileHeader, BITMAPINFOHEADER **info, char palette, unsigned long paletteSize, FILE *finalFile)
{
	output(*rgb, linePadding, *fileHeader, *info, finalFile, palette, paletteSize);
	free(*fileHeader);
	free(*info);
	free(*rgb);
}

int applyFilter(FILE *startFile, int filter, FILE *finalFile)
{
	BITMAPFILEHEADER *fileHeader = malloc(sizeof(BITMAPFILEHEADER));
	BITMAPINFOHEADER *info = malloc(sizeof(BITMAPINFOHEADER));
	
	int linePadding;
	char *palette;
	unsigned long paletteSize;
	
	RGB **rgb = input(fileHeader, info, startFile, &linePadding, &palette, &paletteSize);
	if (rgb == NULL)
	{
		return 0;
	}
	
	switch (filter)
	{
	case 1:
	{
		RGB **newRGB = copyRGB(rgb, info->biHeight, info->biWidth);
		averageFilter(rgb, info->biHeight, info->biWidth, newRGB);
		free(rgb);
		rgb = newRGB;
		endOfFilters(&rgb, linePadding, &fileHeader, &info, palette, paletteSize, finalFile);
		return 1;
	}
	case 2:
	{
		RGB **newRGB = copyRGB(rgb, info->biHeight, info->biWidth);
		gaussFilter(rgb, info->biHeight, info->biWidth, newRGB);
		free(rgb);
		rgb = newRGB;
		endOfFilters(&rgb, linePadding, &fileHeader, &info, palette, paletteSize, finalFile);
		return 1;
	}
	case 3:
	{
		RGB **newRGB = copyRGB(rgb, info->biHeight, info->biWidth);
		sobelFilterX(rgb, info->biHeight, info->biWidth, newRGB);
		free(rgb);
		rgb = newRGB;
		endOfFilters(&rgb, linePadding, &fileHeader, &info, palette, paletteSize, finalFile);
		return 1;
	}
	case 4:
	{
		RGB **newRGB = copyRGB(rgb, info->biHeight, info->biWidth);
		sobelFilterY(rgb, info->biHeight, info->biWidth, newRGB);
		free(rgb);
		rgb = newRGB;
		endOfFilters(&rgb, linePadding, &fileHeader, &info, palette, paletteSize, finalFile);
		return 1;
	}
	case 5:
	{
		greyFilter(rgb, info->biHeight, info->biWidth);
		endOfFilters(&rgb, linePadding, &fileHeader, &info, palette, paletteSize, finalFile);
		return 1;
	}
	default:
	{
		free(fileHeader);
		free(info);
		free(rgb);
		return 0;
	}
	}
}
