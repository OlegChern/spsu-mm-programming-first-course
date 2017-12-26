#pragma once

#pragma pack(2)

typedef struct
{
	unsigned __int16 bfType;       // 0x4d42 | 0x4349 | 0x5450
	int bfSize;                    // ������ �����
	int bfReserved;                // 0
	int bfOffBits;                 // �������� �� ���� ������

	int biSize;                    // ������ �������� � ������
	int biWidth;                   // ������ � ������
	int biHeight;                  // ������ � ������
	unsigned __int16 biPlanes;     // ������ ������ ���� 1
	unsigned __int16 biBitCount;   // � ����� ������ 24 | 32
	int biCompression;             // BI_RGB 
	int biSizeImage;               // ���������� ���� � ���� ������ (� ����� ������ 0)
	int biXPelsPerMeter;           // �������������� ����������, ����� �� ����
	int biYPelsPerMeter;           // ������������ ����������, ����� �� ����
	int biClrUsed;                 // ���������� ������������ ������ (���� ���� ������� ������)
	int biClrImportant;            // ���������� ������������ ������.
}BMPHeader;

typedef struct
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
}RGB;

int* readBMP(FILE * fInput, int *bitCount, int *row, int *column);

int writeBMP(FILE * Output, int* fMemory, int *row, int *column);

void filterArrayRGB(int *fMemory, RGB **valuePixels, int row, int column, char* filter);

unsigned char color(int value);

void gray(RGB** valuePixels, int row, int column);

void filt(RGB** valuePixels, int row, int column, const int array[2][9]);

