#include "stdafx.h"
#include "FilterGrey.h"


FilterGrey::FilterGrey() {}

RGB** FilterGrey::run(RGB** rgb, int width, int height)
{
	RGB** newRgb = new RGB*[height];
	for (int i = 0; i < height; i++)
	{
		newRgb[i] = new RGB[width];
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			double newColor = 0.072 * rgb[i][j].rgbBlue + 0.213 * rgb[i][j].rgbRed + 0.0715 * rgb[i][j].rgbGreen;
			newRgb[i][j].rgbBlue = doubleToChar(newColor);
			newRgb[i][j].rgbRed = doubleToChar(newColor);
			newRgb[i][j].rgbGreen = doubleToChar(newColor);
		}
	}
	return newRgb;
}


FilterGrey::~FilterGrey() {}
