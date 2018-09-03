#pragma once
#include "Filter.h"
class MatrixFilter : public Filter
{
	double** matrix;
public:
	MatrixFilter(double** matrix);
	void run(RGB** rgb, int width, int height);
	~MatrixFilter();
};

