#pragma once
#include <fstream>
#include <iostream>
#include "Filter.h"
using namespace std;



struct BitmapFileHeader
{
	unsigned __int16 Type;
	unsigned __int32 Size;
	unsigned __int16 Reserved1;
	unsigned __int16 Reserved2;
	unsigned __int32 OffBits;
};

struct BitmapInfoHeader
{
	unsigned __int32 Size;
	unsigned __int32 Width;
	unsigned __int32 Height;
	unsigned __int16 Planes;
	unsigned __int16 BitCount;
	unsigned __int32 Compression;
	unsigned __int32 SizeImage;
	unsigned __int32 XPelsPerMeter;
	unsigned __int32 YPelsPerMeter;
	unsigned __int32 ClrUsed;
	unsigned __int32 ClrImportant;
};

class BMP
{
private:
	BITMAPINFOHEADER * bitmapInfoHeader;
	BITMAPFILEHEADER* bitmapFileHeader;
	RGB** rgb;
	int linePadding;
	char* palette;
	long long paletteSize;
public:
	BMP(string inFileName);
	void useFilter(Filter& filter);
	void writeBMP(string outFileName);
	~BMP();
};