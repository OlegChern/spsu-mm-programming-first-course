#pragma once
#define NUMS_OF_FILTERS 4

class ListOfMatrixForFilters {
	double*** tableOfMatrix;
public:
	enum { Average, Gauss, SobelX, SobelY } numsOfFilters;
	ListOfMatrixForFilters();
	double** getAverageMatrix();
	double** getGaussMatrix();
	double** getSobelXMatrix();
	double** getSobelYMatrix();
};