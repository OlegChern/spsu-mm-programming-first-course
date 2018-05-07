namespace Task1.Filters
{
    public class GreyFilter : IFilter
    {
        public RGB[,] Apply(RGB[,] startRGB)
        {
            RGB[,] result = new RGB[startRGB.GetLength(0), startRGB.GetLength(1)];

            for (int i = 0; i < startRGB.GetLength(0); i++)
            {
                for (int j = 0; j < startRGB.GetLength(1); j++)
                {
                    double newColor = 0.072 * startRGB[i, j].rgbBlue + 0.213 * startRGB[i, j].rgbRed + 0.0715 * startRGB[i, j].rgbGreen;
                    result[i, j].rgbBlue = (byte)newColor;
                    result[i, j].rgbRed = (byte)newColor;
                    result[i, j].rgbGreen = (byte)newColor;
                }
            }

            return result;
        }
    }
}
