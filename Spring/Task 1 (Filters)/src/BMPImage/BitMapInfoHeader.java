package BMPImage;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class BitMapInfoHeader implements ByteArrayConvertable {

    // size of all fields in bytes
    private static final int SIZE = 40;

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

    public BitMapInfoHeader(int biSize, int biWidth, int biHeight, short biPlanes, short biBitCount,
                            int biCompression, int biSizeImage, int biXPelsPerMeter, int biYPelsPerMeter,
                            int biClrUsed, int biClrImportant) {
        this.biSize = biSize;
        this.biWidth = biWidth;
        this.biHeight = biHeight;
        this.biPlanes = biPlanes;
        this.biBitCount = biBitCount;
        this.biCompression = biCompression;
        this.biSizeImage = biSizeImage;
        this.biXPelsPerMeter = biXPelsPerMeter;
        this.biYPelsPerMeter = biYPelsPerMeter;
        this.biClrUsed = biClrUsed;
        this.biClrImportant = biClrImportant;
    }

    public BitMapInfoHeader(BitMapInfoHeader another) {
        this(
                another.biSize,
                another.biWidth,
                another.biHeight,
                another.biPlanes,
                another.biBitCount,
                another.biCompression,
                another.biSizeImage,
                another.biXPelsPerMeter,
                another.biYPelsPerMeter,
                another.biClrUsed,
                another.biClrImportant
        );
    }

    @Override
    public void fromByteArray(byte[] bytes, ByteOrder byteOrder) {
        ByteBuffer buffer = ByteBuffer.wrap(bytes);
        buffer.order(byteOrder);

        biSize = buffer.getInt();
        biWidth = buffer.getInt();
        biHeight = buffer.getInt();
        biPlanes = buffer.getShort();
        biBitCount = buffer.getShort();
        biCompression = buffer.getInt();
        biSizeImage = buffer.getInt();
        biXPelsPerMeter = buffer.getInt();
        biYPelsPerMeter = buffer.getInt();
        biClrUsed = buffer.getInt();
        biClrImportant = buffer.getInt();
    }

    @Override
    public byte[] toByteArray(ByteOrder byteOrder) {
        ByteBuffer buffer = ByteBuffer.allocate(SIZE);
        buffer.order(byteOrder);

        buffer.putInt(biSize);
        buffer.putInt(biWidth);
        buffer.putInt(biHeight);
        buffer.putShort(biPlanes);
        buffer.putShort(biBitCount);
        buffer.putInt(biCompression);
        buffer.putInt(biSizeImage);
        buffer.putInt(biXPelsPerMeter);
        buffer.putInt(biYPelsPerMeter);
        buffer.putInt(biClrUsed);
        buffer.putInt(biClrImportant);

        return buffer.array();
    }

    public int getBiSize() {
        return biSize;
    }

    public void setBiSize(int biSize) {
        this.biSize = biSize;
    }

    public int getBiWidth() {
        return biWidth;
    }

    public void setBiWidth(int biWidth) {
        this.biWidth = biWidth;
    }

    public int getBiHeight() {
        return biHeight;
    }

    public void setBiHeight(int biHeight) {
        this.biHeight = biHeight;
    }

    public short getBiPlanes() {
        return biPlanes;
    }

    public void setBiPlanes(short biPlanes) {
        this.biPlanes = biPlanes;
    }

    public short getBiBitCount() {
        return biBitCount;
    }

    public void setBiBitCount(short biBitCount) {
        this.biBitCount = biBitCount;
    }

    public int getBiCompression() {
        return biCompression;
    }

    public void setBiCompression(int biCompression) {
        this.biCompression = biCompression;
    }

    public int getBiSizeImage() {
        return biSizeImage;
    }

    public void setBiSizeImage(int biSizeImage) {
        this.biSizeImage = biSizeImage;
    }

    public int getBiXPelsPerMeter() {
        return biXPelsPerMeter;
    }

    public void setBiXPelsPerMeter(int biXPelsPerMeter) {
        this.biXPelsPerMeter = biXPelsPerMeter;
    }

    public int getBiYPelsPerMeter() {
        return biYPelsPerMeter;
    }

    public void setBiYPelsPerMeter(int biYPelsPerMeter) {
        this.biYPelsPerMeter = biYPelsPerMeter;
    }

    public int getBiClrUsed() {
        return biClrUsed;
    }

    public void setBiClrUsed(int biClrUsed) {
        this.biClrUsed = biClrUsed;
    }

    public int getBiClrImportant() {
        return biClrImportant;
    }

    public void setBiClrImportant(int biClrImportant) {
        this.biClrImportant = biClrImportant;
    }

    @Override
    public String toString() {
        return "BitMapInfoHeader{" +
                "biSize=" + biSize +
                ", biWidth=" + biWidth +
                ", biHeight=" + biHeight +
                ", biPlanes=" + biPlanes +
                ", biBitCount=" + biBitCount +
                ", biCompression=" + biCompression +
                ", biSizeImage=" + biSizeImage +
                ", biXPelsPerMeter=" + biXPelsPerMeter +
                ", biYPelsPerMeter=" + biYPelsPerMeter +
                ", biClrUsed=" + biClrUsed +
                ", biClrImportant=" + biClrImportant +
                '}';
    }
}
