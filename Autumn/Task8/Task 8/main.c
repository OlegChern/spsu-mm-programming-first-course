#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Header.h"

int main()
{
	int row = 0, column = 0, bitCount = 0;
	int* fMemory;
	char fName1[100], fName2[100], filter[100];
	FILE *fInput, *fOutput;

	while (1)
	{
		printf("Enter name of input file, filter's name and name of output file:\n");
		printf("1) Input file -- 24 or 32 bit .bmp\n");
		printf("2) Filter's names:\nmedian3x3\ngauss_3x3\nsobel_x\nsobel_y\ngray\n");
		printf("3) Output file -- .bmp\n");

		scanf("%s %s %s", fName1, filter, fName2);
		fInput = fopen(fName1, "rb");
		fOutput = fopen(fName2, "wb");

		fMemory = readBMP(fInput, &bitCount, &row, &column);

		if (fMemory == NULL)
		{
			printf("Error! Try again.\n");
		}
		else
		{	
			RGB** valuePixels = NULL;

			if ((strcmp(filter, "median3x3") == 0) ||
				(strcmp(filter, "gauss_3x3") == 0) ||
				(strcmp(filter, "sobel_x") == 0) ||
				(strcmp(filter, "sobel_y") == 0) ||
				(strcmp(filter, "gray") == 0))
			{
				filterArrayRGB(fMemory, valuePixels, row, column, filter);

				int error = 1;
				error = writeBMP(fOutput, fMemory, &row, &column);
				if (error != 0)
				{
					printf("Error! Try again.\n");
				}
				else
				{
					printf("Succesfully!\n");
					break;
				}
			}
			else
			{
				printf("Error! Try again.\n");
			}
		}
	}
	free(fMemory);

	_getch();
	return 0;
}