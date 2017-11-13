#pragma warning(disable:4996) // _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "BMPFilters.h"

int main(int argc, char **argv)
{
	//Gauss
	//SobelX
	//SobelY 
	//GrayScale
	//Average

	if (argc < 4)
	{
		printf("Not enough arguments!");
		return 0;
	}

	FILE *sourceFile;
	FILE *targetFile;

	BITMAPFILEHEADER bmFileHeader;
	BITMAPINFOHEADER bmInfoHeader;

	int bit32 = 0;

	sourceFile = fopen(argv[1], "rb");
	if (sourceFile == NULL)
	{
		printf("Wrong path!\n");
		return 0;
	}

	targetFile = fopen(argv[2], "wb");
	if (targetFile == NULL)
	{
		printf("Wrong path!\n");
		return 0;
	}

	fread(&bmFileHeader, sizeof(BITMAPFILEHEADER), 1, sourceFile);
	if (bmFileHeader.bfType != 0x4D42)
	{
		printf("Wrong file header type!\n");
		return 0;
	}

	fread(&bmInfoHeader, sizeof(BITMAPINFOHEADER), 1, sourceFile);
	if (bmInfoHeader.biSize != 0x28)
	{
		printf("Wrong info header size!\n");
		return 0;
	}

	fseek(sourceFile, bmFileHeader.bfOffBits, SEEK_SET);

	// array from source file
	UBYTE *image = (UBYTE*)malloc(bmInfoHeader.biSizeImage);
	if (!image)
	{
		printf("Not enough memory!\n");
		free(image);
		return 0;
	}

	fread(image, bmInfoHeader.biSizeImage, 1, sourceFile);

	int width = bmInfoHeader.biWidth;
	int height = bmInfoHeader.biHeight;

	// new image with RGB
	PIXEL **newImage = (PIXEL**)malloc(sizeof(PIXEL*) * width);
	if (!newImage)
	{
		printf("Not enough memory!\n");
		return 0;
	}

	for (int i = 0; i < width; i++)
	{
		newImage[i] = (PIXEL*)malloc(sizeof(PIXEL) * height);
		if (!newImage[i])
		{
			printf("Not enough memory!\n");
			free(newImage);
			return 0;
		}
	}

	// padding
	UBYTE pad[3] = { 0, 0, 0 };
	int padSize = (4 - (width * 3) % 4) % 4;

	fwrite(&bmFileHeader, sizeof(BITMAPFILEHEADER), 1, targetFile);
	fwrite(&bmInfoHeader, sizeof(BITMAPINFOHEADER), 1, targetFile);

	// pixel array
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int offset = (x + y * width) * 3 + y * padSize;

			newImage[x][y].red = image[offset + 2];
			newImage[x][y].green = image[offset + 1];
			newImage[x][y].blue = image[offset];
		}
	}

	// applying filter
	if (strcmp(argv[2], "Gauss") == 0) // argv[2] == "Gauss")
	{
		float sigma = 1;
		sigma = 2 * sigma * sigma;

		float **kernel = (float**)malloc(sizeof(float*) * 3);
		for (char i = -1; i <= 1; i++)
		{
			kernel[i + 1] = (float*)malloc(sizeof(float) * 3);
			for (char j = -1; j <= 1; j++)
			{
				kernel[i + 1][j + 1] = (float)((exp(-(i*i + j*j) / sigma)) / (PI * sigma));
			}
		}

		gauss3x3(width, height, kernel, newImage);
	}
	else if (strcmp(argv[2], "SobelX") == 0) // argv[2] == "SobelX")
	{
		char maskx[3][3] =
		{
			{ -1, 0, 1 },
			{ -2, 0, 2 },
			{ -1, 0, 1 }
		};

		sobel(width, height, maskx, newImage);
	}
	else if (strcmp(argv[2], "SobelY") == 0) // argv[2] == "SobelY")
	{
		char masky[3][3] =
		{
			{ -1, -2, -1 },
			{ 0, 0, 0 },
			{ 1, 2, 1 }
		};

		sobel(width, height, masky, newImage);
	}
	else if (strcmp(argv[2], "GrayScale") == 0) // argv[2] == "GrayScale")
	{
		grayscale(width, height, newImage);
	}
	else if (strcmp(argv[2], "Average") == 0) // argv[2] == "Average")
	{
		average3x3(width, height, newImage);
	}
	else
	{
		printf("Available filters:\n");
		printf("- Gauss\n");
		printf("- SobelX\n");
		printf("- SobelY\n");
		printf("- GrayScale\n");
		printf("- Average\n");
	}

	// write new image to file
	fseek(targetFile, bmFileHeader.bfOffBits, SEEK_SET);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			UBYTE b = newImage[x][y].blue;
			UBYTE g = newImage[x][y].green;
			UBYTE r = newImage[x][y].red;

			fwrite((UBYTE*)&b, 1, 1, targetFile);
			fwrite((UBYTE*)&g, 1, 1, targetFile);
			fwrite((UBYTE*)&r, 1, 1, targetFile);
		}
		fwrite((char*)pad, padSize, 1, targetFile);
	}

	free(image);

	fclose(sourceFile);
	fclose(targetFile);

	printf("Done!\n");

	return 0;
}