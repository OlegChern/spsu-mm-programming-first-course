package Filters;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class BitMapFileHeader {

    private static final int headerSize = 14;

    private short bfType;
    private int bfSize;
    private short bfReserved1;
    private short bfReserved2;
    private int bfOffBits;

    BitMapFileHeader(short type, int size, short reserved1, short reserved2, int offBits) {
        this.bfType = type;
        this.bfSize = size;
        this.bfReserved1 = reserved1;
        this.bfReserved2 = reserved2;
        this.bfOffBits = offBits;
    }

    public short getType() {
        return bfType;
    }

    public int getSize() {
        return bfSize;
    }

    public short getReserved1() {
        return bfReserved1;
    }

    public short getReserved2() {
        return bfReserved2;
    }

    public int getOffBits() {
        return bfOffBits;
    }

    public boolean checkIfValidType() {
        return (bfType == 0x4D42);
    }

    public byte[] toByteArray(ByteOrder byteOrder) {
        ByteBuffer tempBuffer = ByteBuffer.allocate(headerSize);
        tempBuffer.order(byteOrder);

        tempBuffer.putShort(bfType);
        tempBuffer.putInt(bfSize);
        tempBuffer.putShort(bfReserved1);
        tempBuffer.putShort(bfReserved2);
        tempBuffer.putInt(bfOffBits);

        return tempBuffer.array();
    }


}
