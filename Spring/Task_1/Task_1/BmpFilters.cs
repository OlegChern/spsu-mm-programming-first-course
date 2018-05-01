using System;

namespace Task_1
{
    internal class BMPFilters
    {
        internal static void ApplyingFilterToFile(BMPFile bmp, FilterType filter)
        {
            switch (filter)
            {
                case FilterType.Average:
                    {
                        Console.WriteLine("Successfully applied Average filter.");

                        float[,] average = new float[3, 3];
                        float k = 1f / 9f;

                        for (int i = 0; i < 3; i++)
                        {
                            for (int j = 0; j < 3; j++)
                            {
                                average[i, j] = k;
                            }
                        }

                        Gauss3x3(bmp, average);

                        break;
                    }
                case FilterType.Gauss:
                    {
                        Console.WriteLine("Successfully applied Gauss filter.");

                        float[,] kernel = new float[3, 3];
                        const float sigma = 1;
                        float sigmaSqr = 2 * sigma * sigma;

                        for (int i = -1; i <= 1; i++)
                        {
                            for (int j = -1; j <= 1; j++)
                            {
                                kernel[i + 1, j + 1] = (float)(Math.Exp(-(i * i + j * j) / sigmaSqr) / (Math.PI * sigmaSqr));
                            }
                        }

                        Gauss3x3(bmp, kernel);

                        break;
                    }
                case FilterType.GrayScale:
                    {
                        Console.WriteLine("Successfully applied Gray Scale filter.");

                        Grayscale(bmp);

                        break;
                    }
                case FilterType.SobelX:
                    {
                        Console.WriteLine("Successfully applied SobelX filter.");

                        float[,] maskx =
                        {
                            { -1f, 0f, 1f },
                            { -2f, 0f, 2f },
                            { -1f, 0f, 1f }
                        };

                        Sobel(bmp, maskx);

                        break;
                    }
                case FilterType.SobelY:
                    {
                        Console.WriteLine("Successfully applied SobelY filter.");

                        float[,] masky =
                        {
                            { -1f, -2f, -1f },
                            { 0f, 0f, 0f },
                            { 1f, 2f, 1f }
                        };

                        Sobel(bmp, masky);

                        break;
                    }
            }
        }
        
        #region filterMethods
        private static void Gauss3x3(BMPFile bmp, float[,] kernel)
        {
            int width = bmp.Width;
            int height = bmp.Height;

            for (int x = 1; x < width - 1; x++)
            {
                for (int y = 1; y < height - 1; y++)
                {
                    float sum = 0;
                    float r = 0, g = 0, b = 0;

                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            Pixel pixel = bmp[x + i, y + j];
                            float k = kernel[i + 1, j + 1];

                            r += pixel.Red * k;
                            g += pixel.Green * k;
                            b += pixel.Blue * k;

                            sum += k;
                        }
                    }

                    if (sum != 0)
                    {
                        bmp[x, y] = new Pixel
                        {
                            Red = ToByte(r / sum),
                            Blue = ToByte(b / sum),
                            Green = ToByte(g / sum)
                        };
                    }
                }
            }
        }

        private static void Sobel(BMPFile bmp, float[,] mask)
        {
            int width = bmp.Width;
            int height = bmp.Height;

            Pixel[,] temp = new Pixel[height, width];

            for (int x = 1; x < width - 1; x++)
            {
                for (int y = 1; y < height - 1; y++)
                {
                    int sum = 0;

                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            byte cur = GrayscaledPixel(bmp[x + i, y + j]);
                            sum += (int)(cur * mask[i + 1, j + 1]);
                        }
                    }

                    byte clamped = ToByte(sum);
                    temp[x, y] = new Pixel { Red = clamped, Green = clamped, Blue = clamped };
                }
            }

            for (int x = 0; x < width; x++)
            {
                for (int y = 0; y < height; y++)
                {
                    bmp[x, y] = temp[x, y];
                }
            }
        }

        private static void Grayscale(BMPFile bmp)
        {
            int width = bmp.Width;
            int height = bmp.Height;

            for (int x = 0; x < width; x++)
            {
                for (int y = 0; y < height; y++)
                {
                    byte gray = GrayscaledPixel(bmp[x, y]);
                    bmp[x, y] = new Pixel { Red = gray, Green = gray, Blue = gray };
                }
            }
        }

        private static byte GrayscaledPixel(Pixel pixel)
        {
            return ToByte((pixel.Red + pixel.Green + pixel.Blue) / 3);
        }
        #endregion

        private static byte ToByte(float f)
        {
            return f - (int)f >= 0.5f ?
                (byte)(f + 1) :
                (byte)f;
        }

        private static byte ToByte(int s)
        {
            return s < 0 ? (byte)0 :
                s > 255 ? (byte)255 :
                (byte)s;
        }
    }
}
