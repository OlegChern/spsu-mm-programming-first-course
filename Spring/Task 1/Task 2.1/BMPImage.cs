using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Filter
{
    public struct Pixel
    {
        public int Red { get; set; }
        public int Green { get; set; }
        public int Blue { get; set; }
        public void Read(byte[] data)
        {
            Blue = data[0];
            Green = data[1];
            Red = data[2];
        }
        public byte[] Write()
        {
            var bytes = new byte[4];
            bytes[0] = (byte)Blue;
            bytes[1] = (byte)Green;
            bytes[2] = (byte)Red;
            return bytes;
        }
        public static byte Color(int value)
        {
            if (value < 0)
            {
                return 0;
            }
            else if (value > 255)
            {
                return 255;
            }
            else
            {
                return (byte)value;
            }
        }
        public void SetColor()
        {
            Red = Color(Red);
            Green = Color(Green);
            Blue = Color(Blue);
        }

        public static Pixel operator *(Pixel p, double a)
        {
            p.Blue = (int)(p.Blue * a);
            p.Green = (int)(p.Green * a);
            p.Red = (int)(p.Red * a);
            return p;
        }
        public static Pixel operator +(Pixel p1, Pixel p2)
        {
            p1.Red = p1.Red + p2.Red;
            p1.Green = p1.Green + p2.Green;
            p1.Blue = p1.Blue + p2.Blue;
            return p1;
        }
    }

    class BMPImage
    {
        public byte[] data;
        public UInt16 BitCount { get; private set; }
        public int Size { get; private set; }
        public int Width { get; private set; }
        public int Height { get; private set; }

        private int sizeHeader = sizeof(int) * 12 + sizeof(UInt16) * 3;
        
        public Pixel[,] Pixel { get; set; }
        public Pixel this[int x, int y]
        {
            get { return Pixel[x, y]; }
            set { Pixel[x, y] = value; }
        }
        public void Filter(string name)
        {
            switch (name)
            {
                case "median3x3":
                    {
                        Pixel = new MedianFilter().FilterImage(Pixel);
                        break;
                    }
                case "gauss_3x3":
                    {
                        Pixel = new GaussFilter().FilterImage(Pixel);
                        break;
                    }
                case "sobel_x":
                    {
                        Pixel = new SobelXFilter().FilterImage(Pixel);
                        break;
                    }
                case "sobel_y":
                    {
                        Pixel = new SobelYFilter().FilterImage(Pixel);
                        break;
                    }
                case "gray":
                    {
                        Pixel = new GrayFilter().FilterImage(Pixel);
                        break;
                    }
            }

        }
        public void ReadBMP(string fileName)
        {
            using (var stream = new FileStream(fileName, FileMode.Open))
            {
                data = new byte[sizeHeader];
                stream.Read(data, 0, sizeHeader);
                if ((data[0] != 0x42) || (data[1] != 0x4d))
                {
                    throw new ArgumentException("Неверный формат!");
                }
                BitCount = (UInt16)(data[28] + (data[29] << 8));
                Size = data[2] + (data[3] << 8) + (data[4] << 16) + (data[5] << 24);
                Width = data[18] + (data[19] << 8) + (data[20] << 16) + (data[21] << 24);
                Height = data[22] + (data[23] << 8) + (data[24] << 16) + (data[25] << 24);
                Pixel = new Pixel[Width, Height];
                for (int i = Height - 1; i >= 0; i--)
                {
                    for (int j = 0; j < Width; j++)
                    {
                        var bytes = new byte[BitCount / 8];
                        stream.Read(bytes, 0, BitCount / 8);
                        Pixel[j, i].Read(bytes);
                    }
                    stream.Read(new byte[4], 0, (Width * BitCount / 8) % 4);
                }
            }

        }
        public void WriteBMP(string fileName)
        {
            using (var stream = new FileStream(fileName, FileMode.Create))
            {
                stream.Write(data, 0, sizeHeader);
                for (int i = Height - 1; i >= 0; i--)
                {
                    for (int j = 0; j < Width; j++)
                    {
                        stream.Write(Pixel[j, i].Write(), 0, BitCount/ 8);
                    }
                    stream.Write(new byte[4], 0, (Width * BitCount / 8) % 4);
                }
                stream.Flush();
            }
        }
    }
}
