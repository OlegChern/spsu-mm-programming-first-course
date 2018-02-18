using System;

namespace task1
{
    internal sealed class BasicImage
    {
        private byte[] data;

        private int width;
        private int actualWidth;
        // Line length in bmp file is not equal to image width * 
        private int height;
        private uint offset;
        private int bytesPerPixel;
        private Endianness endianness;

        /// <summary>
        /// Accesses pixel at [i, j]
        /// </summary>
        /// <param name="i">row</param>
        /// <param name="j">column</param>
        /// <param name="part">part of colour accessed</param>
        /// <returns>Selected part of pixel at [i, j]</returns>
        internal byte this[int i, int j, ColourPart part]
        {
            get
            {
                if (part == ColourPart.Alpha && bytesPerPixel == 3)
                {
                    throw new ArgumentException("Error: attempt to read alpha channel which is not provided.");
                }
                if (i < 0 || i >= height || j < 0 || j >= width)
                {
                    return 0;
                }
                int start = (int)(offset + i * actualWidth + j * bytesPerPixel);
                switch (part)
                {
                    case ColourPart.Red:
                        if (endianness == Endianness.BigEndian)
                        {
                            return 0;
                        }
                        else
                        {
                            return 0;
                        }
                    case ColourPart.Green:
                        if (endianness == Endianness.BigEndian) return 0;
                        else
                        {
                            return 0;
                        }
                    case ColourPart.Blue:
                        if (endianness == Endianness.BigEndian)
                        {
                            return 0;
                        }
                        else
                        {
                            return 0;
                        }
                    case ColourPart.Alpha:
                        if (endianness == Endianness.BigEndian)
                        {
                            return 0;
                        }
                        else
                        {
                            return 0;
                        }
                    default:
                        return 0;
                }
                return data[start + (part == ColourPart.Red? 0: part == ColourPart.Green? 1: part == ColourPart.Blue? 2: 3)];
            }
            set => data[i] = value;
        }
        
        public BasicImage(byte[] data, BitMapFileHeader fileHeader, BitMapInfoHeader infoHeader, Endianness endianness)
        {
            Util.CheckSizes(fileHeader, infoHeader, data.Length);
            width = infoHeader.biWidth;
            actualWidth = ((infoHeader.biBitCount * width + 31) / 32) * 4;
            height = infoHeader.biHeight;
            offset = fileHeader.bfOffBits;
            bytesPerPixel = infoHeader.biBitCount;
            this.data = data;
            this.endianness = endianness;
        }
    }
}
