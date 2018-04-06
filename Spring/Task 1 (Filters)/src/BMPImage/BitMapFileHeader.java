package BMPImage;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class BitMapFileHeader implements ByteArrayConvertable {

    // size of all fields in bytes
    private static final int SIZE = 14;

    private short bfType;
    private int bfSize;
    private short bfReserved1;
    private short bfReserved2;
    private int bfOffBits;

    public BitMapFileHeader(short bfType, int bfSize, short bfReserved1, short bfReserved2, int bfOffBits) {
        this.bfType = bfType;
        this.bfSize = bfSize;
        this.bfReserved1 = bfReserved1;
        this.bfReserved2 = bfReserved2;
        this.bfOffBits = bfOffBits;
    }

    public BitMapFileHeader(BitMapFileHeader header) {
        this(header.bfType, header.bfSize, header.bfReserved1, header.bfReserved2, header.bfOffBits);
    }

    @Override
    public void fromByteArray(byte[] bytes, ByteOrder byteOrder) {
        ByteBuffer buffer = ByteBuffer.wrap(bytes);
        buffer.order(byteOrder);

        bfType = buffer.getShort();
        bfSize = buffer.getInt();
        bfReserved1 = buffer.getShort();
        bfReserved2 = buffer.getShort();
        bfOffBits = buffer.getInt();
    }

    @Override
    public byte[] toByteArray(ByteOrder byteOrder) {
        ByteBuffer buffer = ByteBuffer.allocate(SIZE);
        buffer.order(byteOrder);

        buffer.putShort(bfType);
        buffer.putInt(bfSize);
        buffer.putShort(bfReserved1);
        buffer.putShort(bfReserved2);
        buffer.putInt(bfOffBits);

        return buffer.array();
    }

    public short getBfType() {
        return bfType;
    }

    public void setBfType(short bfType) {
        this.bfType = bfType;
    }

    public int getBfSize() {
        return bfSize;
    }

    public void setBfSize(int bfSize) {
        this.bfSize = bfSize;
    }

    public short getBfReserved1() {
        return bfReserved1;
    }

    public void setBfReserved1(short bfReserved1) {
        this.bfReserved1 = bfReserved1;
    }

    public short getBfReserved2() {
        return bfReserved2;
    }

    public void setBfReserved2(short bfReserved2) {
        this.bfReserved2 = bfReserved2;
    }

    public int getBfOffBits() {
        return bfOffBits;
    }

    public void setBfOffBits(int bfOffBits) {
        this.bfOffBits = bfOffBits;
    }

    @Override
    public String toString() {
        return "BitMapFileHeader{" +
                "bfType=" + bfType +
                ", bfSize=" + bfSize +
                ", bfReserved1=" + bfReserved1 +
                ", bfReserved2=" + bfReserved2 +
                ", bfOffBits=" + bfOffBits +
                '}';
    }
}
