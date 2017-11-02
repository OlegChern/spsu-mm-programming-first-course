/**
 * The dark side of force keeps calling me to use goto's.
 * I don't know for how long i'll manage to resist that...
 */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <malloc.h>

#include "colours.h"
#include "util.h"

#define MAIN_ERROR() fclose(fileStreamIn); fclose(fileStreamOut); return 1
#define FILTER_ASSERT(condition, message) if (!(condition)) {printf(message); free(previous); free(current); free(next); return 1;}

const double gaussMatrix[3][3] = {{1.0 / 9, 1.0 / 9, 1.0 / 9},
                                  {1.0 / 9, 1.0 / 9, 1.0 / 9},
                                  {1.0 / 9, 1.0 / 9, 1.0 / 9}};

// const double sobelxMatrix[3][3] = {{}};
// const double sobelyMatrix[3][3] = {{}};

/// Returns 0 on success, non-zero value otherwise
// TODO: support other platforms
// TODO: somehow split this huge method into smaller ones
// TODO: can processing the last line be merged with the main loop?
// Image is considered to be 2 pixels wider and 2 pixels higher than it actually is,
// forming black outline out of those extra pixels,
// so that gauss filter can be applied.
int applyFilter(uint16_t biBitCount, int32_t biWidth, int32_t biHeight, const double filter[3][3], FILE *fileStreamIn, FILE *fileStreamOut, int platform)
{
    int result;
    int rowSize = (biBitCount * biWidth + 31) / 32 * 4;
    int gap = rowSize - biBitCount / 8 * biWidth;
    char *gapBuffer = NULL;
    if (gap != 0)
    {
        gapBuffer = malloc(sizeof(char) * gap);
    }

    if (platform == LITTLE_ENDIAN && biBitCount == 24)
    {
        // Initialize variables

        // calloc is used instead of malloc so that to make sure
        // that "previuos" line is black initially
        // and other lines' borders are black, too.

        LittleEndianColour24 *previous = calloc((size_t) biWidth + 2, sizeof(LittleEndianColour24));
        LittleEndianColour24 *current = calloc((size_t) biWidth + 2, sizeof(LittleEndianColour24));
        LittleEndianColour24 *next = calloc((size_t) biWidth + 2, sizeof(LittleEndianColour24));

        result = fread(current + 1, sizeof(LittleEndianColour24), (size_t) biWidth, fileStreamIn);
        FILTER_ASSERT(result == biWidth, "Error: could not read image line.\n")

        if (gap != 0)
        {
            result = fread(gapBuffer, sizeof(char), (size_t) gap, fileStreamIn);
            FILTER_ASSERT(result == gap, "Error reading gap between lines.\n")
        }

        // Process lines 1 to last - 1

        for (int i = 1; i < biHeight; i++)
        {
            result = fread(next + 1, sizeof(LittleEndianColour24), (size_t) biWidth, fileStreamIn);
            FILTER_ASSERT(result == biWidth, "Error: could not read image line.\n")

            // Modify i-th line

            for (int j = 1; j < biWidth + 1; j++)
            {
                // Calculate new pixel colour

                RealColour newColour;
                newColour.red = 0;
                newColour.green = 0;
                newColour.blue = 0;
                // newColour.alpha = 0;

                for (int k = 0; k < 3; k++)
                {
                    addToColour(&newColour, multiplyLE24(previous[j + k - 1], filter[0][k]));
                    addToColour(&newColour, multiplyLE24(current[j + k - 1], filter[1][k]));
                    addToColour(&newColour, multiplyLE24(next[j + k - 1], filter[2][k]));
                }

                LittleEndianColour24 savingColour;
                savingColour.red = (unsigned char) newColour.red;
                savingColour.green = (unsigned char) newColour.green;
                savingColour.blue = (unsigned char) newColour.blue;

                // Save new pixel colour

                result = fwrite(&savingColour, sizeof(LittleEndianColour24), 1, fileStreamOut);
                FILTER_ASSERT(result == 1, "Error: could not save image line.")
            }

            // Add current paddig and read next one if necessary
            // Paddings are 0 ususally, but let's keep this file's paddings
            // just in case they are different.

            if (gap != 0)
            {
                result = fwrite(gapBuffer, sizeof(char), (size_t) gap, fileStreamOut);
                FILTER_ASSERT(result == gap, "Error writing to file.\n")

                result = fread(gapBuffer, sizeof(char), (size_t) gap, fileStreamIn);
                FILTER_ASSERT(result == gap, "Error reading file.\n")
            }

            // In order to optimize memory usage, only three lines are kept in RAM

            LittleEndianColour24 *tmp = previous;
            previous = current;
            current = next;
            next = tmp;

            // "next" will be overwritten anyway and doesn't have to be set to contain zeros
        }

        // Process last line

        // Since no next line exists, it is considered to be black

        for (int j = 1; j < biWidth + 1; j++)
        {
            next[j].red = 0;
            next[j].green = 0;
            next[j].blue = 0;
        }

        for (int j = 1; j < biWidth + 1; j++)
        {
            // Clcutate new pixel colour

            RealColour newColour;
            newColour.red = 0;
            newColour.green = 0;
            newColour.blue = 0;
            // newColour.alpha = 0;

            for (int k = 0; k < 3; k++)
            {
                addToColour(&newColour, multiplyLE24(previous[j + k - 1], filter[0][k]));
                addToColour(&newColour, multiplyLE24(current[j + k - 1], filter[1][k]));
                addToColour(&newColour, multiplyLE24(next[j + k - 1], filter[2][k]));
            }

            LittleEndianColour24 savingColour;
            savingColour.red = (unsigned char) newColour.red;
            savingColour.green = (unsigned char) newColour.green;
            savingColour.blue = (unsigned char) newColour.blue;

            // Save pixel colour

            result = fwrite(&savingColour, sizeof(LittleEndianColour24), 1, fileStreamOut);
            FILTER_ASSERT(result == 1, "Error: could not save image line.")
        }

        // Add padding if necessary

        if (gap != 0)
        {
            result = fwrite(gapBuffer, sizeof(char), (size_t) gap, fileStreamOut);
            FILTER_ASSERT(result == gap, "Error writing to file.\n")
        }

        free(previous);
        free(current);
        free(next);
    }
    else if (platform == LITTLE_ENDIAN && biBitCount == 32)
    {
        // Initialize variables

        LittleEndianColour32 *previous = calloc((size_t) biWidth + 2, sizeof(LittleEndianColour32));
        LittleEndianColour32 *current = calloc((size_t) biWidth + 2, sizeof(LittleEndianColour32));
        LittleEndianColour32 *next = calloc((size_t) biWidth + 2, sizeof(LittleEndianColour32));

        result = fread(current + 1, sizeof(LittleEndianColour32), (size_t) biWidth, fileStreamIn);
        FILTER_ASSERT(result == biWidth, "Error: could not read image line.\n")

        // Process lies 1 to last - 1

        for (int i = 1; i < biHeight; i++)
        {
            result = fread(next + 1, sizeof(LittleEndianColour24), (size_t) biWidth, fileStreamIn);
            FILTER_ASSERT(result == biWidth, "Error: could not read image line.\n")

            for (int j = 1; j < biWidth + 1; j++)
            {
                RealColour newColour;
                newColour.red = 0;
                newColour.green = 0;
                newColour.blue = 0;
                newColour.alpha = 0;

                for (int k = 0; k < 3; k++)
                {
                    addToColour(&newColour, multiplyLE32(previous[j + k - 1], filter[0][k]));
                    addToColour(&newColour, multiplyLE32(current[j + k - 1], filter[1][k]));
                    addToColour(&newColour, multiplyLE32(next[j + k - 1], filter[2][k]));
                }

                LittleEndianColour32 savingColour;
                savingColour.red = (unsigned char) newColour.red;
                savingColour.green = (unsigned char) newColour.green;
                savingColour.blue = (unsigned char) newColour.blue;
                savingColour.alpha = (unsigned char) newColour.alpha;

                result = fwrite(&savingColour, sizeof(LittleEndianColour32), 1, fileStreamOut);
                FILTER_ASSERT(result == 1, "Error: could not save image line.")
            }

            if (gap != 0)
            {
                result = fwrite(gapBuffer, sizeof(char), (size_t) gap, fileStreamOut);
                FILTER_ASSERT(result == gap, "Error writing to file.\n")

                result = fread(gapBuffer, sizeof(char), (size_t) gap, fileStreamIn);
                FILTER_ASSERT(result == gap, "Error reading file.\n")
            }

            LittleEndianColour32 *tmp = previous;
            previous = current;
            current = next;
            next = tmp;
        }

        // Process last line

        for (int j = 1; j < biWidth + 1; j++)
        {
            next[j].red = 0;
            next[j].green = 0;
            next[j].blue = 0;
            next[j].alpha = 0;
        }

        /// =========

        for (int j = 1; j < biWidth + 1; j++)
        {
            RealColour newColour;
            newColour.red = 0;
            newColour.green = 0;
            newColour.blue = 0;
            newColour.alpha = 0;

            for (int k = 0; k < 3; k++)
            {
                addToColour(&newColour, multiplyLE32(previous[j + k - 1], filter[0][k]));
                addToColour(&newColour, multiplyLE32(current[j + k - 1], filter[1][k]));
                addToColour(&newColour, multiplyLE32(next[j + k - 1], filter[2][k]));
            }

            LittleEndianColour32 savingColour;
            savingColour.red = (unsigned char) newColour.red;
            savingColour.green = (unsigned char) newColour.green;
            savingColour.blue = (unsigned char) newColour.blue;
            savingColour.alpha = (unsigned char) newColour.alpha;

            result = fwrite(&savingColour, sizeof(LittleEndianColour24), 1, fileStreamOut);
            FILTER_ASSERT(result == 1, "Error: could not save image line.")

            LittleEndianColour32 *tmp = previous;
            previous = current;
            current = next;
            next = tmp;
        }

        if (gap != 0)
        {
            result = fwrite(gapBuffer, sizeof(char), (size_t) gap, fileStreamOut);
            FILTER_ASSERT(result == gap, "Error writing to file.\n")

            result = fread(gapBuffer, sizeof(char), (size_t) gap, fileStreamIn);
            FILTER_ASSERT(result == gap, "Error reading file.\n")
        }

        char c;
        FILTER_ASSERT(fread(&c, sizeof(char), 1, fileStreamOut), "Error: file contains more data than expected.\n")

        /// =========

        free(previous);
        free(current);
        free(next);
    }
    else if (platform == BIG_ENDIAN && biBitCount == 24)
    {
        BigEndianColour24 *previous = calloc((size_t) biWidth + 2, sizeof(BigEndianColour24));
        BigEndianColour24 *current = calloc((size_t) biWidth + 2, sizeof(BigEndianColour24));
        BigEndianColour24 *next = calloc((size_t) biWidth + 2, sizeof(BigEndianColour24));

        free(previous);
        free(current);
        free(next);

    }
    else // platform == BIG_ENDIAN && bitCount == 32
    {
        BigEndianColour32 *previous = calloc((size_t) biWidth + 2, sizeof(BigEndianColour32));
        BigEndianColour32 *current = calloc((size_t) biWidth + 2, sizeof(BigEndianColour32));
        BigEndianColour32 *next = calloc((size_t) biWidth + 2, sizeof(BigEndianColour32));

        free(previous);
        free(current);
        free(next);
    }
    if (gap != 0)
    {
        free(gapBuffer);
    }
    return 0;
}

int main(int argc, char **argv)
{
    char *s; // Argument passed after -s, source file path
    char *f; // Argument passed after -f, filter type
    char *o; // Argument passed after -o, destination file path

    if (handleArguments(argc, argv, &s, &f, &o))
        return 1;

    FILE *fileStreamIn = fopen(s, "rb");
    FILE *fileStreamOut = fopen(o, "wb");

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

    // I am uncertain whether it is good or not to write conditions like this one.
    // Welllll, it is beautiful, isn't it?
    if (
            handleBitmapFileHeader(fileStreamIn, &bfType, &bfSize, &bfReserved1, &bfReserved2, &bfOffBits, &platform) ||
            handleBitmapInfoHeader(fileStreamIn, &biSize, &biWidth, &biHeight, &biPlains, &biBitCount) ||
            checkSizes(bfSize, bfOffBits, biSize, biWidth, biHeight, biBitCount) ||
            // I know using fseek is a bad thing to do, but I use fseek just once, what can possibly go wrong?
            fseek(fileStreamIn, 0, SEEK_SET) ||
            copyHeader(fileStreamIn, fileStreamOut, bfOffBits)
    )
    {
        MAIN_ERROR();
    }

    if (!strcmp(f, gauss))
    {
        printf("Working...\n");
        if (applyFilter(biBitCount, biWidth, biHeight, gaussMatrix, fileStreamIn, fileStreamOut, platform))
        {
            MAIN_ERROR();
        }
    }
    else if (!strcmp(f, sobelx))
    {
        printf("Modify as sobelx NYI\n");
//        if (applyFilter(biBitCount, biWidth, biHeight, fileStreamIn, sobelxMatrix))
//        {
//            MAIN_ERROR();
//        }
    }
    else if (!strcmp(f, sobely))
    {
        printf("Modify as sobely NYI\n");
//        if (applyFilter(biBitCount, biWidth, biHeight, fileStreamIn, sobelyMatrix))
//        {
//            MAIN_ERROR();
//        }
    }
    else // It has already been checked that f falls into one of these categories
    {
        printf("Modify with greying NYI\n");
//        if (applyFilter(biBitCount, biWidth, biHeight, fileStreamIn, greyingMatrix))
//        {
//            MAIN_ERROR();
//        }
    }

    fclose(fileStreamIn);
    fclose(fileStreamOut);
    printf("Done.\n");
    getchar();
    return 0;
}
