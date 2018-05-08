using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Filter
{
    public class GrayFilter : Filter
    {
        public override double[,] Parametr { get { return null; } }
        public override Pixel[,] FilterImage(Pixel[,] image)
        {
            for (int j = 0; j < image.GetLength(1); j++)
            {
                for (int i = 0; i < image.GetLength(0); i++)
                {
                    var k = (byte)(0.2126 * image[i, j].Red + 0.7152 * image[i, j].Green + 0.0722 * image[i, j].Blue);
                    image[i, j].Red = k;
                    image[i, j].Green = k;
                    image[i, j].Blue = k;
                    image[i, j].SetColor();
                }
            }
            return image;
        }
    }
}
