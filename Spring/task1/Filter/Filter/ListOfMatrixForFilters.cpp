#include "stdafx.h"
#include "ListOfMatrixForFilters.h"

ListOfMatrixForFilters::ListOfMatrixForFilters()
{
	tableOfMatrix = new double**[NUMS_OF_FILTERS];
	for (int i = 0; i < NUMS_OF_FILTERS; i++)
	{
		tableOfMatrix[i] = new double*[3];
		for (int j = 0; j < 3; j++)
		{
			tableOfMatrix[i][j] = new double[3];
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tableOfMatrix[Average][i][j] = 0.1111;
		}
	}
	tableOfMatrix[Gauss][0][0] = 0.0625, tableOfMatrix[Gauss][0][1] = 0.125, tableOfMatrix[Gauss][0][2] = 0.0625;
	tableOfMatrix[Gauss][1][0] = 0.0125, tableOfMatrix[Gauss][1][1] = 0.25, tableOfMatrix[Gauss][1][2] = 0.125;
	tableOfMatrix[Gauss][2][0] = 0.0625, tableOfMatrix[Gauss][2][1] = 0.125, tableOfMatrix[Gauss][2][2] = 0.0625;
	tableOfMatrix[SobelX][0][0] = -1, tableOfMatrix[SobelX][0][1] = 0, tableOfMatrix[SobelX][0][2] = 1;
	tableOfMatrix[SobelX][1][0] = -2, tableOfMatrix[SobelX][1][1] = 0, tableOfMatrix[SobelX][1][2] = 2;
	tableOfMatrix[SobelX][2][0] = -1, tableOfMatrix[SobelX][2][1] = 0, tableOfMatrix[SobelX][2][2] = 1;
	tableOfMatrix[SobelY][0][0] = -1, tableOfMatrix[SobelY][0][1] = -2, tableOfMatrix[SobelY][0][2] = -1;
	tableOfMatrix[SobelY][1][0] = 0, tableOfMatrix[SobelY][1][1] = 0, tableOfMatrix[SobelY][1][2] = 0;
	tableOfMatrix[SobelY][2][0] = 1, tableOfMatrix[SobelY][2][1] = 2, tableOfMatrix[SobelY][2][2] = 1;
}

double** ListOfMatrixForFilters::getAverageMatrix()
{
	return tableOfMatrix[Average];
}

double** ListOfMatrixForFilters::getGaussMatrix()
{
	return tableOfMatrix[Gauss];
}

double** ListOfMatrixForFilters::getSobelXMatrix()
{
	return tableOfMatrix[SobelX];
}

double** ListOfMatrixForFilters::getSobelYMatrix()
{
	return tableOfMatrix[SobelY];
}