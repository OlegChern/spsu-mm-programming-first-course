/// Had to change quite a lot in my C code!

using System;
using System.IO;

namespace task1
{
    class Program
    {
        #region constants

        const string about = "This is an utility that applies selected filter to selected .bmp image.\r\n"
                           + "Arguments:\r\n"
                           + "-i: path to file to be modified.\r\n"
                           + "-o: path to desired destination of resulting image.\r\n"
                           + "-f: filter to be applied.\npossible filters:\r\n"
                           + "\tgauss\r\n"
                           + "\tsobelx\r\n"
                           + "\tsobely\r\n"
                           + "\tgreyen\n";

        const string gauss = "gauss";
        const string sobelx = "sobelx";
        const string sobely = "sobely";
        const string greyen = "greyen";

        readonly static double[][] gaussMatrix =
        {
            new double[] {1.0 / 16, 1.0 / 8, 1.0 / 16},
            new double[] {1.0 / 8, 1.0 / 4, 1.0 / 8},
            new double[] {1.0 / 16, 1.0 / 8, 1.0 / 16}
        };

        readonly static double[][] sobelxMatrix =
        {
            new double[] {-3.0 / 32, 0, 3.0 / 32},
            new double[] {-10.0 / 32, 0, 10.0 / 32},
            new double[] {-3.0 / 32, 0, 3.0 / 32}
        };

        readonly static double[][] sobelyMatrix =
        {
            new double[] {-3.0 / 32, -10.0 / 32, -3.0 / 32},
            new double[] {0, 0, 0},
            new double[] {3.0 / 32, 10.0 / 32, 3.0 / 32}
        };

        #endregion

        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                Console.WriteLine(about);
                Console.ReadKey();
                return;
            }

            try
            {
                Util.HandleArguments(args, out string source, out string filter, out string destination);
                var bytes = File.ReadAllBytes(source);
                Util.HandleBitMapFileHeader(bytes, out var fileHeader, out var endianness);
                Util.HandleBitMapInfoHeader(bytes, out var infoHeader, endianness);
                
                var newBytes = new byte[bytes.Length];
                Util.CopyHeader(bytes, newBytes, fileHeader.bfOffBits);
                if (filter == gauss)
                {
                    Util.ApplyKernel(bytes, newBytes, gaussMatrix);
                }
                else if (filter == sobelx)
                {
                    Util.ApplyKernel(bytes, newBytes, sobelxMatrix);
                }
                else if (filter == sobely)
                {
                    Util.ApplyKernel(bytes, newBytes, sobelyMatrix);
                }
                else if (filter == greyen)
                {
                    Util.ApplyGreyen(bytes, newBytes, );
                }
                // TODO: save
                else
                {
                    throw new ArgumentException($"Error: unknown filter type: \"{filter}\"");
                }

            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                // Could've performed a minor cleanup at this point, but what for?
                Console.ReadKey();
                return;
            }

            Console.ReadKey();
        }
    }
}
