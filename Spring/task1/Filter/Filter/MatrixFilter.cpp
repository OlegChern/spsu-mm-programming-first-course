#include "stdafx.h"
#include "MatrixFilter.h"


MatrixFilter::MatrixFilter(double** matrix)
{
	this->matrix = matrix;
}

void MatrixFilter::run(RGB** rgb, int width, int height)
{
	double Red, Green, Blue;
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
					Red += rgb[i + k - 1][j + m - 1].rgbRed * matrix[k][m];
					Green += rgb[i + k - 1][j + m - 1].rgbGreen * matrix[k][m];
					Blue += rgb[i + k - 1][j + m - 1].rgbBlue * matrix[k][m];
				}
			}
			rgb[i][j].rgbRed = doubleToChar(Red);
			rgb[i][j].rgbGreen = doubleToChar(Green);
			rgb[i][j].rgbBlue = doubleToChar(Blue);
		}
	}
}

MatrixFilter::~MatrixFilter()
{
}
