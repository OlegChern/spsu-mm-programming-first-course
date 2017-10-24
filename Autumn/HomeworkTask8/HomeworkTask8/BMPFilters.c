#include <stdio.h>

typedef unsigned char UBYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;

#pragma pack(1)
typedef struct
{
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER;
#pragma pack()

#pragma pack(1)
typedef struct
{
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} BITMAPINFOHEADER;
#pragma pack()

typedef struct
{
	UBYTE red;
	UBYTE green;
	UBYTE blue;
} PIXEL;

PIXEL* pixelNew(UBYTE, UBYTE, UBYTE);
void Clamp(short*);

int main()
{
	int restartFileChoosing = 1;

	do {
		FILE *sourceFile;
		BITMAPFILEHEADER bmFileHeader;
		BITMAPINFOHEADER bmInfoHeader;
		UBYTE *image;

		int restartFilterChoosing = 1;

		{
			char* pathsource = malloc(sizeof(char) * 64);
			printf("Enter path to source file : \n");
			scanf("%s", pathsource);
			sourceFile = fopen(pathsource, "rb");
			free(pathsource);
		}

		if (sourceFile == NULL)
		{
			printf("Wrong path!\n");
			continue;
		}

		fread(&bmFileHeader, sizeof(BITMAPFILEHEADER), 1, sourceFile);
		if (bmFileHeader.bfType != 0x4D42)
		{
			printf("Wrong file header type!\n");
			continue;
		}

		fread(&bmInfoHeader, sizeof(BITMAPINFOHEADER), 1, sourceFile);
		if (bmInfoHeader.biSize != 0x28)
		{
			printf("Wrong info header size!\n");
			continue;
		}
		fseek(sourceFile, bmFileHeader.bfOffBits, SEEK_SET);

		image = (UBYTE*)malloc(bmInfoHeader.biSizeImage);
		if (!image)
		{
			printf("Not enough memory!\n");
			free(image);
			continue;
		}
		
		// read 
		fread(image, bmInfoHeader.biSizeImage, 1, sourceFile);
		if (image == NULL)
		{
			printf("Image is NULL!\n");
			continue;
		}

		// choosing filter
		do {

			int filter = 0;
			FILE *targetFile;
			int width = bmInfoHeader.biWidth;
			int height = bmInfoHeader.biHeight;

			{
				char* pathtarget = malloc(sizeof(char) * 64);
				printf("Enter path to target file : \n");
				scanf("%s", pathtarget);
				targetFile = fopen(pathtarget, "wb");
				free(pathtarget);
			}

			if (targetFile == NULL)
			{
				printf("Wrong path!\n");
				continue;
			}

			//new image with RGB
			PIXEL **newImage = (PIXEL**)malloc(sizeof(PIXEL**) * width);
			if (!newImage)
			{
				printf("Not enough memory!\n");
				continue;
			}

			for (int i = 0; i < width; i++)
			{
				newImage[i] = (PIXEL*)malloc(sizeof(PIXEL*) * height);
				if (!newImage[i])
				{
					printf("Not enough memory!\n");
					free(newImage);
					continue;
				}
			}

			// for writing into file
			UBYTE pad[3] = { 0, 0, 0 };
			int padSize = (4 - (width * 3) % 4) % 4;
			fwrite(&bmFileHeader, sizeof(BITMAPFILEHEADER), 1, targetFile);
			fwrite(&bmInfoHeader, sizeof(BITMAPINFOHEADER), 1, targetFile);
			// fseek(targetFile, bmFileHeader.bfOffBits, SEEK_SET);

			// pixel array
			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					int offset = (x + y*width) * 3 + y * padSize;

					newImage[x][y].red = image[offset + 2];
					newImage[x][y].green = image[offset + 1];
					newImage[x][y].blue = image[offset];
				}
			}

			printf("Choose filter:\n0 = Average3x3 (default)\n1 = Gaussian3x3\n2 = Sobel X\n3 = Sobel Y\n4 = GreyScale\n");
			scanf("%d", &filter);

			switch (filter)
			{
			case 1: // gaussian3x3

				break;
			case 2: // sobelx

				break;
			case 3: // sobely

				break;
			case 4: // greyscale

				break;
			default: // avg3x3
				for (int x = 0; x < width; x++)
				{
					for (int y = 0; y < height; y++)
					{
						WORD r = 0, g = 0, b = 0; // WORD used, because 255*9 > 255
						for (int i = -1; i < 2; i++)
						{
							for (int j = -1; j < 2; j++)
							{
								if (x + i >= 0 && x + i < width && y + j >= 0 && y + j < height)
								{
									r += newImage[x + i][y + j].red;
									g += newImage[x + i][y + j].green;
									b += newImage[x + i][y + j].blue;
								}
							}
						}
						newImage[x][y] = *(pixelNew(r / 9, g / 9, b / 9));
					}
				}
				break;
			}

			// write new image to file
			// fseek(targetFile, bmFileHeader.bfOffBits, SEEK_SET);
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					/*Clamp(&r);
					Clamp(&g);
					Clamp(&b);*/

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
			fclose(targetFile);

			printf("Done!\n");

			restartFilterChoosing = 0;

		} while (restartFilterChoosing != 0);

		fclose(sourceFile);
		restartFileChoosing = 0;

	} while (restartFileChoosing != 0);

	return 0;
}

PIXEL* pixelNew(UBYTE r, UBYTE g, UBYTE b)
{
	PIXEL* p = malloc(sizeof(PIXEL));
	p->red = r;
	p->green = g;
	p->blue = b;
	return p;
}

void Clamp(short *value)
{
	*value = 
		*value < 0 ? 0 : 
		*value > 255 ? 255 : 
		*value;
}