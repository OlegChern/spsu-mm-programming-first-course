package Filters;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.channels.FileChannel;

public class ImageReader {

    private File input;

    ImageReader(String path) {
        this.input = new File(path);
    }

    public BmpImage readFile() throws IOException, InvalidFileFormatException {
        FileChannel inChannel = new FileInputStream(input).getChannel();
        ByteBuffer imageBuffer = ByteBuffer.allocate((int) input.length());

        imageBuffer.order(ByteOrder.LITTLE_ENDIAN);
        inChannel.read(imageBuffer);
        imageBuffer.rewind();

        BitMapFileHeader tempHeader = new BitMapFileHeader(
                imageBuffer.getShort(),
                imageBuffer.getInt(),
                imageBuffer.getShort(),
                imageBuffer.getShort(),
                imageBuffer.getInt()
        );

        BitMapInfo tempMapInfo = new BitMapInfo(
                imageBuffer.getInt(),
                imageBuffer.getInt(),
                imageBuffer.getInt(),
                imageBuffer.getShort(),
                imageBuffer.getShort(),
                imageBuffer.getInt(),
                imageBuffer.getInt(),
                imageBuffer.getInt(),
                imageBuffer.getInt(),
                imageBuffer.getInt(),
                imageBuffer.getInt()
        );

        if (tempMapInfo.getBiBitCount() != 24 && tempMapInfo.getBiBitCount() != 32)
            throw new InvalidFileFormatException("Unsupported bit capacity: " + tempMapInfo.getBiBitCount());

        BitMap tempMap = new BitMap(tempMapInfo.getBiBitCount() / 8, tempMapInfo.getBiHeight(), tempMapInfo.getBiWidth());
        BitMap tempNewMap = new BitMap(tempMapInfo.getBiBitCount() / 8, tempMapInfo.getBiHeight(), tempMapInfo.getBiWidth());

        Integer padding = (4 - (tempMapInfo.getBiWidth() * (tempMapInfo.getBiBitCount() / 8) % 4) & 3);

        for (int i = 2; i < tempMapInfo.getBiHeight() + 2; i++) {
            for (int j = 2; j < tempMapInfo.getBiWidth() + 2; j++) {
                tempMap.getPixel(i, j).setPixel(
                        imageBuffer.get(),
                        imageBuffer.get(),
                        imageBuffer.get()
                );
                tempNewMap.getPixel(i, j).setPixel(tempMap.getPixel(i, j));
                if (tempMapInfo.getBiBitCount() / 8 == 4) imageBuffer.get();
            }

            for (int k = 0; k < padding; k++) {
                imageBuffer.get();
            }
        }

        return new BmpImage(tempHeader, tempMapInfo, tempMap, tempNewMap);
    }
}



