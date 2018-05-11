package Image;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class BitMapFileHeader {

    private short Type;
    private int Size;
    private short Reserved1;
    private short Reserved2;
    private int OffBits;

    public BitMapFileHeader(short Type, int Size, short Reserved1, short Reserved2, int OffBits) {
        this.Type = Type;
        this.Size = Size;
        this.Reserved1 = Reserved1;
        this.Reserved2 = Reserved2;
        this.OffBits = OffBits;
    }

    public BitMapFileHeader(BitMapFileHeader header) {
        this(header.Type, header.Size, header.Reserved1, header.Reserved2, header.OffBits);
    }

    public void fromByte(byte[] bytes, ByteOrder byteOrder) {
        ByteBuffer buffer = ByteBuffer.wrap(bytes);
        buffer.order(byteOrder);

        Type = buffer.getShort();
        Size = buffer.getInt();
        Reserved1 = buffer.getShort();
        Reserved2 = buffer.getShort();
        OffBits = buffer.getInt();
    }

    public byte[] toByte(ByteOrder byteOrder) {
        ByteBuffer buffer = ByteBuffer.allocate(14);
        buffer.order(byteOrder);

        buffer.putShort(Type);
        buffer.putInt(Size);
        buffer.putShort(Reserved1);
        buffer.putShort(Reserved2);
        buffer.putInt(OffBits);

        return buffer.array();
    }


    public short getType() {
        return Type;
    }

    public void setType(short Type) {
        this.Type = Type;
    }

    public int getSize() {
        return Size;
    }

    public void setSize(int Size) {
        this.Size = Size;
    }

    public short getReserved1() {
        return Reserved1;
    }

    public void setReserved1(short bfReserved1) {
        this.Reserved1 = bfReserved1;
    }

    public short getReserved2() {
        return Reserved2;
    }

    public void setReserved2(short bfReserved2) {
        this.Reserved2 = bfReserved2;
    }

    public int getOffBits() {
        return OffBits;
    }

    public void setOffBits(int bfOffBits) {
        this.OffBits = bfOffBits;
    }

    @Override
    public String toString() {
        return "BitMapFileHeader{" + "Type=" + Type + ", Size=" + Size + ", Reserved1=" + Reserved1 + ", Reserved2=" + Reserved2 + ", OffBits=" + OffBits + '}';
    }

}
