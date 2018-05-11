package Image;

import java.io.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.channels.FileChannel;
import java.util.function.BiFunction;

public class Image {

    private BitMapFileHeader fileHeader;
    private BitMapInfoHeader infoHeader;
    private BMP BMP;

    public Image(File file) throws Exception {
        try (FileChannel fc = new FileInputStream(file).getChannel()) {

            if (file.length() > Integer.MAX_VALUE) {
                throw new Exception("File is too big: " + file.length() + " bytes");
            }

            ByteBuffer buffer = ByteBuffer.allocate((int) file.length());
            buffer.order(ByteOrder.LITTLE_ENDIAN);
            fc.read(buffer);

            buffer.rewind();

            fileHeader = new BitMapFileHeader(
                    buffer.getShort(),
                    buffer.getInt(),
                    buffer.getShort(),
                    buffer.getShort(),
                    buffer.getInt()
            );

            infoHeader = new BitMapInfoHeader(
                    buffer.getInt(),
                    buffer.getInt(),
                    buffer.getInt(),
                    buffer.getShort(),
                    buffer.getShort(),
                    buffer.getInt(),
                    buffer.getInt(),
                    buffer.getInt(),
                    buffer.getInt(),
                    buffer.getInt(),
                    buffer.getInt()
            );

            if (infoHeader.getBitCount() != 24 && infoHeader.getBitCount() != 32) {
                System.err.println("Sorry, the class works only with 24- or 32-bits files. This file has " +
                        infoHeader.getBitCount() + " bit capacity.");
                throw new Exception("Unsupported bit capacity: " + infoHeader.getBitCount());
            }

            int fPos = buffer.position();
            buffer.position(fileHeader.getOffBits());
            fileHeader.setOffBits(fPos);

            int numberOfChannels = infoHeader.getBitCount() / 8;
            BMP = new BMP(infoHeader.getHeight(), infoHeader.getWidth(), numberOfChannels);

            for (int i = 0; i < infoHeader.getHeight(); i++) {
                for (int j = 0; j < infoHeader.getWidth(); j++) {
                    byte[] pixel = new byte[numberOfChannels];
                    for (int k = 0; k < pixel.length; k++) {
                        pixel[k] = buffer.get();
                    }

                    BMP.setPixel(i, j, new Pixel(pixel));
                }

                for (int k = 0; k < numberOfChannels * infoHeader.getWidth() % 4; k++) {
                    buffer.get();
                }
            }
        }
    }

    public void applyFilter(Filter filter) {
        BMP = BMP.applyFilter(filter);
    }

    public void applyFiltersComposition(Filter filter1, Filter filter2,BiFunction<Pixel, Pixel, Pixel> composition) {
        BMP = BMP.applyOperatorComposition(filter1, filter2, composition);
    }

    public void medianFilter(int regionHeight, int regionWidth) {
        BMP = BMP.averagePixelRegion(regionHeight, regionWidth);
    }

    public void makeMonochrome() {
        BMP = BMP.averageChannels(3);
    }

    public void writeDownTo(File file) throws IOException {
        try (FileOutputStream fs = new FileOutputStream(file)) {

            fs.write(fileHeader.toByte(ByteOrder.LITTLE_ENDIAN));
            fs.write(infoHeader.toByte(ByteOrder.LITTLE_ENDIAN));

            int numberOfChannels = infoHeader.getBitCount() / 8;

            ByteBuffer buffer = ByteBuffer.allocate(
                    numberOfChannels * (infoHeader.getWidth() + 4) * infoHeader.getHeight());

            for (int i = 0; i < infoHeader.getHeight(); i++) {
                for (int j = 0; j < infoHeader.getWidth(); j++) {
                    for (int k = 0; k < BMP.getPixel(i, j).getNumberOfChannels(); k++) {
                        buffer.put(BMP.getPixel(i, j).getChannel(k));
                    }
                }

                for (int k = 0; k < numberOfChannels * infoHeader.getWidth() % 4; k++) {
                    buffer.put((byte) 0);
                }
            }

            buffer.flip();

            fs.getChannel().write(buffer);
        }
    }

    public BitMapFileHeader getFileHeader() {
        return fileHeader;
    }

    public void setFileHeader(BitMapFileHeader fileHeader) {
        this.fileHeader = fileHeader;
    }

    public BitMapInfoHeader getInfoHeader() {
        return infoHeader;
    }

    public void setInfoHeader(BitMapInfoHeader infoHeader) {
        this.infoHeader = infoHeader;
    }

    public BMP getBMP () {
        return BMP;
    }

    public void setBMP(BMP BMP) {
        this.BMP = BMP;
    }

}