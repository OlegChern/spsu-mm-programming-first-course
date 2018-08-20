#pragma once
#include "Filter.h"

class FilterGrey : public Filter
{
public:
	FilterGrey();
	void run(RGB** rgb, int width, int height);
	~FilterGrey();
};

