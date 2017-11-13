#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/filters.h"
#include "../headers/bmp.h"


int main(int argc, char *argv[])
{
    int returnCode = 0;
    FILE *input = NULL, *output = NULL;
    long fPos = 0;

    if (argc == 1)
    {
        printf("It is not specified what to do. See --help to get usage.\n");
        returnCode = 1; goto end;
    }
    else if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        printf(
            "#----------------------------- BEGIN OF USAGE -----------------------------#\n"
            "| Program provides operations with 24- or 32-bit .bmp files. It takes      |\n"
            "| input image, performs specified filter and creates new changed output    |\n"
            "| image.                                                                   |\n"
            "|   Syntax:                                                                |\n"
            "|     filter.exe <action> <input_file> [output_file]                       |\n"
            "|   where                                                                  |\n"
            "|   * <action>                                                             |\n"
            "|       is one of the following long flags:                                |\n"
            "|         --median=3x3   # applies median 3x3 filter to the image          |\n"
            "|         --median=5x5   # applies median 5x5 filter to the image          |\n"
            "|         --gaussian=3x3 # applies gaussian 3x3 filter to the image        |\n"
            "|         --gaussian=5x5 # applies gaussian 5x5 filter to the image        |\n"
            "|         --sobel        # applies sobel operator to the image             |\n"
            "|         --sobelX       # applies sobel horizontal operator to the image  |\n"
            "|         --sobelY       # applies sobel vertical operator to the image    |\n"
            "|         --scharr       # applies scharr operator to the image            |\n"
            "|         --scharrX      # applies scharr horizontal operator to the image |\n"
            "|         --scharrY      # applies scharr vertical operator to the image   |\n"
            "|         --whiteblack   # builds monochrome image                         |\n"
            "|         --help         # prints this info. Mustn't be followed by any    |\n"
            "|                        # flags                                           |\n"
            "|   * <input_file>                                                         |\n"
            "|       is input file name (or relative path)                              |\n"
            "|   * [output_file]                                                        |\n"
            "|       is output file name (or relative path). It is set 'output.bmp'     |\n"
            "|       by default.                                                        |\n"
            "#----------------------------- END OF USAGE -------------------------------#\n"
        );
    }
    else if (argc == 3 || argc == 4)
    {
        enum Filter filter;

        if (strcmp(argv[1], "--median=3x3") == 0)
            filter = MEDIAN_3_X_3;
        else if (strcmp(argv[1], "--median=5x5") == 0)
            filter = MEDIAN_5_X_5;
        else if (strcmp(argv[1], "--gaussian=3x3") == 0)
            filter = GAUSSIAN_3_X_3;
        else if (strcmp(argv[1], "--gaussian=5x5") == 0)
            filter = GAUSSIAN_5_X_5;
        else if (strcmp(argv[1], "--sobel") == 0)
            filter = SOBEL;
        else if (strcmp(argv[1], "--sobel=X") == 0)
            filter = SOBEL_X;
        else if (strcmp(argv[1], "--sobel=Y") == 0)
            filter = SOBEL_Y;
        else if (strcmp(argv[1], "--scharr") == 0)
            filter = SCHARR;
        else if (strcmp(argv[1], "--scharr=X") == 0)
            filter = SCHARR_X;
        else if (strcmp(argv[1], "--scharr=Y") == 0)
            filter = SCHARR_Y;
        else if (strcmp(argv[1], "--whiteblack") == 0)
            filter = WHITE_BLACK_MODE;
        else
        {
            printf("Incorrect action: %s. See usage by --help for help.\n", argv[1]);
            returnCode = 1; goto end;
        }

        if ((input = fopen(argv[2], "rb")) == NULL)
        {
            printf("Error: Input file %s does not exist.\n", argv[2]);
            returnCode = 1; goto end;
        }

        if ((output = fopen(argc == 4 ? argv[3] : "output.bmp", "wb+")) == NULL)
        {
            printf(
                "Error: It is impossible to create or rewrite output file %s. "
                "Perhaps it is not enough rights.\n",
                argc == 4 ? argv[3] : "output.bmp"
            );
            returnCode = 1; goto end;
        }

        BitMapFileHeader bitMapFileHeader;
        BitMapInfoHeader bitMapInfoHeader;

        fread(&bitMapFileHeader, sizeof(BitMapFileHeader), 1, input);
        fread(&bitMapInfoHeader, sizeof(BitMapInfoHeader), 1, input);

        if (bitMapInfoHeader.biBitCount != 24 && bitMapInfoHeader.biBitCount != 32)
        {
            printf("Sorry, program works just with 24- or 32-bits .bmp files. This file is %d bits.\n",
                   bitMapInfoHeader.biBitCount);
            returnCode = 1; goto end;
        }

        // Kill the palette if it exists
        fPos = ftell(input);
        fseek(input, bitMapFileHeader.bfOffBits, SEEK_SET);
        bitMapFileHeader.bfOffBits = (dword) fPos;

        BGRMap inputMap;
        BGRMap outputMap;

        initBGRMap(bitMapInfoHeader.biHeight, bitMapInfoHeader.biWidth, &inputMap);
        initBGRMap(bitMapInfoHeader.biHeight, bitMapInfoHeader.biWidth, &outputMap);

        forwardPixel readPixel = bitMapInfoHeader.biBitCount == 24 ? readPixel24Bit : readPixel32Bit;

        for (int i = 0; i < inputMap.h; ++i)
        {
            for (int j = 0; j < inputMap.w; ++j)
                readPixel(input, &inputMap.map[i][j]);

            // skip empty bytes which complete line so it length would divided into 4 (.BMP format rule)
            if (bitMapInfoHeader.biBitCount == 24)
                for (int k = 0; k < 3 * outputMap.w % 4; ++k)
                    fgetc(input);
        }

        applyFilter(&inputMap, &outputMap, filter);

        fwrite(&bitMapFileHeader, sizeof(BitMapFileHeader), 1, output);
        fwrite(&bitMapInfoHeader, sizeof(BitMapInfoHeader), 1, output);

        forwardPixel writePixel = bitMapInfoHeader.biBitCount == 24 ? writePixel24Bit : writePixel32Bit;

        for (int i = 0; i < outputMap.h; ++i)
        {
            for (int j = 0; j < outputMap.w; ++j)
                writePixel(output, &outputMap.map[i][j]);

            // write empty bytes to complete line so it length would divided into 4 (.BMP format rule)
            if (bitMapInfoHeader.biBitCount == 24)
            {
                for (int k = 0; k < 3 * outputMap.w % 4; ++k)
                    fputc(0, output);
            }

        }
    }
    else
    {
        printf("Wrong usage. See usage by --help for help.\n");
        returnCode = 1; goto end;
    }

    end:

    fclose(input);
    fclose(output);

    return returnCode;
}