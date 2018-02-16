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

        /// <summary>
        /// Accesses pixel at [i, j]
        /// </summary>
        /// <param name="i">row</param>
        /// <param name="j">column</param>
        /// <param name="part">part of colour accessed</param>
        /// <returns>Selected part of pixel at [i, j]</returns>
        internal byte this[int i, int j, ColourPart part]
        {
            // TODO: make propper assignment
            get
            {
                if (i < 0 || i >= height || j < 0 || j >= width)
                {
                    return 0;
                }
                return 1;
            }
            set => data[i] = value;
        }
        
        public BasicImage(byte[] data, BitMapFileHeader fileHeader, BitMapInfoHeader infoHeader)
        {
            Util.CheckSizes(fileHeader, infoHeader, data.Length);
            width = infoHeader.biWidth;
            // TODO: initialize actualWidth
            height = infoHeader.biHeight;
            offset = fileHeader.bfOffBits;
            this.data = data;
        }
    }
}
