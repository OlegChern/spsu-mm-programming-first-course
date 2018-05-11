package Image;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class BitMapInfoHeader {

    private int Size;
    private int Width;
    private int Height;
    private short Planes;
    private short BitCount;
    private int Compression;
    private int SizeImage;
    private int XPelsPerMeter;
    private int YPelsPerMeter;
    private int ClrUsed;
    private int ClrImportant;

    public BitMapInfoHeader(int Size, int Width, int Height, short Planes, short BitCount, int Compression, int SizeImage, int XPelsPerMeter, int YPelsPerMeter, int biClrUsed, int ClrImportant) {
        this.Size = Size;
        this.Width = Width;
        this.Height = Height;
        this.Planes = Planes;
        this.BitCount = BitCount;
        this.Compression = Compression;
        this.SizeImage = SizeImage;
        this.XPelsPerMeter = XPelsPerMeter;
        this.YPelsPerMeter = YPelsPerMeter;
        this.ClrUsed = ClrUsed;
        this.ClrImportant = ClrImportant;
    }

    public BitMapInfoHeader(BitMapInfoHeader another) {
        this(
                another.Size,
                another.Width,
                another.Height,
                another.Planes,
                another.BitCount,
                another.Compression,
                another.SizeImage,
                another.XPelsPerMeter,
                another.YPelsPerMeter,
                another.ClrUsed,
                another.ClrImportant
        );
    }

    public void fromByte(byte[] bytes, ByteOrder byteOrder) {
        ByteBuffer buffer = ByteBuffer.wrap(bytes);
        buffer.order(byteOrder);

        Size = buffer.getInt();
        Width = buffer.getInt();
        Height = buffer.getInt();
        Planes = buffer.getShort();
        BitCount = buffer.getShort();
        Compression = buffer.getInt();
        SizeImage = buffer.getInt();
        XPelsPerMeter = buffer.getInt();
        YPelsPerMeter = buffer.getInt();
        ClrUsed = buffer.getInt();
        ClrImportant = buffer.getInt();
    }

    public byte[] toByte(ByteOrder byteOrder) {
        ByteBuffer buffer = ByteBuffer.allocate(50);
        buffer.order(byteOrder);

        buffer.putInt(Size);
        buffer.putInt(Width);
        buffer.putInt(Height);
        buffer.putShort(Planes);
        buffer.putShort(BitCount);
        buffer.putInt(Compression);
        buffer.putInt(SizeImage);
        buffer.putInt(XPelsPerMeter);
        buffer.putInt(YPelsPerMeter);
        buffer.putInt(ClrUsed);
        buffer.putInt(ClrImportant);

        return buffer.array();
    }

    public int getSize() {
        return Size;
    }

    public void setSize(int Size) {
        this.Size = Size;
    }

    public int getWidth() {
        return Width;
    }

    public void setWidth(int Width) {
        this.Width = Width;
    }

    public int getHeight() {
        return Height;
    }

    public void setHeight(int Height) {
        this.Height = Height;
    }

    public short getPlanes() {
        return Planes;
    }

    public void setPlanes(short Planes) {
        this.Planes = Planes;
    }

    public short getBitCount() {
        return BitCount;
    }

    public void setBitCount(short BitCount) {
        this.BitCount = BitCount;
    }

    public int getCompression() {
        return Compression;
    }

    public void setCompression(int Compression) {
        this.Compression = Compression;
    }

    public int getSizeImage() {
        return SizeImage;
    }

    public void setSizeImage(int SizeImage) {
        this.SizeImage = SizeImage;
    }

    public int getXPelsPerMeter() {
        return XPelsPerMeter;
    }

    public void setXPelsPerMeter(int XPelsPerMeter) {
        this.XPelsPerMeter = XPelsPerMeter;
    }

    public int getYPelsPerMeter() {
        return YPelsPerMeter;
    }

    public void setYPelsPerMeter(int YPelsPerMeter) {
        this.YPelsPerMeter = YPelsPerMeter;
    }

    public int getClrUsed() {
        return ClrUsed;
    }

    public void setClrUsed(int biClrUsed) {
        this.ClrUsed = ClrUsed;
    }

    public int getClrImportant() {
        return ClrImportant;
    }

    public void setClrImportant(int biClrImportant) {
        this.ClrImportant = ClrImportant;
    }

    @Override
    public String toString() {
        return "BitMapInfoHeader{" + "Size=" + Size + ", Width=" + Width + ", Height=" + Height + ", Planes=" + Planes + ", BitCount=" + BitCount + ", Compression=" + Compression + ", SizeImage=" + SizeImage + ", XPelsPerMeter=" + XPelsPerMeter + ", YPelsPerMeter=" + YPelsPerMeter + ", ClrUsed=" + ClrUsed + ", ClrImportant=" + ClrImportant + '}';
    }
}


