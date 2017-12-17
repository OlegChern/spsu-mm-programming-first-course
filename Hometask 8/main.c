#include <stdio.h>
#include <stdlib.h>
#include "bmpprocessing.h"

void processImage(char **args);

int main(int argc, char **argv)
{
	// Testing
	char *params1[] = { "BMPIn\\Colors24.bmp", "ToGray", "BMPOut\\Colors24Gray.bmp" };
	processImage(params1);
	char *params2[] = { "BMPIn\\Colors32.bmp", "ToGray", "BMPOut\\Colors32Gray.bmp" };
	processImage(params2);
	char *params3[] = { "BMPIn\\Colors24.bmp", "Filter3x3", "BMPOut\\Colors24Filtered.bmp" };
	processImage(params3);
	char *params4[] = { "BMPIn\\Colors32.bmp", "Filter3x3", "BMPOut\\Colors32Filtered.bmp" };
	processImage(params4);
	char *params5[] = { "BMPIn\\Colors24.bmp", "Gauss5x5", "BMPOut\\Colors24Gauss.bmp" };
	processImage(params5);
	char *params6[] = { "BMPIn\\Colors32.bmp", "Gauss5x5", "BMPOut\\Colors32Gauss.bmp" };
	processImage(params6);
	/*
	if (argc != 4)
	{
	printf("Using: %s input, mode, output\n", argv[0]);
	exit(1);
	}
	processImage(argv+1);
	*/

	system("pause");
	return 0;
}

void processImage(char **args)
{
	readInput(args[0]);
	callMethod(args[1]);
	writeOutput(args[2]);
}
