#include "util.h"

const int gauss_matrix5x5[5][5] = {{1, 4,  6,  4,  1},
                                   {4, 16, 24, 16, 4},
                                   {6, 24, 36, 24, 6},
                                   {4, 16, 24, 16, 4},
                                   {1, 4,  6,  4,  1}};


const int gauss_matrix3x3[3][3] = {{1, 2, 1},
                                   {2, 4, 2},
                                   {1, 2, 1}};



void filterGauss(int width, int height, struct RGBTRIPLE **rgb_arr, struct RGBTRIPLE **new_arr, int option)
{
    for (int i = 1; i < height - option; i++)
        for (int j = 1; j < width - option; j++)
        {
            applyGaussToPixels(rgb_arr, new_arr, j, i, option);
        }
}

void applyGaussToPixels(struct RGBTRIPLE **arr, struct RGBTRIPLE **new_arr, int idx, int idy, int option)
{
    int sum_g = 0, sum_b = 0, sum_r = 0;
    int div = option < 4 ? 16 : 256;

    if (option < 5)
    {
        for (int i = 0; i < option * option; i++)
        {
            struct RGBTRIPLE *temp_rgb = &arr[idy - 1 + i / option][idx - 1 + i % option];

            sum_b += temp_rgb->rgbBlue * gauss_matrix3x3[i / option][i % option];
            sum_g += temp_rgb->rgbGreen * gauss_matrix3x3[i / option][i % option];
            sum_r += temp_rgb->rgbRed * gauss_matrix3x3[i / option][i % option];
        }
    }
    else
    {
        for (int i = 0; i < option * option; i++)
        {
            struct RGBTRIPLE *temp_rgb = &arr[idy - 1 + i / option][idx - 1 + i % option];

            sum_b += temp_rgb->rgbBlue * gauss_matrix5x5[i / option][i % option];
            sum_g += temp_rgb->rgbGreen * gauss_matrix5x5[i / option][i % option];
            sum_r += temp_rgb->rgbRed * gauss_matrix5x5[i / option][i % option];
        }
    }

    new_arr[idy][idx].rgbRed = (unsigned char) (sum_r / div);
    new_arr[idy][idx].rgbBlue = (unsigned char) (sum_b / div);
    new_arr[idy][idx].rgbGreen = (unsigned char) (sum_g / div);
}