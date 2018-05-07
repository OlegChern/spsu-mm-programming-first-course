namespace Task1.Filters
{
    public abstract class AFilterMatrix : IFilter
    {
        private double[,] Matrix { get; }

        public AFilterMatrix(double[,] matrix)
        {
            Matrix = matrix;
        }

        public RGB[,] Apply(RGB[,] startRGB)
        {
            RGB[,] result = new RGB[startRGB.GetLength(0), startRGB.GetLength(1)];
            
            for (int i = 1; i < startRGB.GetLength(0) - 1; i++)
            {
                for (int j = 1; j < startRGB.GetLength(1) - 1; j++)
                {
                    double rgbRed = 0;
                    double rgbGreen = 0;
                    double rgbBlue = 0;

                    for (int k = 0; k < 3; k++)
                    {
                        for (int m = 0; m < 3; m++)
                        {
                            rgbRed += startRGB[i + k - 1,j + m - 1].rgbRed * Matrix[k,m];
                            rgbGreen += startRGB[i + k - 1, j + m - 1].rgbGreen * Matrix[k, m];
                            rgbBlue += startRGB[i + k - 1, j + m - 1].rgbBlue * Matrix[k, m];
                        }
                    }

                    result[i, j].rgbRed = Picture.DoubleToByte(rgbRed);
                    result[i, j].rgbGreen = Picture.DoubleToByte(rgbGreen);
                    result[i, j].rgbBlue = Picture.DoubleToByte(rgbBlue);
                }
            }
            return result;
        }
    }
}
