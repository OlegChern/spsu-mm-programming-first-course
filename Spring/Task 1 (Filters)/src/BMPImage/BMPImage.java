package BMPImage;

import java.io.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.channels.FileChannel;
import java.util.function.BiFunction;

public class BMPImage {

    private BitMapFileHeader fileHeader;
    private BitMapInfoHeader infoHeader;
    private BitMap bitMap;

    public BMPImage(File file) throws IOException, WrongFileFormatException {
        try (FileChannel fc = new FileInputStream(file).getChannel()) {

            if (file.length() > Integer.MAX_VALUE) {
                throw new WrongFileFormatException("File is too big: " + file.length() + " bytes");
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

            if (infoHeader.getBiBitCount() != 24 && infoHeader.getBiBitCount() != 32) {
                System.err.println("Sorry, the class works only with 24- or 32-bits files. This file has " +
                        infoHeader.getBiBitCount() + " bit capacity.");
                throw new WrongFileFormatException("Unsupported bit capacity: " + infoHeader.getBiBitCount());
            }

            // Kills the palette if it exists
            int fPos = buffer.position();
            buffer.position(fileHeader.getBfOffBits());
            fileHeader.setBfOffBits(fPos);

            int numberOfChannels = infoHeader.getBiBitCount() / 8;
            bitMap = new BitMap(infoHeader.getBiHeight(), infoHeader.getBiWidth(), numberOfChannels);

            for (int i = 0; i < infoHeader.getBiHeight(); i++) {
                for (int j = 0; j < infoHeader.getBiWidth(); j++) {
                    byte[] pixel = new byte[numberOfChannels];
                    for (int k = 0; k < pixel.length; k++) {
                        pixel[k] = buffer.get();
                    }

                    bitMap.setPixel(i, j, new Pixel(pixel));
                }

                // skip empty bytes, which complete line so it length would divided by 4 (.BMP format rule)
                for (int k = 0; k < numberOfChannels * infoHeader.getBiWidth() % 4; k++) {
                    buffer.get();
                }
            }
        }
    }

    public void applyFilter(Operator operator) {
        bitMap = bitMap.applyOperator(operator);
    }

    public void applyFiltersComposition(Operator operator1, Operator operator2, BiFunction<Pixel, Pixel, Pixel> composition) {
        bitMap = bitMap.applyOperatorComposition(operator1, operator2, composition);
    }

    public void medianFilter(int regionHeight, int regionWidth) {
        bitMap = bitMap.averagePixelRegion(regionHeight, regionWidth);
    }

    public void makeMonochrome() {
        bitMap = bitMap.averageChannels(3);
    }

    public void writeDownTo(File file) throws IOException {
        try (FileOutputStream fs = new FileOutputStream(file)) {

            fs.write(fileHeader.toByteArray(ByteOrder.LITTLE_ENDIAN));
            fs.write(infoHeader.toByteArray(ByteOrder.LITTLE_ENDIAN));

            int numberOfChannels = infoHeader.getBiBitCount() / 8;

            ByteBuffer buffer = ByteBuffer.allocate(
                    numberOfChannels * (infoHeader.getBiWidth() + 4) * infoHeader.getBiHeight());

            for (int i = 0; i < infoHeader.getBiHeight(); i++) {
                for (int j = 0; j < infoHeader.getBiWidth(); j++) {
                    for (int k = 0; k < bitMap.getPixel(i, j).getNumberOfChannels(); k++) {
                        buffer.put(bitMap.getPixel(i, j).getChannel(k));
                    }
                }

                // add empty bytes, which complete line so it length would divided by 4 (.BMP format rule)
                for (int k = 0; k < numberOfChannels * infoHeader.getBiWidth() % 4; k++) {
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

    public BitMap getBitMap() {
        return bitMap;
    }

    public void setBitMap(BitMap bitMap) {
        this.bitMap = bitMap;
    }
}