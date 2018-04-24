using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Filter
{
    class Program
    {
        static void Main(string[] args)
        {
            string inFileName = null;
            string outFileName = null;
            string filterName = null;
            if (args.Length != 3)
            {
                Console.WriteLine("Error:\n" +
                "Enter name programm, name of input file, filter's name and name of output file:\n" +
                "1) Input file -- 24 or 32 bit .bmp\n" +
                "2) Filter's names:\nmedian3x3\ngauss_3x3\nsobel_x\nsobel_y\ngray\n" +
                "3) Output file -- .bmp\n" +
                "Example: \"D:\\Task 8.exe\" D:\\inName.bmp gauss_3x3 D:\\outName.bmp");
                return;
            }
            else
            {
                inFileName = args[0];
                filterName = args[1];
                outFileName = args[2];
            }


            var photo = new BMPImage();
            photo.ReadBMP(inFileName);
            if ((filterName != "median3x3") ||
            (filterName != "gauss_3x3") ||
            (filterName != "sobel_x") ||
            (filterName != "sobel_y") ||
            (filterName != "gray"))
            {
                photo.Filter(filterName);
            }
            else
            {
                throw new ArgumentException("Неверное имя фильтра");
            }                
            photo.WriteBMP(outFileName);
        }
    }
}
