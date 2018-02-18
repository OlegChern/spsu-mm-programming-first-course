using System;
using System.IO;

namespace task1
{
    enum ColourPart
    {
        Red = 0,
        Green = 1,
        Blue = 2,
        Alpha = 3
    }

    internal enum Endianness
    {
        BigEndian,
        LittleEndian
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

            try
            {
                File.OpenWrite(destination).Close();
            }
            catch (Exception inner)
            {
                throw new IOException("Error: couldn't write to destination file.", inner);
            }
        }

        internal static void HandleBitMapFileHeader(byte[] bytes, out BitMapFileHeader header, out Endianness endianness)
        {
            header = new BitMapFileHeader();
            if (bytes[0] == 0x42 && bytes[1] == 0x4D)
            {
                endianness = Endianness.LittleEndian;
                header.bfSize = (uint)((bytes[5] << 24) + (bytes[4] << 16) + (bytes[3] << 8) + bytes[2]);
                header.bfOffBits = (uint)((bytes[13] << 24) + (bytes[12] << 16) + (bytes[11] << 8) + bytes[10]);
            }
            else if (bytes[0] == 0x4D && bytes[1] == 0x42)
            {
                endianness = Endianness.BigEndian;
                header.bfSize = (uint)((bytes[2] << 24) + (bytes[3] << 16) + (bytes[4] << 8) + bytes[5]);
                header.bfOffBits = (uint)((bytes[10] << 24) + (bytes[11] << 16) + (bytes[12] << 8) + bytes[13]);
            }
            else
            {
                throw new ArgumentException("Source is not a valid bmp file.");
            }
        }

        internal static void HandleBitMapInfoHeader(byte[] bytes, out BitMapInfoHeader infoHeader, Endianness endianness)
        {
            infoHeader = new BitMapInfoHeader();
            if (endianness == Endianness.LittleEndian)
            {
                infoHeader.biWidth = (bytes[21] << 24) + (bytes[20] << 16) + (bytes[19] << 8) + bytes[18];
                infoHeader.biHeight = (bytes[25] << 24) + (bytes[24] << 16) + (bytes[23] << 8) + bytes[22];
                infoHeader.biBitCount = (ushort)((bytes[29] << 8) + (bytes[28]));
            }
            else
            {
                infoHeader.biWidth = (bytes[18] << 24) + (bytes[19] << 16) + (bytes[20] << 8) + bytes[21];
                infoHeader.biHeight = (bytes[22] << 24) + (bytes[23] << 16) + (bytes[24] << 8) + bytes[25];
                infoHeader.biBitCount = (ushort)((bytes[28] << 8) + (bytes[29]));
            }
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
            BitMapInfoHeader infoHeader,
            Endianness endianness)
        {
            // TODO: finish
        }

        internal static void ApplyGreyen(
            byte[] source,
            byte[] destination,
            BitMapFileHeader fileHeader,
            BitMapInfoHeader infoHeader,
            Endianness endianness)
        {
            // TODO: finish
        }
    }
}

#if false
// Image is considered to be 2 pixels wider
// and 2 pixels higher than it actually is,
// forming black outline out of those extra pixels,
// so that 3x3 kernel can be applied.

int applyKernel(BITMAPINFOHEADER *infoHeader, const double kernel[3][3],
                FILE *fileStreamIn, FILE *fileStreamOut, unsigned char (*castFunction)(double))
{
    int result;
    size_t bytesPerPixel = (size_t)  infoHeader->biBitCount / 8;
    int rowSize = (infoHeader->biBitCount * infoHeader->biWidth + 31) / 32 * 4;

    // Line length in file should always be a multiple of 4 bytes.
    // Hence, gap sometimes has to be added.

    int gap = rowSize - bytesPerPixel * infoHeader->biWidth;
    char *gapBuffer = NULL;
    if (gap != 0)
    {
        gapBuffer = malloc(sizeof(char) * gap);
    }

    // Initialize variables

    // Following arrays contain lines of bytes as stored in file
    // They also provide buffers of 1 black pixel in the beginning and end
    // so that kernel can be propperly applied.
    // They don't contain any space for gap

    unsigned char *previous = calloc(sizeof(unsigned char), bytesPerPixel * (infoHeader->biWidth + 2));
    // Since no previous line exists, let it be black.
    // calloc is more efficient than malloc + manually setting colours to black
    unsigned char *current = malloc(sizeof(unsigned char) * bytesPerPixel * (infoHeader->biWidth + 2));
    unsigned char *next = malloc(sizeof(unsigned char) * bytesPerPixel * (infoHeader->biWidth + 2));

    // Make sure buffer pixels of current and next are black
    // (pixels of previous are all black anyway)

    for (int i = 0; i < bytesPerPixel; i++)
    {
        // Pixel at the start...
        current[i] = 0;
        next[i] = 0;
        // ...and at the end.
        current[bytesPerPixel * (infoHeader->biWidth + 1) + i] = 0;
        next[bytesPerPixel * (infoHeader->biWidth + 1) + i] = 0;
    }

    // Read first line (and it's gap if necessary).

    result = fread(current + bytesPerPixel, sizeof(unsigned char), bytesPerPixel * infoHeader->biWidth, fileStreamIn);
    FILTER_ASSERT(result == bytesPerPixel * infoHeader->biWidth, "Error reading image line.\n")

    if (gap != 0)
    {
        result = fread(gapBuffer, sizeof(unsigned char), (size_t) gap, fileStreamIn);
        FILTER_ASSERT(result == gap, "Error reading line gap.\n")
    }

    // Now, apply kernel to lines.

    for (int i = 0; i < infoHeader->biHeight; i++)
    {
        // Read next line
        // Or clear it, if the image is over

        if (i != infoHeader->biHeight - 1)
        {
            result = fread(next + bytesPerPixel, sizeof(unsigned char), bytesPerPixel * infoHeader->biWidth, fileStreamIn);
            FILTER_ASSERT(result == bytesPerPixel * infoHeader->biWidth, "Error reading image line.\n")
        }
        else
        {
            for (int j = bytesPerPixel; j < bytesPerPixel * (infoHeader->biWidth + 1); j++)
            {
                next[j] = 0;
            }
            // next[j] for other j's are 0 anyay
        }

        // Apply kernel
        // In fact, we don't have to care which byte means what,
        // we can work with all ow them in the same way.

        for (int j = bytesPerPixel; j < bytesPerPixel * (infoHeader->biWidth + 1); j++)
        {
            // previous[j - bytesPerPixel], previous[j], previous[j + bytesPerPixel],
            // current[j - bytesPerPixel],  current[j],  current[j + bytesPerPixel],
            // next[j - bytesPerPixel],     next[j],     next[j + bytesPerPixel].

            // We don't need to know which value exactly it represents
            double newValue =
                    kernel[0][0] * previous[j - bytesPerPixel] +
                    kernel[0][1] * previous[j] +
                    kernel[0][2] * previous[j + bytesPerPixel] +

                    kernel[1][0] * current[j - bytesPerPixel] +
                    kernel[1][1] * current[j] +
                    kernel[1][2] * current[j + bytesPerPixel] +

                    kernel[2][0] * next[j - bytesPerPixel] +
                    kernel[2][1] * next[j] +
                    kernel[2][2] * next[j + bytesPerPixel];

            unsigned char newByte = (*castFunction)(newValue);

            result = fwrite(&newByte, sizeof(unsigned char), 1, fileStreamOut);
            FILTER_ASSERT(result == 1, "Error saving image line.\n")
        }

        // Read & write gap if necessary

        if (gap != 0)
        {
            result = fwrite(gapBuffer, sizeof(unsigned char), (size_t) gap, fileStreamOut);
            FILTER_ASSERT(result == gap, "Error saving line gap.\n")

            if (i != infoHeader->biHeight - 1)
            {
                // This gap can't and doesn't have to be read
                // Since {next} is currently just a black buffer
                result = fread(gapBuffer, sizeof(unsigned char), (size_t) gap, fileStreamIn);
                FILTER_ASSERT(result == gap, "Error reading line gap.\n")
            }
        }

        // Swap lines.
        // {next} doesn't have to be cleared
        // since its contents are going to be overwritten anyway

        unsigned char *tmp = previous;
        previous = current;
        current = next;
        next = tmp;
    }

    if (gap != 0)
    {
        free(gapBuffer);
    }

    free(previous);
    free(current);
    free(next);

    return 0;
}

int applyGreyen(BITMAPINFOHEADER *infoHeader, FILE *fileStreamIn, FILE *fileStreamOut, int platform)
{
    int result;
    size_t bytesPerPixel = (size_t) infoHeader->biBitCount / 8;
    size_t rowSize = (size_t) (infoHeader->biBitCount * infoHeader->biWidth + 31) / 32 * 4;

    // In this method we can merge {gapBuffer} with {line}

    unsigned char *line = malloc(sizeof(unsigned char) * rowSize);

    // Apply filter to lines

    for (int i = 0; i < infoHeader->biHeight; i++)
    {
        result = fread(line, sizeof(unsigned char), rowSize, fileStreamIn);
        if (result != rowSize)
        {
            printf("Error reading line.\n");
            free(line);
            return 1;
        }

        // Modify line in-place

        int j = 0;
        while (j < bytesPerPixel * infoHeader->biWidth)
        {
            // Keep alpha channel
            if (bytesPerPixel == 4 && platform == LITTLE_ENDIAN)
            {
                j++;
            }

            double newValue = 0;

            if (platform == BIG_ENDIAN)
            {
                newValue =
                        LUMINANCE_RED * line[j] +
                        LUMINANCE_GREEN * line[j + 1] +
                        LUMINANCE_BLUE * line[j + 2];
            }
            else
            {
                newValue =
                        LUMINANCE_BLUE * line[j] +
                        LUMINANCE_GREEN * line[j + 1] +
                        LUMINANCE_RED * line[j + 2];
            }

            // This cast is always valid.
            unsigned char newByte = (unsigned char) newValue;

            line[j] = newByte;
            line[j + 1] = newByte;
            line[j + 2] = newByte;

            // Keep alpha channel
            if (bytesPerPixel == 4 && platform == BIG_ENDIAN)
            {
                j++;
            }

            j += 3;
        }

        // Save modification results. Gap bytes stay untouched.

        result = fwrite(line, sizeof(unsigned char), rowSize, fileStreamOut);
        if (result != rowSize)
        {
            printf("Error saving line.\n");
            free(line);
            return 1;
        }
    }

    free(line);

    return 0;
}

#endif
