#include "util.h"

void swap(unsigned char *a, unsigned char *b)
{
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}

void filterMedian(int width, int height, struct RGBTRIPLE **rgb_arr, struct RGBTRIPLE **new_arr)
{
    for (int i = 1; i < height - 3; i++)
        for (int j = 1; j < width - 3; j++)
        {
            applyMedianToPixels(rgb_arr, new_arr, j, i);
        }
}

void applyMedianToPixels(struct RGBTRIPLE **arr, struct RGBTRIPLE **new_arr, int idx, int idy)
{
    unsigned char arr_g[9], arr_b[9], arr_r[9];

    for (int i = 0; i < 9; i++)
    {
        struct RGBTRIPLE *temp_rgb = &arr[idy - 1 + i / 3][idx - 1 + i % 3];

        arr_b[i] = temp_rgb->rgbBlue;
        arr_g[i] = temp_rgb->rgbGreen;
        arr_r[i] = temp_rgb->rgbRed;
    }

    for (int j = 0; j < 9; j++)
        for (int i = 0; i < 9; i++)
        {
            if (arr_b[i] > arr_b[j])
                swap(&arr_b[j], &arr_b[i]);

            if (arr_g[i] > arr_g[j])
                swap(&arr_g[j], &arr_g[i]);

            if (arr_r[i] > arr_r[j])
                swap(&arr_r[j], &arr_r[i]);
        }

    new_arr[idy][idx].rgbRed = arr_r[4];
    new_arr[idy][idx].rgbBlue = arr_b[4];
    new_arr[idy][idx].rgbGreen = arr_g[4];

}

void filterGrey(int width, int height, struct RGBTRIPLE **rgb_arr, struct RGBTRIPLE **new_arr)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned char d = (unsigned char) ((rgb_arr[i][j].rgbGreen + rgb_arr[i][j].rgbBlue + rgb_arr[i][j].rgbRed) /
                                               3);

            new_arr[i][j].rgbBlue = d;
            new_arr[i][j].rgbGreen = d;
            new_arr[i][j].rgbRed = d;
        }
    }
}

