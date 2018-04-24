using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Filter
{
    public abstract class Filter
    {
        public abstract double[,] Parametr { get; set; }
        public Pixel[,] FilterImage(Pixel[,] image)
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
    public class GrayFilter
    {
        public Pixel[,] FilterImage(Pixel[,] image)
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
    public class MedianFilter : Filter
    {
        public override double[,] Parametr
        {
            get
            {
                return new double[3, 3]{ {1.0 / 9, 1.0 / 9, 1.0 / 9},
                                         {1.0 / 9, 1.0 / 9, 1.0 / 9},
                                         {1.0 / 9, 1.0 / 9, 1.0 / 9} };
            }
            set
            {
                Parametr = value;
            }
        }
    }
    public class GaussFilter : Filter
    {
        public override double[,] Parametr
        {
            get
            {
                return new double[3, 3] {{ 1.0 / 16, 2.0 / 16, 1.0 / 16}, 
                                         { 2.0 / 16, 4.0 / 16, 2.0 / 16},
                                         { 1.0 / 16, 2.0 / 16, 1.0 / 16}};
            }
            set
            {
                Parametr = value;
            }
        }
    }
    public class SobelXFilter : Filter
    {
        public override double[,] Parametr
        {
            get
            {
                return new double[3, 3] {{ -1.0, 0, 1.0}, 
                                         { -2.0, 0, 2.0},
                                         { -1.0, 0, 1.0}};
            }
            set
            {
                Parametr = value;
            }
        }
    }
    public class SobelYFilter : Filter
    {
        public override double[,] Parametr
        {
            get
            {
                return new double[3, 3] {{ -1.0, -2.0, -1.0},
                                         { 0   , 0   , 0   },
                                         { 1.0 , 2.0 , 1.0 }};
            }
            set
            {
                Parametr = value;
            }
        }
    }

}
