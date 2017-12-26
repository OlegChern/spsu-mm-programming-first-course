#pragma once

#pragma pack(2)

typedef struct
{
	unsigned __int16 bfType;       // 0x4d42 | 0x4349 | 0x5450
	int bfSize;                    // Размер файла
	int bfReserved;                // 0
	int bfOffBits;                 // Смещение до поля данных

	int biSize;                    // Размер струкуры в байтах
	int biWidth;                   // Ширина в точках
	int biHeight;                  // Высота в точках
	unsigned __int16 biPlanes;     // Всегда должно быть 1
	unsigned __int16 biBitCount;   // В нашем случае 24 | 32
	int biCompression;             // BI_RGB 
	int biSizeImage;               // Количество байт в поле данных (в нашем случае 0)
	int biXPelsPerMeter;           // Горизонтальное разрешение, точек на дюйм
	int biYPelsPerMeter;           // Вертикальное разрешение, точек на дюйм
	int biClrUsed;                 // Количество используемых цветов (если есть таблица цветов)
	int biClrImportant;            // Количество существенных цветов.
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

