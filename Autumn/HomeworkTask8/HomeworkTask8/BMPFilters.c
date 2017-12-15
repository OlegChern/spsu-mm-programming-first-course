#pragma warning(disable:4996) // _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include "BMPFilters.h"

int main(int argc, char **argv)
{
	if (argc < 4)
	{
		printf("Not enough arguments! Should be:\n");

		printf("[source path] [filter name] [target path]\n\n");

		printf("Available filters:\n");
		printf("- Gauss\n");
		printf("- SobelX\n");
		printf("- SobelY\n");
		printf("- GrayScale\n");
		printf("- Average\n");

		return 0;
	}

	char openedCount = 2;
	char done = TRUE;

	FILE *sourceFile;
	FILE *targetFile;

	BITMAPFILEHEADER bmFileHeader;
	BITMAPINFOHEADER bmInfoHeader;

	printf("Wait. ");

	sourceFile = fopen(argv[1], "rb");
	if (sourceFile == NULL)
	{
		printf("Wrong source path!\n");
		return 0;
	}

	targetFile = fopen(argv[3], "wb");
	if (targetFile == NULL)
	{
		printf("Wrong target path!\n");
		openedCount--;

		return 0;
	}

	fread(&bmFileHeader, sizeof(BITMAPFILEHEADER), 1, sourceFile);
	if (bmFileHeader.bfType != 0x4D42)
	{
		printf("Wrong file header type!\n");
		openedCount--;

		return 0;
	}

	fread(&bmInfoHeader, sizeof(BITMAPINFOHEADER), 1, sourceFile);
	if (bmInfoHeader.biSize != 0x28)
	{
		printf("Wrong info header size!\n");
		openedCount--;

		return 0;
	}

	fseek(sourceFile, bmFileHeader.bfOffBits, SEEK_SET);

	// array from source file
	UBYTE *image = (UBYTE*)malloc(bmInfoHeader.biSizeImage);
	if (!image)
	{
		printf("Not enough memory!\n");
		openedCount--;

		return 0;
	}

	fread(image, bmInfoHeader.biSizeImage, 1, sourceFile);

	int width = bmInfoHeader.biWidth;
	int height = bmInfoHeader.biHeight;

	// new image with RGB

	PIXEL **newImage = (PIXEL**)malloc(sizeof(PIXEL*) * width);
	if (!createImage(width, height, newImage))
	{
		free(image);
		openedCount--;
	}

	openedCount = openedCount < 0 ? 0 : openedCount;
	switch (openedCount)
	{
		case 1:
		{
			closeFiles(1, sourceFile);
			break;
		}
		case 0:
		{
			closeFiles(2, sourceFile, targetFile);
			break;
		}
	}

	// padding
	UBYTE pad[3] = { 0, 0, 0 };
	int padSize = (4 - (width * 3) % 4) % 4;

	fwrite(&bmFileHeader, sizeof(BITMAPFILEHEADER), 1, targetFile);
	fwrite(&bmInfoHeader, sizeof(BITMAPINFOHEADER), 1, targetFile);

	int pixelSize = bmInfoHeader.biBitCount / 8; // 32bit image check

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int offset = (x + y * width) * pixelSize + y * padSize;

			newImage[x][y].red = image[offset + 2];
			newImage[x][y].green = image[offset + 1];
			newImage[x][y].blue = image[offset];
		}
	}

	// applying filter
	if (compare(argv[2], "Gauss"))//(strcmp(argv[2], "Gauss") == 0)
	{
		printf("Applying Gauss3x3 filter.\n");

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

		if (!gauss3x3(width, height, kernel, newImage))
		{
			done = FALSE;
		}

		for (char i = 0; i < 3; i++)
		{
			free(kernel[i]);
		}

		free(kernel);
	}
	else if (compare(argv[2], "SobelX"))
	{
		printf("Applying SobelX filter\n");

		char maskx[3][3] =
		{
			{ -1, 0, 1 },
			{ -2, 0, 2 },
			{ -1, 0, 1 }
		};

		if (!sobel(width, height, maskx, newImage))
		{
			done = FALSE;
		}
	}
	else if (compare(argv[2], "SobelY"))
	{
		printf("Applying SobelY filter.\n");

		char masky[3][3] =
		{
			{ -1, -2, -1 },
			{ 0, 0, 0 },
			{ 1, 2, 1 }
		};

		if (!sobel(width, height, masky, newImage))
		{
			done = FALSE;
		}
	}
	else if (compare(argv[2], "GrayScale"))
	{
		printf("Applying GrayScale filter.\n");
		grayscale(width, height, newImage);
	}
	else if (compare(argv[2], "Average"))
	{
		printf("Applying Average3x3 filter.\n");

		float **average = (float**)malloc(sizeof(float*) * 3);
		for (char i = 0; i < 3; i++)
		{
			average[i] = (float*)malloc(sizeof(float) * 3);
			for (char j = 0; j < 3; j++)
			{
				average[i][j] = 1.0f / 9.0f;
			}
		}

		if (!gauss3x3(width, height, average, newImage))
		{
			done = FALSE;
		}

		for (char i = 0; i < 3; i++)
		{
			free(average[i]);
		}

		free(average);
	}
	else
	{
		printf("Wrong filter name! Available filters:\n");
		printf("- Gauss\n");
		printf("- SobelX\n");
		printf("- SobelY\n");
		printf("- GrayScale\n");
		printf("- Average\n");

		done = FALSE;
	}

	// if there is no errors
	if (done)
	{
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

				if (pixelSize == 4) // if 32bit image
				{
					UBYTE a = 0; // just delete alpha channel
					fwrite((UBYTE*)&a, 1, 1, targetFile);
				}
			}
			fwrite((char*)pad, padSize, 1, targetFile);
		}

		printf("Done!\n");
	}

	free(image);
	closeImage(width, newImage);
	closeFiles(2, sourceFile, targetFile);

	return 0;
}

int createImage(int width, int height, PIXEL **target)
{
	if (!target)
	{
		printf("Not enough memory!\n");
		return 0;
	}

	for (int i = 0; i < width; i++)
	{
		target[i] = (PIXEL*)malloc(sizeof(PIXEL) * height);
		if (!target[i])
		{
			printf("Not enough memory!\n");
			return 0;
		}
	}

	return 1;
}

void closeImage(int width, PIXEL **target)
{
	for (int i = 0; i < width; i++)
	{
		free(target[i]);
	}

	free(target);
}

PIXEL *pixelNew(UBYTE r, UBYTE g, UBYTE b)
{
	PIXEL* p = (PIXEL*)malloc(sizeof(PIXEL));
	p->red = r;
	p->green = g;
	p->blue = b;
	return p;
}

PIXEL *pixelNewSame(UBYTE v)
{
	PIXEL* p = (PIXEL*)malloc(sizeof(PIXEL));
	p->red = v;
	p->green = v;
	p->blue = v;
	return p;
}

UBYTE pixelGrayscaled(PIXEL p)
{
	return (UBYTE)((p.blue + p.green + p.red) / 3);
}

UBYTE clampToUBYTE(short value)
{
	UBYTE clamped =
		value < 0 ? 0 :
		value > 255 ? 255 :
		(UBYTE)value;

	return clamped;
}

UBYTE roundUBYTE(float f)
{
	UBYTE rounded = f - (float)((int)f) >= 0.5f ? 
		(int)f + 1 :
		(int)f;

	return rounded;
}

int gauss3x3(int width, int height, float **kernel, PIXEL **newImage)
{
	for (int x = 1; x < width - 1; x++)
	{
		for (int y = 1; y < height - 1; y++)
		{
			float sum = 0;
			float r = 0, g = 0, b = 0;

			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					PIXEL pix = newImage[x + i][y + j];

					r += pix.red * kernel[i + 1][j + 1];
					g += pix.green * kernel[i + 1][j + 1];
					b += pix.blue * kernel[i + 1][j + 1];

					sum += kernel[i + 1][j + 1];
				}
			}

			if (sum != 0)
			{
				newImage[x][y] = *(pixelNew(roundUBYTE(r / sum), roundUBYTE(g / sum), roundUBYTE(b / sum)));
			}
		}
	}

	return 1;
}

int sobel(int width, int height, char mask[3][3], PIXEL **targetImage)
{
	PIXEL **temp = (PIXEL**)malloc(sizeof(PIXEL*) * width);
	if (!createImage(width, height, temp))
	{
		printf("Not enough memory!\n");
		return 0;
	}

	for (int x = 1; x < width - 1; x++)
	{
		for (int y = 1; y < height - 1; y++)
		{
			short sum = 0;

			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					UBYTE cur = pixelGrayscaled(targetImage[x + i][y + j]);
					sum += cur * mask[i + 1][j + 1];
				}
			}

			UBYTE clamped = clampToUBYTE(sum);
			temp[x][y] = *(pixelNewSame(clamped));
		}
	}

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			targetImage[x][y] = temp[x][y];
		}
	}

	return 1;
}

int grayscale(int width, int height, PIXEL **newImage)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			UBYTE grayscale = pixelGrayscaled(newImage[x][y]);
			newImage[x][y] = *(pixelNewSame(grayscale));
		}
	}

	return 1;
}

int compare(const char *c1, const char*c2)
{
	return strcmp(c1, c2) == 0;
}

void closeFiles(int count, ...)
{
	va_list files;

	va_start(files, count);

	for (int i = 0; i < count; i++)
	{
		fclose(va_arg(files, FILE*));
	}

	va_end(files);
}