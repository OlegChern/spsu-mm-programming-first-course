#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "util.h"

const char *gauss = "gauss";
const char *sobelx = "sobelx";
const char *sobely = "sobely";
const char *greyen = "greyen";

unsigned char toByte(double value)
{
    if (value < 0)
    {
        return 0;
    }
    if (value > 255)
    {
        return 255;
    }
    return (unsigned char) value;
}

unsigned char absToByte(double value)
{
    if (abs((int)  value) > 255)
    {
        return 255;
    }
    return (unsigned char) abs((int) value);
}

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

int choose(const char *type, char *value, char **source, char **filter, char **destination)
{
    if (type[1] == 'i' && type[2] == '\0')
    {
        if (*source == NULL)
        {
            *source = value;
            return 0;
        }
        printf("Error: -i parameter provided more than once.\n");
        return 1;
    }
    else if (type[1] == 'f' && type[2] == '\0')
    {
        if (*filter == NULL)
        {
            *filter = value;
            return 0;
        }
        printf("Error: -f parameter provided more than once.\n");
        return 1;
    }
    else if (type[1] == 'o' && type[2] == '\0')
    {
        if (*destination == NULL)
        {
            *destination = value;
            return 0;
        }
        printf("Error: -o parameter provided more than once.\n");
        return 1;
    }
    printf("Error: \"%s\" is unknown argument specifier.\n", value);
    return 1;
}

int handleArguments(int argc, char **argv, char **source, char **filter, char **destination)
{
    *source = NULL;
    *filter = NULL;
    *destination = NULL;
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
            if (choose(argv[i], argv[i + 1], source, filter, destination))
                return 1; // choose() will have already printf'ed error type
            i += 2;
        }
        else
        {
            printf("Error: argument \"%s\" provided without type specifier.\n", argv[i]);
            return 1;
        }
    }

    if (*source == NULL)
    {
        printf("Error: source file not provided.\n");
        return 1;
    }
    if (*destination == NULL)
    {
        printf("Error: destination file not provided.\n");
        return 1;
    }
    if (*filter == NULL)
    {
        printf("Error: filter type not provided.\n");
        return 1;
    }

    printf("Selected filter: \"%s\"\n", *filter);
    printf("Source file path: \"%s\"\n", *source);
    printf("Destination file path: \"%s\"\n", *destination);

    if (!exists(*source, "rb"))
    {
        printf("Error: source file doesn't exist.\n");
        return 1;
    }
    if (strcmp(*filter, gauss) != 0 && strcmp(*filter, sobelx) != 0 && strcmp(*filter, sobely) != 0 && strcmp(*filter, greyen) != 0)
    {
        printf("Error: unknown filter type: \"%s\"", *filter);
        return 1;
    }
    if (exists(*destination, "rb"))
    {
        if (strcmp(*source, *destination) == 0)
        {
            printf("Error: destination file path is equal to source file path.\n");
            return 1;
        }
        printf("Warning: destination file already exists.\n");

    }
    if (!confirm("Proceed? [Y/n]: "))
    {
        printf("Abort.\n");
        return 1;
    }

    if (!exists(*destination, "wb"))
    {
        printf("Error: couldn't write to destination file.\n");
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

int handleBitmapInfoHeader(FILE *fileStreamIn, uint32_t *biSize, int32_t *biWidth, int32_t *biHeight, uint16_t *biPlains, uint16_t *biBitCount)
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

// Image is considered to be 2 pixels wider and 2 pixels higher than it actually is,
// forming black outline out of those extra pixels,
// so that 3x3 kernel can be applied.

// Might it be faster to use the fact that
// line length in file should always be a multiple of 4 bytes,
// merging lines with gaps and viewing them as (uint32_t*)?

int applyKernel(uint16_t biBitCount, int32_t biWidth, int32_t biHeight, const double kernel[3][3],
                FILE *fileStreamIn, FILE *fileStreamOut, unsigned char (*castFunction)(double))
{
    int result;
    size_t bytesPerPixel = (size_t)  biBitCount / 8;
    int rowSize = (biBitCount * biWidth + 31) / 32 * 4;

    // Line length in file should always be a multiple of 4 bytes.
    // Hence, gap sometimes has to be added.

    int gap = rowSize - bytesPerPixel * biWidth;
    char *gapBuffer = NULL;
    if (gap != 0)
    {
        gapBuffer = malloc(sizeof(char) * gap);
    }

    // Initialize variables

    // Following arrays contain lines of bytes as stored in file
    // They also provide buffers of 1 black pixel in the beginning and end
    // so that kernel can be propperly applied.
    // They don't contain any space for gap

    unsigned char *previous = calloc(sizeof(unsigned char), bytesPerPixel * (biWidth + 2));
    // Since no previous line exists, let it be black.
    // calloc is more efficient than malloc + manually setting colours to black
    unsigned char *current = malloc(sizeof(unsigned char) * bytesPerPixel * (biWidth + 2));
    unsigned char *next = malloc(sizeof(unsigned char) * bytesPerPixel * (biWidth + 2));

    // Make sure buffer pixels of current and next are black
    // (pixels of previous are all black anyway)

    for (int i = 0; i < bytesPerPixel; i++)
    {
        // Pixel at the start...
        current[i] = 0;
        next[i] = 0;
        // ...and at the end.
        current[bytesPerPixel * (biWidth + 1) + i] = 0;
        next[bytesPerPixel * (biWidth + 1) + i] = 0;
    }

    // Read first line (and it's gap if necessary).

    result = fread(current + bytesPerPixel, sizeof(unsigned char), bytesPerPixel * biWidth, fileStreamIn);
    FILTER_ASSERT(result == bytesPerPixel * biWidth, "Error reading image line.\n")

    if (gap != 0)
    {
        result = fread(gapBuffer, sizeof(unsigned char), (size_t) gap, fileStreamIn);
        FILTER_ASSERT(result == gap, "Error reading line gap.\n")
    }

    // Now, apply kernel to lines.

    for (int i = 0; i < biHeight; i++)
    {
        // Read next line
        // Or clear it, if the image is over

        if (i != biHeight - 1)
        {
            result = fread(next + bytesPerPixel, sizeof(unsigned char), bytesPerPixel * biWidth, fileStreamIn);
            FILTER_ASSERT(result == bytesPerPixel * biWidth, "Error reading image line.\n")
        }
        else
        {
            for (int j = bytesPerPixel; j < bytesPerPixel * (biWidth + 1); j++)
            {
                next[j] = 0;
            }
            // next[j] for other j's are 0 anyay
        }

        // Apply kernel
        // In fact, we don't have to care which byte means what,
        // we can work with all ow them in the same way.

        for (int j = bytesPerPixel; j < bytesPerPixel * (biWidth + 1); j++)
        {
            // previous[j - bytesPerPixel], previous[j], previous[j + bytesPerPixel],
            // current[j - bytesPerPixel],  current[j],  current[j + bytesPerPixel],
            // next[j - bytesPerPixel],     next[j],     next[j + bytesPerPixel].

            // We don't need to know which value exactly it represents
            double newValue =
                    kernel[0][0] * previous[j - bytesPerPixel] +
                    kernel[0][1] * previous[j] +
                    kernel[0][2] * previous[j + bytesPerPixel] +

                    kernel[1][0] * current[j - bytesPerPixel] +
                    kernel[1][1] * current[j] +
                    kernel[1][2] * current[j + bytesPerPixel] +

                    kernel[2][0] * next[j - bytesPerPixel] +
                    kernel[2][1] * next[j] +
                    kernel[2][2] * next[j + bytesPerPixel];

            unsigned char newByte = (*castFunction)(newValue);

            result = fwrite(&newByte, sizeof(unsigned char), 1, fileStreamOut);
            FILTER_ASSERT(result == 1, "Error saving image line.\n")
        }

        // Read & write gap if necessary

        if (gap != 0)
        {
            result = fwrite(gapBuffer, sizeof(unsigned char), (size_t) gap, fileStreamOut);
            FILTER_ASSERT(result == gap, "Error saving line gap.\n")

            if (i != biHeight - 1)
            {
                // This gap can't and doesn't have to be read
                // Since {next} is currently just a black buffer
                result = fread(gapBuffer, sizeof(unsigned char), (size_t) gap, fileStreamIn);
                FILTER_ASSERT(result == gap, "Error reading line gap.\n")
            }
        }

        // Swap lines.
        // {next} doesn't have to be cleared
        // since its contents are going to be overwritten anyway

        unsigned char *tmp = previous;
        previous = current;
        current = next;
        next = tmp;
    }

    if (gap != 0)
    {
        free(gapBuffer);
    }

    free(previous);
    free(current);
    free(next);

    return 0;
}

int applyGreyen(uint16_t biBitCount, int32_t biWidth, int32_t biHeight, FILE *fileStreamIn, FILE *fileStreamOut, int platform)
{
    int result;
    size_t bytesPerPixel = (size_t) biBitCount / 8;
    size_t rowSize = (size_t) (biBitCount * biWidth + 31) / 32 * 4;

    // In this method we can merge {gapBuffer} with {line}

    unsigned char *line = malloc(sizeof(unsigned char) * rowSize);

    // Apply filter to lines

    for (int i = 0; i < biHeight; i++)
    {
        result = fread(line, sizeof(unsigned char), rowSize, fileStreamIn);
        if (result != rowSize)
        {
            printf("Error reading line.\n");
            free(line);
            return 1;
        }

        // Modify line in-place

        int j = 0;
        while (j < bytesPerPixel * biWidth)
        {
            // Keep alpha channel
            if (bytesPerPixel == 4 && platform == LITTLE_ENDIAN)
            {
                j++;
            }

            double newValue = 0;

            if (platform == BIG_ENDIAN)
            {
                newValue =
                        LUMINANCE_RED * line[j] +
                        LUMINANCE_GREEN * line[j + 1] +
                        LUMINANCE_BLUE * line[j + 2];
            }
            else
            {
                newValue =
                        LUMINANCE_BLUE * line[j] +
                        LUMINANCE_GREEN * line[j + 1] +
                        LUMINANCE_RED * line[j + 2];
            }

            // This cast is always valid.
            unsigned char newByte = (unsigned char) newValue;

            line[j] = newByte;
            line[j + 1] = newByte;
            line[j + 2] = newByte;

            // Keep alpha channel
            if (bytesPerPixel == 4 && platform == BIG_ENDIAN)
            {
                j++;
            }

            j += 3;
        }

        // Save modification results. Gap bytes stay untouched.

        result = fwrite(line, sizeof(unsigned char), rowSize, fileStreamOut);
        if (result != rowSize)
        {
            printf("Error saving line.\n");
            free(line);
            return 1;
        }
    }

    free(line);

    return 0;
}
