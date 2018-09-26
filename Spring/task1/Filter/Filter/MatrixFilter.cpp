#include "stdafx.h"
#include "MatrixFilter.h"
#include <iostream>

MatrixFilter::MatrixFilter(double** matrix)
{
	this->matrix = matrix;
}

RGB** MatrixFilter::run(RGB** rgb, int width, int height)
{
	double Red, Green, Blue;
	RGB** newRgb = new RGB*[height];
	for (int i = 0; i < height; i++)
	{
		newRgb[i] = new RGB[width];
	}
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			Red = 0;
			Green = 0;
			Blue = 0;

			for (int k = 0; k < 3; k++)
			{
				for (int m = 0; m < 3; m++)
				{
					//cout << i + k - 1 << " " << j + m - 1 << " " << k << " " << m << " | ";
					Red += rgb[i + k - 1][j + m - 1].rgbRed * matrix[k][m];
					Green += rgb[i + k - 1][j + m - 1].rgbGreen * matrix[k][m];
					Blue += rgb[i + k - 1][j + m - 1].rgbBlue * matrix[k][m];
				}
			}
			//cout << Red << " " << Green << " " << Blue << " | ";
			newRgb[i][j].rgbRed = doubleToChar(Red);
			newRgb[i][j].rgbGreen = doubleToChar(Green);
			newRgb[i][j].rgbBlue = doubleToChar(Blue);
			//cout << (int)newRgb[i][j].rgbRed << " " << (int)newRgb[i][j].rgbGreen << " " << (int)newRgb[i][j].rgbBlue << " !\n";
		}
	}
	return newRgb;
}

MatrixFilter::~MatrixFilter()
{
}
