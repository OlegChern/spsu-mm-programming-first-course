#include "util.h"

const char info[] = "\nPlease, enter the path to the input file, the output file "
        "and name of the filter you want to apply\n\n"
        "Available filters:\n"
        "Median filter (type median)\n"
        "Gray filter (type grey)\n"
        "Gauss filter 3x3 (type gauss3)\n"
        "Gauss filter 5x5 (type gauss5)\n"
        "Sobel filter X (type sobelX)\n"
        "Sobel filter Y (type sobelY)\n"
        "Sobel filter (type sobelXY)\n\n"
        "Example: /home/username/bird.bmp /home/username/output.bmp gauss5\n\n";


void applyFilter(char *filter, struct RGBTRIPLE **old_arr, struct RGBTRIPLE **new_arr, int width, int height)
{
    if (!strcmp(filter, "median"))
    {
        filterMedian(width, height, old_arr, new_arr);
    }
    if (!strcmp(filter, "grey"))
    {
        filterGrey(width, height, old_arr, new_arr);
    }
    if (!strcmp(filter, "gauss3"))
    {
        filterGauss3x3(width, height, old_arr, new_arr);
    }
    if (!strcmp(filter, "gauss5"))
    {
        filterGauss5x5(width, height, old_arr, new_arr);
    }
    if (!strcmp(filter, "sobelX"))
    {
        filterSobelX(width, height, old_arr, new_arr);
    }
    if (!strcmp(filter, "sobelY"))
    {
        filterSobelY(width, height, old_arr, new_arr);
    }
    if (!strcmp(filter, "sobelXY"))
    {
        filterSobelXY(width, height, old_arr, new_arr);
    }
}

int checkArguments(char *filter, int argc)
{
    if (argc == 1)
    {
        printf("%s", info);
        return 1;
    }


    if (argc < 4)
    {
        printf("NOT ENOUGH ARGUMENTS\n");
        return 1;
    }

    if (strcmp(filter, "median") && strcmp(filter, "grey") && strcmp(filter, "gauss3") && strcmp(filter, "gauss5") &&
        strcmp(filter, "sobelX") && strcmp(filter, "sobelY") && strcmp(filter, "sobelXY"))
    {
        printf("INVALID FILTER NAME\n");
        return 1;
    }

    return 0;
}

struct RGBTRIPLE **cpyArray(struct RGBTRIPLE **old_arr, struct map *BITMAPINFO)
{
    struct RGBTRIPLE **rgb_new = malloc(sizeof(struct RGBTRIPLE *) * BITMAPINFO->biHeight);

    for (int i = 0; i < BITMAPINFO->biHeight; i++)
    {
        rgb_new[i] = calloc(sizeof(struct RGBTRIPLE), BITMAPINFO->biWidth);
        memcpy(rgb_new[i], old_arr[i], sizeof(struct RGBTRIPLE) * BITMAPINFO->biWidth);
    }

    return rgb_new;
}

int readFile(struct header *BITMAPFILEHEADER, struct map *BITMAPINFO, FILE *in)
{
    if (in == NULL)
    {
        printf("ERROR! UNABLE TO OPEN THE INPUT FILE!\n");

        return 0;
    }

    fread(BITMAPFILEHEADER, sizeof(struct header), 1, in);

    if (BITMAPFILEHEADER->bfType != 0x4D42)
    {
        printf("INVALID FORMAT, IT IS NOT A BMP FILE\n");
        return 0;
    }

    fread(BITMAPINFO, sizeof(struct map), 1, in);

    if (BITMAPINFO->biSize != 40)
    {
        printf("INVALID BITMAPINFO SIZE\n");
        return 0;
    }

    if (BITMAPINFO->biBitCount != 24 && BITMAPINFO->biBitCount != 32)
    {
        printf("ERROR! ONLY 24 AND 32 BIT FILES ARE SUPPORTED\n");
        return 0;
    }

    return BITMAPINFO->biBitCount;
}

struct RGBTRIPLE **readArrayX24(int *padding, struct map *BITMAPINFO, FILE *in)
{
    struct RGBTRIPLE **rgb_arr = calloc(sizeof(struct RGBTRIPLE *), BITMAPINFO->biHeight);

    for (int i = 0; i < BITMAPINFO->biHeight; i++)
    {
        rgb_arr[i] = calloc(sizeof(struct RGBTRIPLE *), BITMAPINFO->biWidth);
    }

    *padding = (4 - (BITMAPINFO->biWidth * (BITMAPINFO->biBitCount / 8)) % 4) & 3;


    for (int i = 0; i < BITMAPINFO->biHeight; i++)
    {
        for (int j = 0; j < BITMAPINFO->biWidth; j++)
        {
            rgb_arr[i][j].rgbBlue = (unsigned char) getc(in);
            rgb_arr[i][j].rgbGreen = (unsigned char) getc(in);
            rgb_arr[i][j].rgbRed = (unsigned char) getc(in);
        }

        for (int k = 0; k < *padding; k++)
            getc(in);
    }

    fclose(in);

    return rgb_arr;
}

struct RGBTRIPLE **readArrayX32(int *padding, struct map *BITMAPINFO, FILE *in)
{
    struct RGBTRIPLE **rgb_arr = calloc(sizeof(struct RGBTRIPLE *), BITMAPINFO->biHeight);

    for (int i = 0; i < BITMAPINFO->biHeight; i++)
    {
        rgb_arr[i] = calloc(BITMAPINFO->biWidth, sizeof(struct RGBTRIPLE));
    }

    *padding = (4 - (BITMAPINFO->biWidth * (BITMAPINFO->biBitCount / 8)) % 4) & 3;

    for (int i = 0; i < BITMAPINFO->biHeight; i++)
    {
        for (int j = 0; j < BITMAPINFO->biWidth; j++)
        {
            rgb_arr[i][j].rgbBlue = (unsigned char) getc(in);
            rgb_arr[i][j].rgbGreen = (unsigned char) getc(in);
            rgb_arr[i][j].rgbRed = (unsigned char) getc(in);
            getc(in);
        }

        for (int k = 0; k < *padding; k++)
            getc(in);
    }

    fclose(in);

    return rgb_arr;
}

int writeFIleX24(struct RGBTRIPLE **rgb_arr, int *padding, struct header *BITMAPFILEHEADER, struct map *BITMAPINFO,
                 char *output, FILE *out)
{
    if (out == NULL)
    {
        printf("ERROR! UNABLE TO OPEN THE OUTPUT FILE!");
        fclose(out);
        return 0;
    }

    fwrite(BITMAPFILEHEADER, sizeof(struct header), 1, out);
    fwrite(BITMAPINFO, sizeof(struct map), 1, out);

    for (int i = 0; i < BITMAPINFO->biHeight; i++)
    {
        for (int j = 0; j < BITMAPINFO->biWidth; j++)
            fwrite(&rgb_arr[i][j], sizeof(struct RGBTRIPLE), 1, out);

        for (int k = 0; k < *padding; k++)
            fputc(0, out);
    }

    fclose(out);
}

int writeFIleX32(struct RGBTRIPLE **rgb_arr, int *padding, struct header *BITMAPFILEHEADER, struct map *BITMAPINFO,
                 char *output, FILE *out)
{
    if (out == NULL)
    {
        printf("ERROR! UNABLE TO OPEN THE OUTPUT FILE!");
        fclose(out);
        return 0;
    }

    fwrite(BITMAPFILEHEADER, sizeof(struct header), 1, out);
    fwrite(BITMAPINFO, sizeof(struct map), 1, out);

    for (int i = 0; i < BITMAPINFO->biHeight; i++)
    {
        for (int j = 0; j < BITMAPINFO->biWidth; j++)
        {
            fwrite(&rgb_arr[i][j], sizeof(struct RGBTRIPLE), 1, out);
            putc(0, out);
        }

        for (int k = 0; k < *padding; k++)
            fputc(0, out);
    }

    fclose(out);
}