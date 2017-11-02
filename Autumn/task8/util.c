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
