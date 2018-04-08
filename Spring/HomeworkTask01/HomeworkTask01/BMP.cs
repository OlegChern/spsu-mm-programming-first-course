using System;
using System.IO;

namespace HomeworkTask01
{
	public class BMP
	{
		#region structs
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
		#endregion

		#region fields
		private BitmapFileHeader fileHeader;
		private BitmapInfoHeader infoHeader;

        private uint width;
        private uint height;

        private Pixel[,] pixelArray;
		#endregion

		#region properties
        // vertical is x, horizontal is y
		public Pixel this[long x, long y]
		{
			get
			{
                if (x >= 0 && x < height && y >= 0 && y < width)
                {
                    return pixelArray[x, y];
                }

                return new Pixel { Red = 0, Green = 0, Blue = 0 };
			}
			set
            {
                if (x >= 0 && x < height && y >= 0 && y < width)
                {
                    pixelArray[x, y] = value;
                }
			}
		}

		public uint Width
		{
			get
			{
				return width;
			}
		}

		public uint Height
		{
			get
			{
				return height;
			}
		}
        #endregion

        #region public
        /// <summary>
        /// Reads BMP file
        /// </summary>
        /// <param name="sourcePath">path to file</param>
        /// <returns>BMP file</returns>
        public BMP()
        {
            fileHeader = new BitmapFileHeader();
            infoHeader = new BitmapInfoHeader();
        }

        /// <summary>
        /// Loads BMP file
        /// </summary>
        /// <param name="sourcePath">path to file</param>
        /// <returns>BMP file</returns>
        public void Load(string sourcePath)
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

                width = infoHeader.Width;
                height = infoHeader.Height;

                pixelArray = new Pixel[height, width];

                ReadPixelData(reader);
            }
        }

        /// <summary>
        /// Creates new copy of BMP
        /// </summary>
        /// <param name="targetPath">target path</param>
        public void Copy(string targetPath)
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

                int pixelSize = infoHeader.BitCount / 8; // bytes per pixel
                int padSize = (4 - ((int)width * pixelSize) % 4) % 4; // padding after line

                byte[] padding = { 0, 0, 0, 0 };

                for (int x = 0; x < height; x++)
                {
                    for (int y = 0; y < width; y++)
                    {
                        // bgr, not rgb					
                        writer.Write(pixelArray[x, y].Blue);
                        writer.Write(pixelArray[x, y].Green);
                        writer.Write(pixelArray[x, y].Red);
                    }

                    writer.Write(padding, 0, padSize);
                }
            }
		}

		private void WriteFromFileHeader(BinaryWriter writer)
		{
			writer.Write(fileHeader.Type);
			writer.Write(fileHeader.Size);
			writer.Write(fileHeader.Reserved1);
			writer.Write(fileHeader.Reserved2);
			writer.Write(fileHeader.OffBits);
		}

		private void WriteFromInfoHeader(BinaryWriter writer)
		{
			writer.Write(infoHeader.Size);
			writer.Write(infoHeader.Width);
			writer.Write(infoHeader.Height);
			writer.Write(infoHeader.Planes);
			writer.Write(infoHeader.BitCount);
			writer.Write(infoHeader.Compression);
			writer.Write(infoHeader.SizeImage);
			writer.Write(infoHeader.XPelsPerMeter);
			writer.Write(infoHeader.YPelsPerMeter);
			writer.Write(infoHeader.ClrUsed);
			writer.Write(infoHeader.ClrImportant);
		}
		#endregion

		#region readers
		private void ReadPixelData(BinaryReader reader)
		{
			int pixelSize = infoHeader.BitCount / 8; // bytes per pixel
			int padSize = (4 - ((int)width * pixelSize) % 4) % 4; // padding after line

			for (int x = 0; x < height; x++)
			{
				for (int y = 0; y < width; y++)
				{
					byte[] buffer = new byte[pixelSize];

					buffer = reader.ReadBytes(pixelSize);

					// bgr, not rgb					
					pixelArray[x, y].Red = buffer[2];
					pixelArray[x, y].Green = buffer[1];
					pixelArray[x, y].Blue = buffer[0];
				}

                reader.ReadBytes(padSize);
			}
		}

		private bool ReadToFileHeader(BinaryReader reader)
		{
			fileHeader.Type = reader.ReadUInt16();
			fileHeader.Size = reader.ReadUInt32();
			fileHeader.Reserved1 = reader.ReadUInt16();
			fileHeader.Reserved2 = reader.ReadUInt16();
			fileHeader.OffBits = reader.ReadUInt32();

			return fileHeader.Type == 0x4D42;
		}

		private bool ReadToInfoHeader(BinaryReader reader)
        {
			infoHeader.Size = reader.ReadUInt32();
			infoHeader.Width = reader.ReadUInt32();
			infoHeader.Height = reader.ReadUInt32();
			infoHeader.Planes = reader.ReadUInt16();
			infoHeader.BitCount = reader.ReadUInt16();
			infoHeader.Compression = reader.ReadUInt32();
			infoHeader.SizeImage = reader.ReadUInt32();
			infoHeader.XPelsPerMeter = reader.ReadUInt32();
			infoHeader.YPelsPerMeter = reader.ReadUInt32();
			infoHeader.ClrUsed = reader.ReadUInt32();
			infoHeader.ClrImportant = reader.ReadUInt32();

			return infoHeader.Size == 0x28;
		}
		#endregion
	}

	public struct Pixel
	{
		public byte Red;
		public byte Green;
		public byte Blue;
	}
}
