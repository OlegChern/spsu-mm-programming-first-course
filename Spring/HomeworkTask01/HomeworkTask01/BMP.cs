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

		#region private properties
		private BinaryReader binary;
		private BitmapFileHeader fileHeader;
		private BitmapInfoHeader infoHeader;
		private Pixel[,] pixelArray { get; }
		#endregion

		#region private properties
		public Pixel this[long x, long y]
		{
			get
			{
				return pixelArray[x, y];
			}
			set
			{
				pixelArray[x, y] = value;
			}
		}
		public uint Width
		{
			get
			{
				return infoHeader.Width;
			}
		}
		public uint Height
		{
			get
			{
				return infoHeader.Height;
			}
		}
		#endregion

		#region constructor
		/// <summary>
		/// Reads BMP file
		/// </summary>
		/// <param name="sourcePath">path to file</param>
		/// <returns>BMP file</returns>
		public BMP(string sourcePath)
		{
			try
			{
				binary = new BinaryReader(File.OpenRead(sourcePath));
			}
			catch
			{
				throw new ArgumentException("Can't read file!");
			}

			if (!ReadToFileHeader())
			{
				throw new ArgumentException("Wrong file header size!");
			}

			if (!ReadToInfoHeader())
			{
				throw new ArgumentException("Wrong info header size!");
			}

			pixelArray = new Pixel[infoHeader.Height, infoHeader.Width];

			ReadPixelData();
		}

		~BMP()
		{
			if (binary != null)
			{
				binary.Close();
			}
		}
		#endregion

		#region writers
		/// <summary>
		/// Creates BMP file
		/// </summary>
		/// <param name="targetPath">target path</param>
		public void Create(string targetPath)
		{
			try
			{
				BinaryWriter writer = new BinaryWriter(File.Create(targetPath));
				WritePixelData(writer);
			}
			catch
			{
				throw new ArgumentException("Can't create file!");
			}
		}

		private void WritePixelData(BinaryWriter writer)
		{
			WriteFromFileHeader(writer);
			WriteFromInfoHeader(writer);

			int width = (int)infoHeader.Width;
			int height = (int)infoHeader.Height;

			int pixelSize = infoHeader.BitCount / 8; // bytes per pixel
			int padSize = (4 - (width * pixelSize) % 4) % 4; // padding after line

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
		private void ReadPixelData()
		{
			int width = (int)infoHeader.Width;
			int height = (int)infoHeader.Height;

			int pixelSize = infoHeader.BitCount / 8; // bytes per pixel
			int padSize = (4 - (width * pixelSize) % 4) % 4; // padding after line

			for (int x = 0; x < height; x++)
			{
				for (int y = 0; y < width; y++)
				{
					byte[] buffer = new byte[pixelSize];

					buffer = binary.ReadBytes(pixelSize);

					// bgr, not rgb					
					pixelArray[x, y].Red = buffer[2];
					pixelArray[x, y].Green = buffer[1];
					pixelArray[x, y].Blue = buffer[0];
				}

				binary.ReadBytes(padSize);
			}
		}

		private bool ReadToFileHeader()
		{
			fileHeader = new BitmapFileHeader();

			fileHeader.Type = binary.ReadUInt16();
			fileHeader.Size = binary.ReadUInt32();
			fileHeader.Reserved1 = binary.ReadUInt16();
			fileHeader.Reserved2 = binary.ReadUInt16();
			fileHeader.OffBits = binary.ReadUInt32();

			return fileHeader.Type == 0x4D42;
		}

		private bool ReadToInfoHeader()
		{
			infoHeader = new BitmapInfoHeader();

			infoHeader.Size = binary.ReadUInt32();
			infoHeader.Width = binary.ReadUInt32();
			infoHeader.Height = binary.ReadUInt32();
			infoHeader.Planes = binary.ReadUInt16();
			infoHeader.BitCount = binary.ReadUInt16();
			infoHeader.Compression = binary.ReadUInt32();
			infoHeader.SizeImage = binary.ReadUInt32();
			infoHeader.XPelsPerMeter = binary.ReadUInt32();
			infoHeader.YPelsPerMeter = binary.ReadUInt32();
			infoHeader.ClrUsed = binary.ReadUInt32();
			infoHeader.ClrImportant = binary.ReadUInt32();

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
