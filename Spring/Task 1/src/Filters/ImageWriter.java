package Filters;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class ImageWriter {

    private BmpImage image;
    private File output;

    ImageWriter(BmpImage image, String outPath) {
        this.image = image;
        this.output = new File(outPath);
    }

    public void writeFile() throws IOException {
        FileOutputStream outStream = new FileOutputStream(output);

        outStream.write(image.getHeader().toByteArray(ByteOrder.LITTLE_ENDIAN));
        outStream.write(image.getMapInfo().toByteArray(ByteOrder.LITTLE_ENDIAN));

        int channels = image.getMapInfo().getBiBitCount() / 8;
        ByteBuffer buffer = ByteBuffer.allocate(channels * (image.getWidth() + 4) * image.getHeight());

        BitMap tempMap = image.getNewMap();

        for (int i = 2; i < image.getHeight() + 2; i++) {
            for (int j = 2; j < image.getWidth() + 2; j++) {
                tempMap.getPixel(i, j).putPixel(buffer, channels);
            }

            for (int k = 0; k < channels * image.getWidth() % 4; k++) {
                buffer.put((byte) 0);
            }
        }

        buffer.flip();

        outStream.write(buffer.array());
    }
}
