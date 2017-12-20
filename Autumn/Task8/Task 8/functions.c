#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Header.h"


int* readBMP(FILE * fInput,int *bitCount, int *row, int *column) // ������� ������ ���� � � ������ ������ ���������� ��������� NULL, ����� ���������� ��������� �� ������ �������, ���������� ���������� � ��������.
{
	if (fInput == NULL)   // �������� ������������� �����
	{
		return NULL;
	}

	BMPHeader bh;
	int result;

	result = fread(&bh, 1, sizeof(BMPHeader), fInput);  // ������ ���������
	if (result != sizeof(BMPHeader))
	{
		return NULL;
		fclose(fInput);
	}

	if (bh.bfType != 0x4d42 && bh.bfType != 0x4349 && bh.bfType != 0x5450) // �������� �� BMP
	{
		return NULL;
		fclose(fInput);
	}

	fseek(fInput, 0, SEEK_END);
	int fSize = ftell(fInput);  // ������� ������� �����
	fseek(fInput, sizeof(BMPHeader), SEEK_SET);
	if (bh.bfSize != fSize ||                      // �������� �������
		bh.bfReserved != 0 ||
		bh.biPlanes != 1 ||
		(bh.biSize != 40 && bh.biSize != 108 && bh.biSize != 124) ||
		bh.bfOffBits != 14 + bh.biSize ||
		bh.biWidth < 1 || bh.biWidth > 10000 ||
		bh.biHeight < 1 || bh.biHeight > 10000 ||
		(bh.biBitCount != 24 && bh.biBitCount != 32) ||
		bh.biCompression != 0)
	{
		return NULL;
		fclose(fInput);
	}

	*bitCount = bh.biBitCount;
	*row = bh.biWidth;
	*column = bh.biHeight;
	int rowFull;
	if (bh.biBitCount == 24)
	{
		rowFull = 3 * *row + (3 * *row % 4);          	// ������� ��������� ������ ������� ������
	}
	else
	{
		rowFull = 4 * *row;
	}
	unsigned char *buff = (unsigned char *)malloc(sizeof(unsigned char) * rowFull * *column);
	result = fread(buff, 1, rowFull * *column, fInput); // ������ ������ �������� � ����� 
	if (result != rowFull * *column)
	{
		return NULL;
		fclose(fInput);
	}

	fclose(fInput);

	int* fMemory = (int*)malloc(sizeof(int) * *row * *column);  // ��������� ������ ��� ����������

	// ��������� ������ � �������� � ���������� �������
	unsigned char* pointer = (unsigned char *)fMemory;
	for (int y = *column - 1; y >= 0; y--)
	{
		unsigned char* yRow = buff + rowFull * y;   // ������ ���������� ������� �������
		for (int x = 0; x < *row; x++)
		{
			*pointer++ = *(yRow + 2);       // ������ ������� BGR -> RGB
			*pointer++ = *(yRow + 1);
			*pointer++ = *yRow;
			yRow += 3;
			pointer++;                      // ���������� ���� ����, ����� ��������� � int
		}
	}

	free(buff);
	return fMemory;
}

int writeBMP(FILE * fOutput, int* fMemory, int *row, int *column) // ������� ��������� ������ � ����� ����������� � �������� ���� � � ������ ������ ���������� 0.
{
	if (fOutput == NULL)
	{
		return 1;
	}

	BMPHeader bh;
	memset(&bh, 0, sizeof(bh));
	bh.bfType = 0x4d42;  // ��� bmp.

	int rowFull;
	rowFull = 3 * *row + (3 * *row % 4);          	// ������� ��������� ������ ������� ������ (�������� ���� ����� 24-������)

	int fSize = 54 + rowFull * *column;        // �������� ���������
	bh.bfSize = fSize;
	bh.bfReserved = 0;
	bh.biPlanes = 1;
	bh.biSize = 40;
	bh.bfOffBits = 14 + bh.biSize;
	bh.biWidth = *row;
	bh.biHeight = *column;
	bh.biBitCount = 24;
	bh.biCompression = 0;

	int result;

	result = fwrite(&bh, 1, sizeof(BMPHeader), fOutput);    // ������ ���������
	if (result != sizeof(BMPHeader))
	{
		return 1;
	}

	unsigned char* buff = (unsigned char*)malloc(sizeof(unsigned char) * rowFull * *column);
	unsigned char* pointer = (unsigned char*)fMemory;
	for (int y = *column - 1; y >= 0; y--)     // ��������� � ����� ������ � �������� � ������ ������� (�������� ������� ����� � RGB->BGR)
	{
		unsigned char* yRow = buff + rowFull * y;  
		for (int x = 0; x < *row; x++)        
		{
			*(yRow + 2) = *pointer++;
			*(yRow + 1) = *pointer++;
			*yRow = *pointer++;
			yRow += 3;
			pointer++;
		}
	}

	fwrite(buff, 1, rowFull * *column, fOutput);
	fclose(fOutput);
	free(buff);
	return 0;
}

void median(RGB** valuePixels, int row, int column)
{
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			if ((i != 0) && (i != column - 1) && (j != 0) && (j != row - 1))
			{
				valuePixels[i][j].red = (valuePixels[i][j].red + valuePixels[i][j + 1].red + valuePixels[i + 1][j].red + valuePixels[i + 1][j + 1].red + valuePixels[i - 1][j + 1].red + valuePixels[i - 1][j].red + valuePixels[i - 1][j - 1].red + valuePixels[i][j - 1].red + valuePixels[i + 1][j - 1].red) / 9;
				valuePixels[i][j].green = (valuePixels[i][j].green + valuePixels[i][j + 1].green + valuePixels[i + 1][j].green + valuePixels[i + 1][j + 1].green + valuePixels[i - 1][j + 1].green + valuePixels[i - 1][j].green + valuePixels[i - 1][j - 1].green + valuePixels[i][j - 1].green + valuePixels[i + 1][j - 1].green) / 9;
				valuePixels[i][j].blue = (valuePixels[i][j].blue + valuePixels[i][j + 1].blue + valuePixels[i + 1][j].blue + valuePixels[i + 1][j + 1].blue + valuePixels[i - 1][j + 1].blue + valuePixels[i - 1][j].blue + valuePixels[i - 1][j - 1].blue + valuePixels[i][j - 1].blue + valuePixels[i + 1][j - 1].blue) / 9;
			}
			else
			{
				valuePixels[i][j].red = 0;
				valuePixels[i][j].green = 0;
				valuePixels[i][j].blue = 0;
			}
		}
	}
}

void gauss_3x3(RGB** valuePixels, int row, int column)
{
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			if ((i != 0) && (i != column - 1) && (j != 0) && (j != row - 1))
			{
				valuePixels[i][j].red = (4 * valuePixels[i][j].red + 2 * valuePixels[i][j + 1].red + 2 * valuePixels[i + 1][j].red + valuePixels[i + 1][j + 1].red + valuePixels[i - 1][j + 1].red + 2 * valuePixels[i - 1][j].red + valuePixels[i - 1][j - 1].red + 2 * valuePixels[i][j - 1].red + valuePixels[i + 1][j - 1].red) / 16;
				valuePixels[i][j].green = (4 * valuePixels[i][j].green + 2 * valuePixels[i][j + 1].green + 2 * valuePixels[i + 1][j].green + valuePixels[i + 1][j + 1].green + valuePixels[i - 1][j + 1].green + 2 * valuePixels[i - 1][j].green + valuePixels[i - 1][j - 1].green + 2 * valuePixels[i][j - 1].green + valuePixels[i + 1][j - 1].green) / 16;
				valuePixels[i][j].blue = (4 * valuePixels[i][j].blue + 2 * valuePixels[i][j + 1].blue + 2 * valuePixels[i + 1][j].blue + valuePixels[i + 1][j + 1].blue + valuePixels[i - 1][j + 1].blue + 2 * valuePixels[i - 1][j].blue + valuePixels[i - 1][j - 1].blue + 2 * valuePixels[i][j - 1].blue + valuePixels[i + 1][j - 1].blue) / 16;
			}
			else
			{
				valuePixels[i][j].red = 0;
				valuePixels[i][j].green = 0;
				valuePixels[i][j].blue = 0;
			}
		}
	}
}

unsigned char color(int value)
{
	if (value < 0)
	{
		return 0;
	}
	else if (value > 255)
	{
		return 255;
	}
	else
	{
		return value;
	}
}

void sobel(RGB** valuePixels, int row, int column, int n)
{
	unsigned char* pointer = (unsigned char*)malloc(3 * row * column * sizeof(unsigned char));

	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			if ((i != 0) && (i != column - 1) && (j != 0) && (j != row - 1))
			{
				if (n == 1)
				{
					*pointer++ = color(valuePixels[i - 1][j + 1].red + 2 * valuePixels[i][j + 1].red + valuePixels[i + 1][j + 1].red - valuePixels[i - 1][j - 1].red - 2 * valuePixels[i][j - 1].red - valuePixels[i + 1][j - 1].red);
					*pointer++ = color(valuePixels[i - 1][j + 1].green + 2 * valuePixels[i][j + 1].green + valuePixels[i + 1][j + 1].green - valuePixels[i - 1][j - 1].green - 2 * valuePixels[i][j - 1].green - valuePixels[i + 1][j - 1].green);
					*pointer++ = color(valuePixels[i - 1][j + 1].blue + 2 * valuePixels[i][j + 1].blue + valuePixels[i + 1][j + 1].blue - valuePixels[i - 1][j - 1].blue - 2 * valuePixels[i][j - 1].blue - valuePixels[i + 1][j - 1].blue);
				}
				else
				{
					*pointer++ = color(valuePixels[i + 1][j - 1].red + 2 * valuePixels[i + 1][j].red + valuePixels[i + 1][j + 1].red - valuePixels[i - 1][j - 1].red - 2 * valuePixels[i - 1][j].red - valuePixels[i - 1][j + 1].red);
					*pointer++ = color(valuePixels[i + 1][j - 1].green + 2 * valuePixels[i + 1][j].green + valuePixels[i + 1][j + 1].green - valuePixels[i - 1][j - 1].green - 2 * valuePixels[i - 1][j].green - valuePixels[i - 1][j + 1].green);
					*pointer++ = color(valuePixels[i + 1][j - 1].blue + 2 * valuePixels[i + 1][j].blue + valuePixels[i + 1][j + 1].blue - valuePixels[i - 1][j - 1].blue - 2 * valuePixels[i - 1][j].blue - valuePixels[i - 1][j + 1].blue);
				}
			}
			else
			{
				*pointer++ = 0;
				*pointer++ = 0;
				*pointer++ = 0;
			}
		}
	}
	pointer -= 3 * row * column;
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			valuePixels[i][j].red = *pointer++;
			valuePixels[i][j].green = *pointer++;
			valuePixels[i][j].blue = *pointer++;
		}	
	}
	pointer -= 3 * row * column;

	free(pointer);
}

void gray(RGB** valuePixels, int row, int column)
{
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			unsigned char k = (unsigned char)(0.2126 * valuePixels[i][j].red + 0.7152 * valuePixels[i][j].green + 0.0722 * valuePixels[i][j].blue);
			valuePixels[i][j].red = k;
			valuePixels[i][j].green = k;
			valuePixels[i][j].blue = k;
		}
	}
}

void filterArrayRGB(int *fMemory, RGB **valuePixels, int row, int column, char* filter)
{
	valuePixels = (RGB**)malloc(sizeof(RGB*) * column);
	for (int y = 0; y < column; y++)
	{
		valuePixels[y] = (RGB*)malloc(sizeof(RGB) * row);
	}

	unsigned char* pointer = (unsigned char*)fMemory;

	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			valuePixels[i][j].red = *pointer++;
			valuePixels[i][j].green = *pointer++;
			valuePixels[i][j].blue = *pointer++;
			pointer++;
		}
	}

	if (strcmp(filter, "median3x3") == 0)
	{
		median(valuePixels, row, column);
	}
	else if (strcmp(filter, "gauss_3x3") == 0)
	{
		gauss_3x3(valuePixels, row, column);
	}
	else if (strcmp(filter, "sobel_x") == 0)
	{
		sobel(valuePixels, row, column, 1);
	}
	else if (strcmp(filter, "sobel_y") == 0)
	{
		sobel(valuePixels, row, column, 2);
	}
	else if (strcmp(filter, "gray") == 0)
	{
		gray(valuePixels, row, column);
	}


	unsigned char* pointer2 = (unsigned char*)fMemory;

	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			*pointer2++ = valuePixels[i][j].red;
			*pointer2++ = valuePixels[i][j].green;
			*pointer2++ = valuePixels[i][j].blue;
			pointer2++;
		}
	}

	for (int y = 0; y < column; y++)
	{
		free(valuePixels[y]);
	}

	free(valuePixels);
}
