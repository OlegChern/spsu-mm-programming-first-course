using System;
using System.IO;

namespace Task1.Filters
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 3)
            {
                Console.WriteLine("Incorrect Input");
                return;
            }

            FileStream fileInput = File.Open(args[0], FileMode.Open);
            Picture bmp = new Picture(fileInput);
            fileInput.Close();

            string filterName = args[1];
            switch (filterName)
            {
                case "Average":
                    {
                        AverageFilter filter = new AverageFilter();
                        bmp.ApplyFilter(filter);
                        break;
                    }
                case "Gauss":
                    {
                        GaussFilter filter = new GaussFilter();
                        bmp.ApplyFilter(filter);
                        break;
                    }
                case "Grey":
                    {
                        GreyFilter filter = new GreyFilter();
                        bmp.ApplyFilter(filter);
                        break;
                    }
                case "SobelX":
                    {
                        SobelFilterX filter = new SobelFilterX();
                        bmp.ApplyFilter(filter);
                        break;
                    }
                case "SobelY":
                    {
                        SobelFilterY filter = new SobelFilterY();
                        bmp.ApplyFilter(filter);
                        break;
                    }
                default:
                    {
                        throw new ArgumentException("Incorrect Input");
                    }
            }

            FileStream fileOutput = File.Open(args[2], FileMode.Open);
            bmp.WriteBMP(fileOutput);
            fileOutput.Close();
        }
    }
}
