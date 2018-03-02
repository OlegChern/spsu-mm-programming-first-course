using System;

namespace HomeworkTask01
{
	public class BMPFilters
	{
		public enum Type
		{
			Gauss,
			SobelX,
			SobelY,
			GrayScale,
			Average
		}

		#region processing method
		public static void ProcessBMP(BMP bmp, Type filter)
		{
			switch (filter)
			{
				case Type.Average:
					{
						Console.WriteLine("Applying Average3x3 filter.");

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
				case Type.Gauss:
					{
						Console.WriteLine("Applying Gauss3x3 filter.");

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
				case Type.GrayScale:
					{
						Console.WriteLine("Applying GrayScale filter.");
						Grayscale(bmp);

						break;
					}
				case Type.SobelX:
					{
						Console.WriteLine("Applying SobelX filter.");

						float[,] maskx = new float[,]
						{
							{ -1f, 0f, 1f },
							{ -2f, 0f, 2f },
							{ -1f, 0f, 1f }
						};

						Sobel(bmp, maskx);

						break;
					}
				case Type.SobelY:
					{
						Console.WriteLine("Applying SobelY filter.");

						float[,] masky = new float[,]
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
		#endregion

		#region filter methods
		private static void Gauss3x3(BMP bmp, float[,] kernel)
		{
			uint width = bmp.Width;
			uint height = bmp.Height;

			for (uint x = 1; x < height - 1; x++)
			{
				for (uint y = 1; y < width - 1; y++)
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
							Red = RoundToByte(r / sum),
							Blue = RoundToByte(b / sum),
							Green = RoundToByte(g / sum)
						};
					}
				}
			}
		}

		private static void Sobel(BMP bmp, float[,] mask)
		{
			uint width = bmp.Width;
			uint height = bmp.Height;

			Pixel[,] temp = new Pixel[height, width];

			for (int x = 1; x < height - 1; x++)
			{
				for (int y = 1; y < width - 1; y++)
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

					byte clamped = ClampToByte(sum);
					temp[x, y] = new Pixel { Red = clamped, Green = clamped, Blue = clamped };
				}
			}

			for (int x = 0; x < height; x++)
			{
				for (int y = 0; y < width; y++)
				{
					bmp[x, y] = temp[x, y];
				}
			}
		}

		private static void Grayscale(BMP bmp)
		{
			uint width = bmp.Width;
			uint height = bmp.Height;

			for (uint x = 0; x < height; x++)
			{
				for (uint y = 0; y < width; y++)
				{
					byte gray = GrayscaledPixel(bmp[x, y]);
					bmp[x, y] = new Pixel { Red = gray, Green = gray, Blue = gray };
				}
			}
		}
		#endregion

		#region byte methods
		private static byte RoundToByte(float f)
		{
			return f - (int)f >= 0.5f ?
				(byte)(f + 1) :
				(byte)f;
		}

		private static byte ClampToByte(int s)
		{
			return s < 0 ? (byte)0 :
				s > 255 ? (byte)255 :
				(byte)s;
		}

		private static byte GrayscaledPixel(Pixel pixel)
		{
			return RoundToByte((pixel.Red + pixel.Green + pixel.Blue) / 3);
		}
		#endregion
	}
}
