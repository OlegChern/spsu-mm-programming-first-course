#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "util.h"

const char *about = "This is utility that applies selected filter to selected .bmp image.\n"
                    "Arguments:\n"
                    "-i: path to file to be modified.\n"
                    "-o: path to desired destination of resulting image.\n"
                    "-f: filter to be applied.\n"
                    "  possible filters:\n"
                    "    gauss\n"
                    "    sobelx\n"
                    "    sobely\n"
                    "    greyen\n";

const double gaussMatrix[3][3] = {{1.0 / 16, 1.0 / 8, 1.0 / 16},
                                  {1.0 / 8, 1.0 / 4, 1.0 / 8},
                                  {1.0 / 16, 1.0 / 8, 1.0 / 16}};

// I used normalisation so that to make sure
// resulting image is no brighter than the original one.

const double sobelxMatrix[3][3] = {{-3.0 / 32, 0, 3.0 / 32},
                                   {-10.0 / 32, 0, 10.0 / 32},
                                   {-3.0 / 32, 0, 3.0 / 32}};

const double sobelyMatrix[3][3] = {{-3.0 / 32, -10.0 / 32, -3.0 / 32},
                                   {0, 0, 0},
                                   {3.0 / 32, 10.0 / 32, 3.0 / 32}};

// TODO: also implement absolute sobel filter

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf(about);
        return 0;
    }

    char *source; // Argument passed after -i, source file path
    char *filter; // Argument passed after -f, filter type
    char *destination; // Argument passed after -o, destination file path

    if (handleArguments(argc, argv, &source, &filter, &destination))
        return 1;

    FILE *fileStreamIn = fopen(source, "rb");
    FILE *fileStreamOut = fopen(destination, "wb");

    // All ugly variable names are equal to the ones in documentation.

    uint16_t bfType; // File format and system endianness
    uint32_t bfSize; // File size
    uint16_t bfReserved1; // Reserved field, needs to be 0
    uint16_t bfReserved2; // Reserved field, needs to be 0
    uint32_t bfOffBits; // Pixel data offset

    uint32_t biSize; // Size of bitmap-info-header structure
    int32_t biWidth; // Image width
    int32_t biHeight; // Image height
    uint16_t biPlains; // The number of color planes (must be 1)
    uint16_t biBitCount; // Number of bits per pixel

    int platform;

    // If it isn't beautiful, huh?
    if (
            handleBitmapFileHeader(fileStreamIn, &bfType, &bfSize, &bfReserved1, &bfReserved2, &bfOffBits, &platform) ||
            handleBitmapInfoHeader(fileStreamIn, &biSize, &biWidth, &biHeight, &biPlains, &biBitCount) ||
            checkSizes(bfSize, bfOffBits, biSize, biWidth, biHeight, biBitCount) ||
            // I know using fseek is a bad thing to do, but I use fseek just once, what can possibly go wrong?
            fseek(fileStreamIn, 0, SEEK_SET) ||
            copyHeader(fileStreamIn, fileStreamOut, bfOffBits) ||
            printf("Working...\n") < 0 ||
            strcmp(filter, gauss) == 0 && applyKernel(biBitCount, biWidth, biHeight, gaussMatrix, fileStreamIn, fileStreamOut, &toByte) ||
            // Note: it is not clear whether I should greyen image when applying sobel filter ir not.
            strcmp(filter, sobelx) == 0 && applyKernel(biBitCount, biWidth, biHeight, sobelxMatrix, fileStreamIn, fileStreamOut, &absToByte) ||
            strcmp(filter, sobely) == 0 && applyKernel(biBitCount, biWidth, biHeight, sobelyMatrix, fileStreamIn, fileStreamOut, &absToByte) ||
            strcmp(filter, greyen) == 0 && applyGreyen(biBitCount, biWidth, biHeight, fileStreamIn, fileStreamOut, platform)
    )
    {
        fclose(fileStreamIn);
        fclose(fileStreamOut);
        return 1;
    }

    fclose(fileStreamIn);
    fclose(fileStreamOut);
    printf("Done.\n");
    return 0;
}
