#include "stdafx.h"

#include <iostream>
#include <string>
#include "Filter.h"
#include "BMP.h"
#include "MatrixFilter.h"
#include "FilterGrey.h"
#include "ListOfMatrixForFilters.h"
using namespace std;

bool chooseAndUseFilter(string filterName, BMP* bmp)
{
	ListOfMatrixForFilters list;
	switch (filterName[0])
	{
	case 'S':
		if (filterName == "SobelX") {
			MatrixFilter filter(list.getSobelXMatrix());
			bmp->useFilter(filter);
		}
		else if (filterName == "SobelY")
		{
			MatrixFilter filter(list.getSobelYMatrix());
			bmp->useFilter(filter);
		}
		break;
	case 'G':
		if (filterName == "Grey")
		{
			FilterGrey filter;
			bmp->useFilter(filter);
		}
		else if (filterName == "Gauss")
		{
			MatrixFilter filter(list.getGaussMatrix());
			bmp->useFilter(filter);
		}
		break;
	case 'A':
		if (filterName == "Average")
		{
			MatrixFilter filter(list.getAverageMatrix());
			bmp->useFilter(filter);
		}
		break;
	default:
		return 1;
	}
	return 0;
}


int main(int argc, char* argv[])
{
	string inFileName, filterName, outFileName;
	if (argc > 1) {
		inFileName = argv[1];
		filterName = argv[2];
		outFileName = argv[3];
	}
	else {
		cout << "Enter 'Input File Name' 'Name of Filter' 'Output File Name'\nName of avalaible filters:\n1. SobelX\n2. SobelY\n3. Grey\n4. Gauss\n5. Average\n";
		cin >> inFileName >> filterName >> outFileName;
	}
	BMP bmp(inFileName);
	if (chooseAndUseFilter(filterName, &bmp))
	{
		cout << "No such filter!!\n";
	}
	bmp.writeBMP(outFileName);
	system("pause");
	return 0;
}

