#include "util.h"
#include <math.h>

const int sobelx_matrix[3][3] = {{1,  2,  1},
                                 {0,  0,  0},
                                 {-1, -2, -1}};


const int sobely_matrix[3][3] = {{1,  2,  1},
                                 {0,  0,  0},
                                 {-1, -2, -1}};


void filterSobelX(int width, int height, struct RGBTRIPLE **rgb_arr, struct RGBTRIPLE **new_arr)
{
    for (int i = 1; i < height - 3; i++)
        for (int j = 1; j < width - 3; j++)
        {
            applySobelXToPixels(rgb_arr, new_arr, j, i);
        }
}


void applySobelXToPixels(struct RGBTRIPLE **arr, struct RGBTRIPLE **new_arr, int idx, int idy)
{
    int x_sum_g = 0, x_sum_b = 0, x_sum_r = 0;

    for (int i = 0; i < 9; i++)
    {
        struct RGBTRIPLE *temp_rgb = &arr[idy - 1 + i / 3][idx - 1 + i % 3];

        x_sum_b += temp_rgb->rgbBlue * sobelx_matrix[i / 3][i % 3];
        x_sum_g += temp_rgb->rgbGreen * sobelx_matrix[i / 3][i % 3];
        x_sum_r += temp_rgb->rgbRed * sobelx_matrix[i / 3][i % 3];
    }

    if (x_sum_r < 0) x_sum_r = 0;
    if (x_sum_b < 0) x_sum_b = 0;
    if (x_sum_g < 0) x_sum_g = 0;

    if (x_sum_b > 255) x_sum_b = 255;
    if (x_sum_g > 255) x_sum_g = 255;
    if (x_sum_r > 255) x_sum_r = 255;

    new_arr[idy][idx].rgbRed = (unsigned char) (x_sum_r);
    new_arr[idy][idx].rgbBlue = (unsigned char) (x_sum_b);
    new_arr[idy][idx].rgbGreen = (unsigned char) (x_sum_g);
}


void filterSobelY(int width, int height, struct RGBTRIPLE **rgb_arr, struct RGBTRIPLE **new_arr)
{
    for (int i = 1; i < height - 3; i++)
        for (int j = 1; j < width - 3; j++)
        {
            applySobelYToPixels(rgb_arr, new_arr, j, i);
        }
}


void applySobelYToPixels(struct RGBTRIPLE **arr, struct RGBTRIPLE **new_arr, int idx, int idy)
{
    int y_sum_g = 0, y_sum_b = 0, y_sum_r = 0;

    for (int i = 0; i < 9; i++)
    {
        struct RGBTRIPLE *temp_rgb = &arr[idy - 1 + i / 3][idx - 1 + i % 3];

        y_sum_b += temp_rgb->rgbBlue * sobely_matrix[i / 3][i % 3];
        y_sum_g += temp_rgb->rgbGreen * sobely_matrix[i / 3][i % 3];
        y_sum_r += temp_rgb->rgbRed * sobely_matrix[i / 3][i % 3];
    }

    if (y_sum_r < 0) y_sum_r = 0;
    if (y_sum_b < 0) y_sum_b = 0;
    if (y_sum_g < 0) y_sum_g = 0;

    if (y_sum_b > 255) y_sum_b = 255;
    if (y_sum_g > 255) y_sum_g = 255;
    if (y_sum_r > 255) y_sum_r = 255;

    new_arr[idy][idx].rgbRed = (unsigned char) (y_sum_r);
    new_arr[idy][idx].rgbBlue = (unsigned char) (y_sum_b);
    new_arr[idy][idx].rgbGreen = (unsigned char) (y_sum_g);
}

void filterSobelXY(int width, int height, struct RGBTRIPLE **rgb_arr, struct RGBTRIPLE **new_arr)
{
    for (int i = 1; i < height - 3; i++)
        for (int j = 1; j < width - 3; j++)
        {
            applySobelXYToPixels(rgb_arr, new_arr, j, i);
        }
}


void applySobelXYToPixels(struct RGBTRIPLE **arr, struct RGBTRIPLE **new_arr, int idx, int idy)
{
    int y_sum_g = 0, y_sum_b = 0, y_sum_r = 0, x_sum_g = 0, x_sum_b = 0, x_sum_r = 0;

    for (int i = 0; i < 9; i++)
    {
        struct RGBTRIPLE *temp_rgb = &arr[idy - 1 + i / 3][idx - 1 + i % 3];

        y_sum_b += temp_rgb->rgbBlue * sobely_matrix[i / 3][i % 3];
        y_sum_g += temp_rgb->rgbGreen * sobely_matrix[i / 3][i % 3];
        y_sum_r += temp_rgb->rgbRed * sobely_matrix[i / 3][i % 3];

        x_sum_b += temp_rgb->rgbBlue * sobelx_matrix[i / 3][i % 3];
        x_sum_g += temp_rgb->rgbGreen * sobelx_matrix[i / 3][i % 3];
        x_sum_r += temp_rgb->rgbRed * sobelx_matrix[i / 3][i % 3];
    }

    int Gb = (int) sqrt(y_sum_b * y_sum_b + x_sum_b * x_sum_b);
    int Gg = (int) sqrt(y_sum_g * y_sum_g + x_sum_g * x_sum_g);
    int Gr = (int) sqrt(y_sum_r * y_sum_r + x_sum_r * x_sum_r);

    if (Gb > 255) Gb = 255;
    if (Gg > 255) Gg = 255;
    if (Gr > 255) Gr = 255;

    new_arr[idy][idx].rgbRed = (unsigned char) (Gb);
    new_arr[idy][idx].rgbBlue = (unsigned char) (Gg);
    new_arr[idy][idx].rgbGreen = (unsigned char) (Gr);
}

