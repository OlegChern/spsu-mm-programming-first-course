#pragma once
#include "Filter.h"

class FilterGrey : public Filter
{
public:
	FilterGrey();
	RGB** run(RGB** rgb, int width, int height);
	~FilterGrey();
};

