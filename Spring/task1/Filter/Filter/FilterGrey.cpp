#include "stdafx.h"
#include "FilterGrey.h"


FilterGrey::FilterGrey() {}

void FilterGrey::run(RGB** rgb, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			double newColor = 0.072 * rgb[i][j].rgbBlue + 0.213 * rgb[i][j].rgbRed + 0.0715 * rgb[i][j].rgbGreen;
			rgb[i][j].rgbBlue = doubleToChar(newColor);
			rgb[i][j].rgbRed = doubleToChar(newColor);
			rgb[i][j].rgbGreen = doubleToChar(newColor);
		}
	}
}


FilterGrey::~FilterGrey() {}
