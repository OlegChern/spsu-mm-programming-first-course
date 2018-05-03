using System;

namespace Task_1
{
    class Program
    {
        private static void Main(string[] args)
        {
            try
            {
                if (args.Length != 3)
                {
                    throw new ArgumentException("Wrong arguments!");
                }

                try
                {
                    BMPFile bmp = new BMPFile();

                    bmp.LoadFile(args[0]);

                    switch (args[1])
                    {
                        case "Gauss":
                        {
                            BMPFilters.ApplyingFilterToFile(bmp, FilterType.Gauss);
                                break;
                        }
                        case "SobelX":
                        {
                            BMPFilters.ApplyingFilterToFile(bmp, FilterType.SobelX);
                                break;
                        }
                        case "SobelY":
                        {
                            BMPFilters.ApplyingFilterToFile(bmp, FilterType.SobelY);
                                break;
                        }
                        case "GrayScale":
                        {
                            BMPFilters.ApplyingFilterToFile(bmp, FilterType.GrayScale);
                                break;
                        }
                        case "Average":
                        {
                            BMPFilters.ApplyingFilterToFile(bmp, FilterType.Average);
                                break;
                        }
                        case "Haar":
                        {
                            BMPFilters.ApplyingFilterToFile(bmp, FilterType.Haar);
                                break;

                        }
                        default:
                        {
                            throw new ArgumentException("Wrong filter name!");
                        }
                    }

                    bmp.CreateFile(args[2]);
                }
                catch (ArgumentException exception)
                {
                    Console.WriteLine('\n' + exception.Message + '\n');
                }

            }
            catch (ArgumentException exception)
            {
                Console.WriteLine('\n' + exception.Message + '\n');
            }
        }
    }
}