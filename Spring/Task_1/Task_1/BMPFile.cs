using System;
using System.IO;

namespace Task_1
{
    internal class BMPFile
    {
        #region fields

        private BitmapFileHeader _fileHeader;
        private BitmapInfoHeader _infoHeader;

        private Pixel[,] _pixelArray;

        #endregion

        #region properties

        public int Width { get; private set; }


        public int Height { get; private set; }

        internal Pixel this[int x, int y]
        {
            get
            {
                if (x >= 0 && x < Width && y >= 0 && y < Height)
                {
                    return _pixelArray[x, y];
                }

                return new Pixel {Red = 0, Green = 0, Blue = 0};
            }
            set
            {
                if (x >= 0 && x < Width && y >= 0 && y < Height)
                {
                    _pixelArray[x, y] = value;
                }
            }
        }
        
        #endregion

        #region workWithPaths

        internal void LoadFile(string sourcePath)
        {
            using (BinaryReader reader = new BinaryReader(File.OpenRead(sourcePath)))
            {
                if (!ReadToFileHeader(reader))
                {
                    throw new ArgumentException("Wrong file header size!");
                }

                if (!ReadToInfoHeader(reader))
                {
                    throw new ArgumentException("Wrong info header size!");
                }

                Width = _infoHeader.Width;
                Height = _infoHeader.Height;

                _pixelArray = new Pixel[Width, Height];

                ReadPixelData(reader);
            }
        }

        public void CreateFile(string targetPath)
        {
            try
            {
                WritePixelData(targetPath);
            }
            catch
            {
                throw new ArgumentException("Can't create file!");
            }
        }

        #endregion

        #region writers

        private void WritePixelData(string targetPath)
        {
            using (BinaryWriter writer = new BinaryWriter(File.Create(targetPath)))
            {
                WriteFromFileHeader(writer);
                WriteFromInfoHeader(writer);

                int pixelSize = _infoHeader.BitCount / 8;
                int padSize = (4 - Width * pixelSize % 4) % 4;

                byte[] padding = {0, 0, 0, 0};

                for (int x = 0; x < Width; x++)
                {
                    for (int y = 0; y < Height; y++)
                    {
                        writer.Write(_pixelArray[x, y].Blue);
                        writer.Write(_pixelArray[x, y].Green);
                        writer.Write(_pixelArray[x, y].Red);
                    }

                    writer.Write(padding, 0, padSize);
                }
            }
        }

        private void WriteFromFileHeader(BinaryWriter writer)
        {
            writer.Write(_fileHeader.Type);
            writer.Write(_fileHeader.Size);
            writer.Write(_fileHeader.Reserved1);
            writer.Write(_fileHeader.Reserved2);
            writer.Write(_fileHeader.OffBits);
        }

        private void WriteFromInfoHeader(BinaryWriter writer)
        {
            writer.Write(_infoHeader.Size);
            writer.Write(_infoHeader.Width);
            writer.Write(_infoHeader.Height);
            writer.Write(_infoHeader.Planes);
            writer.Write(_infoHeader.BitCount);
            writer.Write(_infoHeader.Compression);
            writer.Write(_infoHeader.SizeImage);
            writer.Write(_infoHeader.XPelsPerMeter);
            writer.Write(_infoHeader.YPelsPerMeter);
            writer.Write(_infoHeader.ClrUsed);
            writer.Write(_infoHeader.ClrImportant);
        }

        #endregion

        #region readers

        private void ReadPixelData(BinaryReader reader)
        {
            int pixelSize = _infoHeader.BitCount / 8;
            int padSize = (4 - (Width * pixelSize) % 4) % 4;

            for (int x = 0; x < Width; x++)
            {
                for (int y = 0; y < Height; y++)
                {
                    byte[] buffer = new byte[pixelSize];

                    buffer = reader.ReadBytes(pixelSize);

                    _pixelArray[x, y].Red = buffer[2];
                    _pixelArray[x, y].Green = buffer[1];
                    _pixelArray[x, y].Blue = buffer[0];
                }

                reader.ReadBytes(padSize);
            }
        }

        private bool ReadToFileHeader(BinaryReader reader)
        {
            _fileHeader.Type = reader.ReadInt16();
            _fileHeader.Size = reader.ReadInt32();
            _fileHeader.Reserved1 = reader.ReadInt16();
            _fileHeader.Reserved2 = reader.ReadInt16();
            _fileHeader.OffBits = reader.ReadInt32();

            return _fileHeader.Type == 0x4D42;
        }

        private bool ReadToInfoHeader(BinaryReader reader)
        {
            _infoHeader.Size = reader.ReadInt32();
            _infoHeader.Width = reader.ReadInt32();
            _infoHeader.Height = reader.ReadInt32();
            _infoHeader.Planes = reader.ReadInt16();
            _infoHeader.BitCount = reader.ReadInt16();
            _infoHeader.Compression = reader.ReadInt32();
            _infoHeader.SizeImage = reader.ReadInt32();
            _infoHeader.XPelsPerMeter = reader.ReadInt32();
            _infoHeader.YPelsPerMeter = reader.ReadInt32();
            _infoHeader.ClrUsed = reader.ReadInt32();
            _infoHeader.ClrImportant = reader.ReadInt32();

            return _infoHeader.Size == 0x28;
        }

        #endregion
    }
}
