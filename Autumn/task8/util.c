#include <stdio.h>
#include <malloc.h>
#include <mem.h>

#include "util.h"

const char *gauss = "gauss";
const char *sobelx = "sobelx";
const char *sobely = "sobely";
const char *greyen = "greyen";

int confirm(char *message)
{
    while (1)
    {
        printf(message);
        char answer = (char) getchar();
        if (answer == 'y' || answer == 'Y')
        {
            while (getchar() != '\n');
            return 1;
        }
        else if (answer == 'N' || answer == 'n')
        {
            while (getchar() != '\n');
            return 0;
        }
        else if (answer != '\n')
            while (getchar() != '\n');
    }
}

int exists(const char *fileName, const char *mode)
{
    FILE *file = fopen(fileName, mode);
    return !fclose(file);
}

int choose(const char *type, char *value, char **s, char **f, char **o)
{
    if (type[1] == 's' && type[2] == '\0')
    {
        if (*s == NULL)
        {
            *s = value;
            return 0;
        }
        printf("Error: -s value provided more than once.\n");
        return 1;
    }
    else if (type[1] == 'f' && type[2] == '\0')
    {
        if (*f == NULL)
        {
            *f = value;
            return 0;
        }
        printf("Error: -f value provided more than once.\n");
        return 1;
    }
    else if (type[1] == 'o' && type[2] == '\0')
    {
        if (*o == NULL)
        {
            *o = value;
            return 0;
        }
        printf("Error: -o value provided more than once.\n");
        return 1;
    }
    printf("Error: \"%s\" is unknown argument specifier.\n", value);
    return 1;
}

int handleArguments(int argc, char **argv, char **s, char **f, char **o)
{
    *s = NULL;
    *f = NULL;
    *o = NULL;
    int i = 1;
    while (i < argc)
    {
        if (argv[i][0] == '-')
        {
            if (i + 1 == argc || argv[i + 1][0] == '-')
            {
                printf("Error: no value is provided after \"%s\".\n", argv[i]);
                return 1;
            }
            if (choose(argv[i], argv[i + 1], s, f, o))
                return 1; // choose() will have already printf'ed error type
            i += 2;
        }
        else
        {
            printf("Error: argument \"%s\" provided without type specifier.\n", argv[i]);
            return 1;
        }
    }

    if (*s == NULL)
    {
        printf("Error: source file not provided.\n");
        return 1;
    }
    if (!exists(*s, "rb"))
    {
        printf("Error: source file doesn't exist.\n");
        return 1;
    }
    if (*o == NULL)
    {
        printf("Error: destination file not provided.\n");
        return 1;
    }
    if (exists(*o, "rb") && !confirm("Warning: destination file already exists. Proceed anyway? [Y/n]: "))
    {
        printf("Abort.\n");
        return 1;
    }
    if (!exists(*o, "wb"))
    {
        printf("Error: couldn't create destination file.\n");
        return 1;
    }
    if (*f == NULL)
    {
        printf("Error: filter type not provided.\n");
        return 1;
    }
    if (strcmp(*f, gauss) != 0 && strcmp(*f, sobelx) != 0 && strcmp(*f, sobely) != 0 && strcmp(*f, greyen) != 0)
    {
        printf("Error: unknown filter type: \"%s\"", *f);
        return 1;
    }
    return 0;
}

int handleBitmapFileHeader(FILE *fileStreamIn, uint16_t *bfType, uint32_t *bfSize, uint16_t *bfReserved1, uint16_t *bfReserved2, uint32_t *bfOffBits, int *platform)
{
    if (!fread(bfType, 2, 1, fileStreamIn))
    {
        printf("Error: could not read file header.\n");
        return 1;
    }
    if (*bfType == 0x4D42)
    {
        *platform = LITTLE_ENDIAN;
    }
    else if (*bfType == 0x424D)
    {
        *platform = BIG_ENDIAN;
    }
    else
    {
        printf("Error: file doesn't start with a valid bmp header.\n");
        printf("Header expected: 4D42 or 424D.\n");
        printf("Header found: %02X", *bfType);
        return 1;
    }

    if (!fread(bfSize, 4, 1, fileStreamIn))
    {
        printf("Error: could not read file size.\n");
        return 1;
    }

    if (!fread(bfReserved1, 2, 1, fileStreamIn) || !fread(bfReserved2, 2, 1, fileStreamIn))
    {
        printf("Error: could not read reserved areas.\n");
        return 1;
    }
    if (*bfReserved1 || *bfReserved2)
    {
        printf("Error: reserved regions contain non-zero value.\n");
        return 1;
    }

    if (!fread(bfOffBits, 4, 1, fileStreamIn))
    {
        printf("Error: could not read data offset.\n");
        return 1;
    }
    return 0;
}

int
handleBitmapInfoHeader(FILE *fileStreamIn, uint32_t *biSize, int32_t *biWidth, int32_t *biHeight, uint16_t *biPlains, uint16_t *biBitCount)
{
    if (!fread(biSize, 4, 1, fileStreamIn))
    {
        printf("Error: could not read bitmap-info-header size.\n");
        return 1;
    }

    // "BITMAPCOREHEADER" format is also supported
    if (*biSize == 12)
    {
        uint16_t bcWidth;
        uint16_t bcHeight;

        if (!fread(&bcWidth, 2, 1, fileStreamIn) || !fread(&bcHeight, 2, 1, fileStreamIn))
        {
            printf("Error: could not read file dimensions.\n");
            return 1;
        }

        *biWidth = (int32_t) bcWidth;
        *biHeight = (int32_t) bcHeight;
    }
    else if (*biSize < 16)
    {
        printf("Error: unexpected info header size: \"%d\"", *biSize);
        return 1;
    }
    else
    {
        if (!fread(biWidth, 4, 1, fileStreamIn) || !fread(biHeight, 4, 1, fileStreamIn))
        {
            printf("Error: could not read file dimensions.\n");
            return 1;
        }
    }

    if (*biWidth <= 0 || *biHeight <= 0)
    {
        printf("Error: found non-positive values for image dimensions.\n");
        return 0;
    }

    if (!fread(biPlains, 2, 1, fileStreamIn))
    {
        printf("Error: could not read colour planes number.\n");
        return 1;
    }

    if (*biPlains != 1)
    {
        printf("Error: unexpected number of colour planes: \"%d\".\n", *biPlains);
        return 1;
    }

    if (!fread(biBitCount, 2, 1, fileStreamIn))
    {
        printf("Error: could not read bit per pixel count.\n");
        return 1;
    }
    return 0;
}

int checkSizes(uint32_t bfSize, uint32_t bfOffBits, uint32_t biSize, int32_t biWidth, int32_t biHeight, uint16_t biBitCount)
{
    if (bfOffBits < BITMAP_FILE_HEADER_SIZE + biSize)
    {
        printf("Error: file contents are not valid: data offset is less that total length of headers.\n");
        return 1;
    }
    if (biBitCount != 24 && biBitCount != 32)
    {
        printf("Error: images with \"%d\" bits per pixel are not supported.\n", biBitCount);
        return 1;
    }
    int rowSize = (biBitCount * biWidth + 31) / 32 * 4;
    if (rowSize * biHeight + bfOffBits != bfSize)
    {
        printf("Error: file size doesn't match declared data.\n");
        return 1;
    }
    if (biHeight <= 2)
    {
        printf("Error: image height is too small to apply filters.\n");
        return 1;
    }
    return 0;
}

int copyHeader(FILE *fileStreamIn, FILE *fileStreamOut, uint32_t headerSize)
{
    int result;
    char *headerBuf = malloc(sizeof(char) * headerSize);

    result = fread(headerBuf, sizeof(char), headerSize, fileStreamIn);
    if (result != headerSize)
    {
        free(headerBuf);
        printf("Error reading file header.");
        return 1;
    }

    result = fwrite(headerBuf, sizeof(char), headerSize, fileStreamOut);
    if (result != headerSize)
    {
        free(headerBuf);
        printf("Error copying file header.\n");
        return 1;
    }

    free(headerBuf);
    return 0;
}

int applyFilter(uint16_t biBitCount, int32_t biWidth, int32_t biHeight, const double (*filter)[3], FILE *fileStreamIn, FILE *fileStreamOut, int platform)
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

        // Process all lines

        for (int i = 1; i < biHeight + 1; i++)
        {
            if (i < biHeight)
            {
                result = fread(next + 1, sizeof(LittleEndianColour24), (size_t) biWidth, fileStreamIn);
                FILTER_ASSERT(result == biWidth, "Error: could not read image line.\n")
            }
            else
            {
                // Since no next line really exists, it is considered to be black
                for (int j = 1; j < biWidth + 1; j++)
                {
                    next[j].red = 0;
                    next[j].green = 0;
                    next[j].blue = 0;
                }
            }

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

            if (gap != 0)
            {
                result = fwrite(gapBuffer, sizeof(char), (size_t) gap, fileStreamOut);
                FILTER_ASSERT(result == gap, "Error writing to file.\n")

                if (i < biHeight)
                {
                    result = fread(gapBuffer, sizeof(char), (size_t) gap, fileStreamIn);
                    FILTER_ASSERT(result == gap, "Error reading file.\n")
                }
            }

            // In order to optimize memory usage, only three lines are kept in RAM

            LittleEndianColour24 *tmp = previous;
            previous = current;
            current = next;
            next = tmp;

            // "next" will be overwritten anyway and doesn't have to be set to contain zeros
        }

        free(previous);
        free(current);
        free(next);
    }
    else if (platform == LITTLE_ENDIAN && biBitCount == 32)
    {
        // Initialize variables

        // calloc is used instead of malloc so that to make sure
        // that "previuos" line is black initially
        // and other lines' borders are black, too.

        LittleEndianColour32 *previous = calloc((size_t) biWidth + 2, sizeof(LittleEndianColour32));
        LittleEndianColour32 *current = calloc((size_t) biWidth + 2, sizeof(LittleEndianColour32));
        LittleEndianColour32 *next = calloc((size_t) biWidth + 2, sizeof(LittleEndianColour32));

        result = fread(current + 1, sizeof(LittleEndianColour32), (size_t) biWidth, fileStreamIn);
        FILTER_ASSERT(result == biWidth, "Error: could not read image line.\n")

        if (gap != 0)
        {
            result = fread(gapBuffer, sizeof(char), (size_t) gap, fileStreamIn);
            FILTER_ASSERT(result == gap, "Error reading gap between lines.\n")
        }

        // Process all lines

        for (int i = 1; i < biHeight + 1; i++)
        {
            if (i < biHeight)
            {
                result = fread(next + 1, sizeof(LittleEndianColour32), (size_t) biWidth, fileStreamIn);
                FILTER_ASSERT(result == biWidth, "Error: could not read image line.\n")
            }
            else
            {
                // Since no next line really exists, it is considered to be black
                for (int j = 1; j < biWidth + 1; j++)
                {
                    next[j].red = 0;
                    next[j].green = 0;
                    next[j].blue = 0;
                    next[j].alpha = 0;
                }
            }

            // Modify i-th line

            for (int j = 1; j < biWidth + 1; j++)
            {
                // Calculate new pixel colour

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

                // Save new pixel colour

                result = fwrite(&savingColour, sizeof(LittleEndianColour32), 1, fileStreamOut);
                FILTER_ASSERT(result == 1, "Error: could not save image line.")
            }

            // Add current paddig and read next one if necessary

            if (gap != 0)
            {
                result = fwrite(gapBuffer, sizeof(char), (size_t) gap, fileStreamOut);
                FILTER_ASSERT(result == gap, "Error writing to file.\n")

                if (i < biHeight)
                {
                    result = fread(gapBuffer, sizeof(char), (size_t) gap, fileStreamIn);
                    FILTER_ASSERT(result == gap, "Error reading file.\n")
                }
            }

            // In order to optimize memory usage, only three lines are kept in RAM

            LittleEndianColour32 *tmp = previous;
            previous = current;
            current = next;
            next = tmp;

            // "next" will be overwritten anyway and doesn't have to be set to contain zeros
        }

        free(previous);
        free(current);
        free(next);
    }
    else if (platform == BIG_ENDIAN && biBitCount == 24)
    {
        // Initialize variables

        // calloc is used instead of malloc so that to make sure
        // that "previuos" line is black initially
        // and other lines' borders are black, too.

        BigEndianColour24 *previous = calloc((size_t) biWidth + 2, sizeof(BigEndianColour24));
        BigEndianColour24 *current = calloc((size_t) biWidth + 2, sizeof(BigEndianColour24));
        BigEndianColour24 *next = calloc((size_t) biWidth + 2, sizeof(BigEndianColour24));

        result = fread(current + 1, sizeof(BigEndianColour24), (size_t) biWidth, fileStreamIn);
        FILTER_ASSERT(result == biWidth, "Error: could not read image line.\n")

        if (gap != 0)
        {
            result = fread(gapBuffer, sizeof(char), (size_t) gap, fileStreamIn);
            FILTER_ASSERT(result == gap, "Error reading gap between lines.\n")
        }

        // Process all lines

        for (int i = 1; i < biHeight + 1; i++)
        {
            if (i < biHeight)
            {
                result = fread(next + 1, sizeof(BigEndianColour24), (size_t) biWidth, fileStreamIn);
                FILTER_ASSERT(result == biWidth, "Error: could not read image line.\n")
            }
            else
            {
                // Since no next line really exists, it is considered to be black
                for (int j = 1; j < biWidth + 1; j++)
                {
                    next[j].red = 0;
                    next[j].green = 0;
                    next[j].blue = 0;
                }
            }

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
                    addToColour(&newColour, multiplyBE24(previous[j + k - 1], filter[0][k]));
                    addToColour(&newColour, multiplyBE24(current[j + k - 1], filter[1][k]));
                    addToColour(&newColour, multiplyBE24(next[j + k - 1], filter[2][k]));
                }

                BigEndianColour24 savingColour;
                savingColour.red = (unsigned char) newColour.red;
                savingColour.green = (unsigned char) newColour.green;
                savingColour.blue = (unsigned char) newColour.blue;

                // Save new pixel colour

                result = fwrite(&savingColour, sizeof(BigEndianColour24), 1, fileStreamOut);
                FILTER_ASSERT(result == 1, "Error: could not save image line.")
            }

            // Add current paddig and read next one if necessary

            if (gap != 0)
            {
                result = fwrite(gapBuffer, sizeof(char), (size_t) gap, fileStreamOut);
                FILTER_ASSERT(result == gap, "Error writing to file.\n")

                if (i < biHeight)
                {
                    result = fread(gapBuffer, sizeof(char), (size_t) gap, fileStreamIn);
                    FILTER_ASSERT(result == gap, "Error reading file.\n")
                }
            }

            // In order to optimize memory usage, only three lines are kept in RAM

            BigEndianColour24 *tmp = previous;
            previous = current;
            current = next;
            next = tmp;

            // "next" will be overwritten anyway and doesn't have to be set to contain zeros
        }

        free(previous);
        free(current);
        free(next);
    }
    else // platform == BIG_ENDIAN && bitCount == 32
    {
        // Initialize variables

        // calloc is used instead of malloc so that to make sure
        // that "previuos" line is black initially
        // and other lines' borders are black, too.

        BigEndianColour32 *previous = calloc((size_t) biWidth + 2, sizeof(BigEndianColour32));
        BigEndianColour32 *current = calloc((size_t) biWidth + 2, sizeof(BigEndianColour32));
        BigEndianColour32 *next = calloc((size_t) biWidth + 2, sizeof(BigEndianColour32));

        result = fread(current + 1, sizeof(BigEndianColour32), (size_t) biWidth, fileStreamIn);
        FILTER_ASSERT(result == biWidth, "Error: could not read image line.\n")

        if (gap != 0)
        {
            result = fread(gapBuffer, sizeof(char), (size_t) gap, fileStreamIn);
            FILTER_ASSERT(result == gap, "Error reading gap between lines.\n")
        }

        // Process all lines

        for (int i = 1; i < biHeight + 1; i++)
        {
            if (i < biHeight)
            {
                result = fread(next + 1, sizeof(BigEndianColour32), (size_t) biWidth, fileStreamIn);
                FILTER_ASSERT(result == biWidth, "Error: could not read image line.\n")
            }
            else
            {
                // Since no next line really exists, it is considered to be black
                for (int j = 1; j < biWidth + 1; j++)
                {
                    next[j].red = 0;
                    next[j].green = 0;
                    next[j].blue = 0;
                    next[j].alpha = 0;
                }
            }

            // Modify i-th line

            for (int j = 1; j < biWidth + 1; j++)
            {
                // Calculate new pixel colour

                RealColour newColour;
                newColour.red = 0;
                newColour.green = 0;
                newColour.blue = 0;
                newColour.alpha = 0;

                for (int k = 0; k < 3; k++)
                {
                    addToColour(&newColour, multiplyBE32(previous[j + k - 1], filter[0][k]));
                    addToColour(&newColour, multiplyBE32(current[j + k - 1], filter[1][k]));
                    addToColour(&newColour, multiplyBE32(next[j + k - 1], filter[2][k]));
                }

                BigEndianColour32 savingColour;
                savingColour.red = (unsigned char) newColour.red;
                savingColour.green = (unsigned char) newColour.green;
                savingColour.blue = (unsigned char) newColour.blue;
                savingColour.alpha = (unsigned char) newColour.alpha;

                // Save new pixel colour

                result = fwrite(&savingColour, sizeof(BigEndianColour32), 1, fileStreamOut);
                FILTER_ASSERT(result == 1, "Error: could not save image line.")
            }

            // Add current paddig and read next one if necessary

            if (gap != 0)
            {
                result = fwrite(gapBuffer, sizeof(char), (size_t) gap, fileStreamOut);
                FILTER_ASSERT(result == gap, "Error writing to file.\n")

                if (i < biHeight)
                {
                    result = fread(gapBuffer, sizeof(char), (size_t) gap, fileStreamIn);
                    FILTER_ASSERT(result == gap, "Error reading file.\n")
                }
            }

            // In order to optimize memory usage, only three lines are kept in RAM

            BigEndianColour32 *tmp = previous;
            previous = current;
            current = next;
            next = tmp;

            // "next" will be overwritten anyway and doesn't have to be set to contain zeros
        }

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
