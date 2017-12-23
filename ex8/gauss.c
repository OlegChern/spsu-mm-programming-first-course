#include "util.h"

const int gauss_matrix5x5[5][5] = {{1, 4,  6,  4,  1},
                                   {4, 16, 24, 16, 4},
                                   {6, 24, 36, 24, 6},
                                   {4, 16, 24, 16, 4},
                                   {1, 4,  6,  4,  1}};


const int gauss_matrix3x3[3][3] = {{1, 2, 1},
                                   {2, 4, 2},
                                   {1, 2, 1}};


void filterGauss5x5(int width, int height, struct RGBTRIPLE **rgb_arr, struct RGBTRIPLE **new_arr)
{
    for (int i = 1; i < height - 5; i++)
        for (int j = 1; j < width - 5; j++)
        {
            applyGaussToPixels5x5(rgb_arr, new_arr, j, i);
        }
}


void applyGaussToPixels5x5(struct RGBTRIPLE **arr, struct RGBTRIPLE **new_arr, int idx, int idy)
{
    int sum_g = 0, sum_b = 0, sum_r = 0;
    int div = 256;

    for (int i = 0; i < 25; i++)
    {
        struct RGBTRIPLE *temp_rgb = &arr[idy - 1 + i / 5][idx - 1 + i % 5];

        sum_b += temp_rgb->rgbBlue * gauss_matrix5x5[i / 5][i % 5];
        sum_g += temp_rgb->rgbGreen * gauss_matrix5x5[i / 5][i % 5];
        sum_r += temp_rgb->rgbRed * gauss_matrix5x5[i / 5][i % 5];
    }

    new_arr[idy][idx].rgbRed = (unsigned char) (sum_r / div);
    new_arr[idy][idx].rgbBlue = (unsigned char) (sum_b / div);
    new_arr[idy][idx].rgbGreen = (unsigned char) (sum_g / div);
}


void filterGauss3x3(int width, int height, struct RGBTRIPLE **rgb_arr, struct RGBTRIPLE **new_arr)
{
    for (int i = 1; i < height - 3; i++)
        for (int j = 1; j < width - 3; j++)
        {
            applyGaussToPixels3x3(rgb_arr, new_arr, j, i);
        }
}


void applyGaussToPixels3x3(struct RGBTRIPLE **arr, struct RGBTRIPLE **new_arr, int idx, int idy)
{
    int sum_g = 0, sum_b = 0, sum_r = 0;
    int div = 16;

    for (int i = 0; i < 9; i++)
    {
        struct RGBTRIPLE *temp_rgb = &arr[idy - 1 + i / 3][idx - 1 + i % 3];

        sum_b += temp_rgb->rgbBlue * gauss_matrix3x3[i / 3][i % 3];
        sum_g += temp_rgb->rgbGreen * gauss_matrix3x3[i / 3][i % 3];
        sum_r += temp_rgb->rgbRed * gauss_matrix3x3[i / 3][i % 3];
    }

    new_arr[idy][idx].rgbRed = (unsigned char) (sum_r / div);
    new_arr[idy][idx].rgbBlue = (unsigned char) (sum_b / div);
    new_arr[idy][idx].rgbGreen = (unsigned char) (sum_g / div);
}
