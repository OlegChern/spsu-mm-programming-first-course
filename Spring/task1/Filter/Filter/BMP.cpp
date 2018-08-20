#include "stdafx.h"
#include "BMP.h"
using namespace std;


BMP::BMP(string inFileName)
{
	ifstream fin(inFileName, ios::in | ios::binary);
	if (!fin)
	{
		cout << "No such file!!";
	}
	bitmapFileHeader = new BitmapFileHeader();
	bitmapInfoHeader = new BitmapInfoHeader();
	fin.read((char*)&bitmapFileHeader->Type, sizeof(bitmapFileHeader->Type));
	fin.read((char*)&bitmapFileHeader->Size, sizeof(bitmapFileHeader->Size));
	fin.read((char*)&bitmapFileHeader->Reserved1, sizeof(bitmapFileHeader->Reserved1));
	fin.read((char*)&bitmapFileHeader->Reserved2, sizeof(bitmapFileHeader->Reserved2));
	fin.read((char*)&bitmapFileHeader->Reserved2, sizeof(bitmapFileHeader->OffBits));

	fin.read((char*)&bitmapInfoHeader->Size, sizeof(bitmapInfoHeader->Size));
	fin.read((char*)&bitmapInfoHeader->Width, sizeof(bitmapInfoHeader->Width));
	fin.read((char*)&bitmapInfoHeader->Height, sizeof(bitmapInfoHeader->Height));
	fin.read((char*)&bitmapInfoHeader->Planes, sizeof(bitmapInfoHeader->Planes));
	fin.read((char*)&bitmapInfoHeader->BitCount, sizeof(bitmapInfoHeader->BitCount));
	fin.read((char*)&bitmapInfoHeader->Compression, sizeof(bitmapInfoHeader->Compression));
	fin.read((char*)&bitmapInfoHeader->SizeImage, sizeof(bitmapInfoHeader->SizeImage));
	fin.read((char*)&bitmapInfoHeader->XPelsPerMeter, sizeof(bitmapInfoHeader->XPelsPerMeter));
	fin.read((char*)&bitmapInfoHeader->YPelsPerMeter, sizeof(bitmapInfoHeader->YPelsPerMeter));
	fin.read((char*)&bitmapInfoHeader->ClrUsed, sizeof(bitmapInfoHeader->ClrUsed));
	fin.read((char*)&bitmapInfoHeader->ClrImportant, sizeof(bitmapInfoHeader->ClrImportant));

	/*fin >> bitmapFileHeader->Type >> bitmapFileHeader->Size >> bitmapFileHeader->Reserved1 >> bitmapFileHeader->Reserved2 >> bitmapFileHeader->OffBits;
	fin >> bitmapInfoHeader->Size >> bitmapInfoHeader->Width >> bitmapInfoHeader->Height >> bitmapInfoHeader->Planes >>
	bitmapInfoHeader->BitCount >> bitmapInfoHeader->Compression >> bitmapInfoHeader->SizeImage >> bitmapInfoHeader->XPelsPerMeter >>
	bitmapInfoHeader->YPelsPerMeter >> bitmapInfoHeader->ClrUsed >> bitmapInfoHeader->ClrImportant;
	*/
	if ((bitmapInfoHeader->BitCount != 24) && (bitmapInfoHeader->BitCount != 32) || (bitmapFileHeader->Type != 0x4D42))
	{
		cout << bitmapInfoHeader->BitCount << " " << bitmapFileHeader->Type << "\n";
		cout << "Wrong format!!!";
		//return;
	}

	rgb = new RGB*[bitmapInfoHeader->Height];
	for (int i = 0; i < bitmapInfoHeader->Height; i++)
	{
		rgb[i] = new RGB[bitmapInfoHeader->Width];
	}

	for (int i = 0; i < bitmapInfoHeader->Height; i++)
	{
		for (int j = 0; j < bitmapInfoHeader->Width; j++)
		{
			fin.read((char*)&rgb[i][j].rgbBlue, sizeof(rgb[i][j].rgbBlue));
			fin.read((char*)&rgb[i][j].rgbGreen, sizeof(rgb[i][j].rgbGreen));
			fin.read((char*)&rgb[i][j].rgbRed, sizeof(rgb[i][j].rgbRed));
			if (bitmapInfoHeader->BitCount == 32)
			{
				char c;
				fin.read(&c, sizeof(char));
			}
		}
	}
}
void BMP::writeBMP(string outFileName)
{
	ofstream fout(outFileName, ios::out | ios::binary);
	/*fout << bitmapFileHeader->Type << bitmapFileHeader->Size << bitmapFileHeader->Reserved1 << bitmapFileHeader->Reserved2 << bitmapFileHeader->OffBits;
	fout << bitmapInfoHeader->Size << bitmapInfoHeader->Width << bitmapInfoHeader->Height << bitmapInfoHeader->Planes << bitmapInfoHeader->BitCount <<
	bitmapInfoHeader->Compression << bitmapInfoHeader->SizeImage << bitmapInfoHeader->XPelsPerMeter << bitmapInfoHeader->YPelsPerMeter <<
	bitmapInfoHeader->ClrUsed << bitmapInfoHeader->ClrImportant;
	*/

	fout.write((char*)&bitmapFileHeader->Type, sizeof(bitmapFileHeader->Type));
	fout.write((char*)&bitmapFileHeader->Size, sizeof(bitmapFileHeader->Size));
	fout.write((char*)&bitmapFileHeader->Reserved1, sizeof(bitmapFileHeader->Reserved1));
	fout.write((char*)&bitmapFileHeader->Reserved2, sizeof(bitmapFileHeader->Reserved2));
	fout.write((char*)&bitmapFileHeader->Reserved2, sizeof(bitmapFileHeader->OffBits));

	fout.write((char*)&bitmapInfoHeader->Size, sizeof(bitmapInfoHeader->Size));
	fout.write((char*)&bitmapInfoHeader->Width, sizeof(bitmapInfoHeader->Width));
	fout.write((char*)&bitmapInfoHeader->Height, sizeof(bitmapInfoHeader->Height));
	fout.write((char*)&bitmapInfoHeader->Planes, sizeof(bitmapInfoHeader->Planes));
	fout.write((char*)&bitmapInfoHeader->BitCount, sizeof(bitmapInfoHeader->BitCount));
	fout.write((char*)&bitmapInfoHeader->Compression, sizeof(bitmapInfoHeader->Compression));
	fout.write((char*)&bitmapInfoHeader->SizeImage, sizeof(bitmapInfoHeader->SizeImage));
	fout.write((char*)&bitmapInfoHeader->XPelsPerMeter, sizeof(bitmapInfoHeader->XPelsPerMeter));
	fout.write((char*)&bitmapInfoHeader->YPelsPerMeter, sizeof(bitmapInfoHeader->YPelsPerMeter));
	fout.write((char*)&bitmapInfoHeader->ClrUsed, sizeof(bitmapInfoHeader->ClrUsed));
	fout.write((char*)&bitmapInfoHeader->ClrImportant, sizeof(bitmapInfoHeader->ClrImportant));

	for (int i = 0; i < bitmapInfoHeader->Height; i++)
	{
		for (int j = 0; j < bitmapInfoHeader->Width; j++)
		{
			fout.write((char*)&rgb[i][j].rgbBlue, sizeof(rgb[i][j].rgbBlue));
			fout.write((char*)&rgb[i][j].rgbGreen, sizeof(rgb[i][j].rgbGreen));
			fout.write((char*)&rgb[i][j].rgbRed, sizeof(rgb[i][j].rgbRed));
			//fout << rgb[i][j].rgbBlue << rgb[i][j].rgbGreen << rgb[i][j].rgbRed;
			if (bitmapInfoHeader->BitCount == 32)
			{
				char c = 0;
				fout.write(&c, sizeof(char));
			}
		}
	}
}

void BMP::useFilter(Filter& filter)
{
	filter.run(rgb, bitmapInfoHeader->Width, bitmapInfoHeader->Height);
}

BMP::~BMP()
{
}
