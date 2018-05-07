using System;
using System.IO;

namespace Task1.Filters
{
    public struct RGB
    {
        public byte rgbBlue;
        public byte rgbGreen;
        public byte rgbRed;
    }

    public class Picture
    {

        private struct BitmapFileHeader
        {
            public ushort Type;
            public uint Size;
            public ushort Reserved1;
            public ushort Reserved2;
            public uint OffBits;
        }

        private struct BitmapInfoHeader
        {
            public uint Size;
            public uint Width;
            public uint Height;
            public ushort Planes;
            public ushort BitCount;
            public uint Compression;
            public uint SizeImage;
            public uint XPelsPerMeter;
            public uint YPelsPerMeter;
            public uint ClrUsed;
            public uint ClrImportant;
        }

        private BitmapInfoHeader bitmapInfoHeader;

        private BitmapFileHeader bitmapFileHeader;

        private RGB[,] rgb;

        public Picture(FileStream file)
        {
            BinaryReader reader = new BinaryReader(file);

            bitmapFileHeader = new BitmapFileHeader();
            bitmapFileHeader.Type = reader.ReadUInt16();
            bitmapFileHeader.Size = reader.ReadUInt32();
            bitmapFileHeader.Reserved1 = reader.ReadUInt16();
            bitmapFileHeader.Reserved2 = reader.ReadUInt16();
            bitmapFileHeader.OffBits = reader.ReadUInt32();

            bitmapInfoHeader = new BitmapInfoHeader();
            bitmapInfoHeader.Size = reader.ReadUInt32();
            bitmapInfoHeader.Width = reader.ReadUInt32();
            bitmapInfoHeader.Height = reader.ReadUInt32();
            bitmapInfoHeader.Planes = reader.ReadUInt16();
            bitmapInfoHeader.BitCount = reader.ReadUInt16();
            bitmapInfoHeader.Compression = reader.ReadUInt32();
            bitmapInfoHeader.SizeImage = reader.ReadUInt32();
            bitmapInfoHeader.XPelsPerMeter = reader.ReadUInt32();
            bitmapInfoHeader.YPelsPerMeter = reader.ReadUInt32();
            bitmapInfoHeader.ClrUsed = reader.ReadUInt32();
            bitmapInfoHeader.ClrImportant = reader.ReadUInt32();

            if((bitmapInfoHeader.BitCount != 24) && (bitmapInfoHeader.BitCount != 32) || (bitmapFileHeader.Type != 0x4D42))
            {
                throw new ArgumentException();
            }

            rgb = new RGB[bitmapInfoHeader.Height, bitmapInfoHeader.Width];
            for(int i = 0; i < bitmapInfoHeader.Height; i++)
            {
                for(int j = 0; j < bitmapInfoHeader.Width; j++)
                {
                    rgb[i, j].rgbBlue = reader.ReadByte();
                    rgb[i, j].rgbGreen = reader.ReadByte();
                    rgb[i, j].rgbRed = reader.ReadByte();
                    if(bitmapInfoHeader.BitCount == 32)
                    {
                        reader.ReadByte();
                    }
                }
            }
        }

        public void WriteBMP(FileStream file)
        {
            BinaryWriter writer = new BinaryWriter(file);

            writer.Write(bitmapFileHeader.Type);
            writer.Write(bitmapFileHeader.Size);
            writer.Write(bitmapFileHeader.Reserved1);
            writer.Write(bitmapFileHeader.Reserved2);
            writer.Write(bitmapFileHeader.OffBits);

            writer.Write(bitmapInfoHeader.Size);
            writer.Write(bitmapInfoHeader.Width);
            writer.Write(bitmapInfoHeader.Height);
            writer.Write(bitmapInfoHeader.Planes);
            writer.Write(bitmapInfoHeader.BitCount);
            writer.Write(bitmapInfoHeader.Compression);
            writer.Write(bitmapInfoHeader.SizeImage);
            writer.Write(bitmapInfoHeader.XPelsPerMeter);
            writer.Write(bitmapInfoHeader.YPelsPerMeter);
            writer.Write(bitmapInfoHeader.ClrUsed);
            writer.Write(bitmapInfoHeader.ClrImportant);

            for (int i = 0; i < bitmapInfoHeader.Height; i++)
            {
                for (int j = 0; j < bitmapInfoHeader.Width; j++)
                {
                    writer.Write(rgb[i, j].rgbBlue);
                    writer.Write(rgb[i, j].rgbGreen);
                    writer.Write(rgb[i, j].rgbRed);
                    if (bitmapInfoHeader.BitCount == 32)
                    {
                        writer.Write(0);
                    }
                }
            }
        }

        public static byte DoubleToByte(double value)
        {
            if(value > 255)
            {
                return 255;
            }
            if(value < 0)
            {
                return 0;
            }
            return (byte)value;
        }

        public void ApplyFilter(IFilter filter)
        {
            RGB[,] newRGB = filter.Apply(rgb);
            rgb = newRGB;
        }
    }

}
