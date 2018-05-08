using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Filter
{
    public abstract class Filter
    {
        public abstract double[,] Parametr { get; }
        public virtual Pixel[,] FilterImage(Pixel[,] image)
        {
            var newImage = new Pixel[image.GetLength(0), image.GetLength(1)];
            for (int j = 0; j < image.GetLength(1); j++)
            {
                for (int i = 0; i < image.GetLength(0); i++)
                {
                    if (!(i == 0) && !(j == 0) && !(i == (image.GetLength(0) - 1)) && !(j == (image.GetLength(1) - 1)))
                    {
                        for (int x = -1; x < 2; x++)
                        {
                            for (int y = -1; y < 2; y++)
                            {
                                newImage[i, j] += image[i + x, j + y] * Parametr[x + 1, y + 1];
                            }
                        }
                        newImage[i, j].SetColor();
                    }
                }
            }
            return newImage;
        }
    }
}
