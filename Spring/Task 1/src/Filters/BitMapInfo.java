package Filters;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class BitMapInfo {

    private static final int mapInFoSize = 40;

    private int biSize;
    private int biWidth;
    private int biHeight;
    private short biPlanes;
    private short biBitCount;
    private int biCompression;
    private int biSizeImage;
    private int biXPelsPerMeter;
    private int biYPelsPerMeter;
    private int biClrUsed;
    private int biClrImportant;

    BitMapInfo(int size, int width, int height, short planes, short bitCount, int compression, int sizeImage,
                            int XPelsPerMeter, int YPelsPerMeter, int clrUsed, int clrImportant) {
        this.biSize = size;
        this.biWidth = width;
        this.biHeight = height;
        this.biPlanes = planes;
        this.biBitCount = bitCount;
        this.biCompression = compression;
        this.biSizeImage = sizeImage;
        this.biXPelsPerMeter = XPelsPerMeter;
        this.biYPelsPerMeter = YPelsPerMeter;
        this.biClrUsed = clrUsed;
        this.biClrImportant = clrImportant;
    }

    public int getBiSize() {
        return biSize;
    }

    public int getBiWidth() {
        return biWidth;
    }

    public int getBiHeight() {
        return biHeight;
    }

    public short getBiBitCount() {
        return biBitCount;
    }

    public int getBiSizeImage() {
        return biSizeImage;
    }

    public boolean checkStructSize() {
        return (biSize == 40);
    }

    public boolean checkBitCount() {
        return (biBitCount == 24 || biBitCount == 32);
    }

    public byte[] toByteArray(ByteOrder byteOrder) {
        ByteBuffer tempBuffer = ByteBuffer.allocate(mapInFoSize);
        tempBuffer.order(byteOrder);

        tempBuffer.putInt(biSize);
        tempBuffer.putInt(biWidth);
        tempBuffer.putInt(biHeight);
        tempBuffer.putShort(biPlanes);
        tempBuffer.putShort(biBitCount);
        tempBuffer.putInt(biCompression);
        tempBuffer.putInt(biSizeImage);
        tempBuffer.putInt(biXPelsPerMeter);
        tempBuffer.putInt(biYPelsPerMeter);
        tempBuffer.putInt(biClrUsed);
        tempBuffer.putInt(biClrImportant);

        return tempBuffer.array();
    }
}
