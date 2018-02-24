using System;
using System.IO;

namespace task1
{
    internal enum ColourPart
    {
        Red = 0,
        Green = 1,
        Blue = 2,
        Alpha = 3
    }
   
    // All ugly variable names are equal to the ones in documentation.

    internal struct BitMapFileHeader
    {
        internal System.UInt32 bfSize; // File size
        internal System.UInt32 bfOffBits; // Pixel data offset
    }

    internal struct BitMapInfoHeader
    {
        internal System.Int32 biWidth; // Image width
        internal System.Int32 biHeight; // Image height
        internal System.UInt16 biBitCount; // Number of bits per pixel
    }

    internal static class Util
    {
        internal const double RedLuminance = 0.2126;
        internal const double GreenLuminance = 0.7152;
        internal const double BlueLuminance = 0.0722;

        internal static byte ToByte(double value)
        {
            if (value < 0)
            {
                return 0;
            }
            if (value > 255)
            {
                return 255;
            }
            return (byte)value;
        }

        internal static byte AbsToByte(double value)
        {
            if (Math.Abs((int)value) > 255)
            {
                return 255;
            }
            return (byte)Math.Abs((int)value);
        }

        /// <summary>
        /// Asks user whether to apply action or not
        /// </summary>
        /// <param name="message">message to be displayed to user</param>
        /// <returns>whether user approves action or not</returns>
        internal static bool Confirm(string message)
        {
            while (true)
            {
                Console.Write(message);
                char answer = Console.ReadLine()[0];
                if (answer == 'y' || answer == 'Y')
                {
                    return true;
                }
                else if (answer == 'n' || answer == 'N')
                {
                    return false;
                }
            }
        }

        /// type[0] is supposed be '-'
        /// length of type is supposed to be 2
        internal static void Choose(string type, string value, ref string source, ref string filter, ref string destination)
        {
            if (type[1] == 'i')
            {
                if (source == null)
                {
                    source = value;
                    return;
                }
                throw new ArgumentException("Error: -i parameter provided more than once.");
            }
            else if (type[1] == 'f')
            {
                if (filter == null)
                {
                    filter = value;
                    return;
                }
                throw new ArgumentException("Error: -f parameter provided more than once.");
            }
            else if (type[1] == 'o')
            {
                if (destination == null)
                {
                    destination = value;
                    return;
                }
                throw new ArgumentException("Error: -o parameter provided more than once.");
            }
            throw new ArgumentException($"Error: \"{type}\" is unknown argument specifier.");
        }

        internal static void HandleArguments(string[] args, out string source, out string filter, out string destination)
        {
            source = null;
            filter = null;
            destination = null;

            int i = 0;
            while (i < args.Length)
            {
                if (args[i][0] != '-')
                {
                    throw new ArgumentException($"Error: argument \"{args[i]}\" provided without type specifier.");
                }

                if (args[i].Length != 2)
                {
                    throw new ArgumentException($"Error: {args[i]} is not a valid type specifier.");
                }

                if (i + 1 == args.Length || args[i + 1][0] == '-')
                {
                    throw new ArgumentException($"Error: no value is provided after \"{args[i]}\".");
                }
                Choose(args[i], args[i + 1], ref source, ref filter, ref destination);
                i += 2;

            }

            if (source == null)
            {
                throw new ArgumentException("Error: source file not provided.");
            }
            if (destination == null)
            {
                throw new ArgumentException("Error: destination file not provided.");
            }
            if (filter == null)
            {
                throw new ArgumentException("Error: filter type not provided.");
            }

            Console.WriteLine($"Selected filter: \"{filter}\"");
            Console.WriteLine($"Source file path: \"{source}\"");
            Console.WriteLine($"Destination file path: \"{destination}\"");

            if (!File.Exists(source))
            {
                throw new ArgumentException("Error: source file doesn't exist.");
            }
            if (File.Exists(destination))
            {
                if (source == destination)
                {
                    throw new ArgumentException("Error: destination file path is equal to source file path.");
                }
                Console.WriteLine("Warning: destination file already exists.");

            }
            if (!Confirm("Proceed? [Y/n]: "))
            {
                throw new AbortedException("Abort.");
            }
        }

        internal static void HandleBitMapFileHeader(byte[] bytes, out BitMapFileHeader header)
        {
            header = new BitMapFileHeader();
            if (bytes[0] == 0x42 && bytes[1] == 0x4D)
            {
                header.bfSize = (uint)((bytes[5] << 24) + (bytes[4] << 16) + (bytes[3] << 8) + bytes[2]);
                header.bfOffBits = (uint)((bytes[13] << 24) + (bytes[12] << 16) + (bytes[11] << 8) + bytes[10]);
            }
            else if (bytes[0] == 0x4D && bytes[1] == 0x42)
            {
                throw new ArgumentException("Big-endian images are not supported.");
                /*endianness = Endianness.BigEndian;
                header.bfSize = (uint)((bytes[2] << 24) + (bytes[3] << 16) + (bytes[4] << 8) + bytes[5]);
                header.bfOffBits = (uint)((bytes[10] << 24) + (bytes[11] << 16) + (bytes[12] << 8) + bytes[13]);*/
            }
            else
            {
                throw new ArgumentException("Source is not a valid bmp file.");
            }
        }

        internal static void HandleBitMapInfoHeader(byte[] bytes, out BitMapInfoHeader infoHeader)
        {
            infoHeader = new BitMapInfoHeader
            {
                biWidth = (bytes[21] << 24) + (bytes[20] << 16) + (bytes[19] << 8) + bytes[18],
                biHeight = (bytes[25] << 24) + (bytes[24] << 16) + (bytes[23] << 8) + bytes[22],
                biBitCount = (ushort)((bytes[29] << 8) + (bytes[28]))
            };
        }

        internal static void CheckSizes(BitMapFileHeader fileHeader, BitMapInfoHeader infoHeader, int actualSize)
        {
            if (infoHeader.biBitCount != 24 && infoHeader.biBitCount != 32)
            {
                throw new ArgumentException("Error: nuber of bits per pixel other than 24 and 32 are not supported.");
            }
            if (fileHeader.bfSize !=  actualSize ||
                infoHeader.biWidth * infoHeader.biHeight * (infoHeader.biBitCount / 8) > fileHeader.bfSize)
            {
                throw new ArgumentException("Error: file contents don't match declared size.");
            }
        }

        internal static void CopyHeader(byte[] source, byte[] destination, uint headerSize)
        {
            Array.Copy(source, destination, headerSize);
        }

        internal static void ApplyKernel(
            byte[] source,
            byte[] destination,
            double[][] kernel,
            BitMapFileHeader fileHeader,
            BitMapInfoHeader infoHeader)
        {
            throw new NotImplementedException();
        }

        internal static void ApplyGreyen(
            byte[] source,
            byte[] destination,
            BitMapFileHeader fileHeader,
            BitMapInfoHeader infoHeader)
        {
            var sourceImage = new BasicImage(source, fileHeader, infoHeader);
            var destinationImage = new BasicImage(destination, fileHeader, infoHeader);
            for (int i = 0; i < infoHeader.biHeight; i++)
            {
                for (int j = 0; j < infoHeader.biWidth; j++)
                {
                    byte average = ToByte(sourceImage[i, j, ColourPart.Red] * RedLuminance
                        + sourceImage[i, j, ColourPart.Green] * GreenLuminance
                        + sourceImage[i, j, ColourPart.Blue] * BlueLuminance);
                    destinationImage[i, j, ColourPart.Red] = average;
                    destinationImage[i, j, ColourPart.Green] = average;
                    destinationImage[i, j, ColourPart.Blue] = average;
                }
            }
        }
    }
}
