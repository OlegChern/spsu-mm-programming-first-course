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
                    double newColor = (startRGB[i, j].rgbBlue + startRGB[i, j].rgbRed + startRGB[i, j].rgbGreen) / 3;
                    result[i, j].rgbBlue = (byte)newColor;
                    result[i, j].rgbRed = (byte)newColor;
                    result[i, j].rgbGreen = (byte)newColor;
                }
            }

            return result;
        }
    }
}
