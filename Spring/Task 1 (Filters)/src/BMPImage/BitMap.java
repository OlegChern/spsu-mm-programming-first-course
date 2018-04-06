package BMPImage;

import java.security.InvalidParameterException;
import java.util.Arrays;
import java.util.Comparator;
import java.util.function.BiFunction;

public class BitMap {

    private Pixel[][] bitMap;

    public BitMap(int height, int width, int numberOfChannels) {
        bitMap = new Pixel[height][width];
        for (int i = 0; i < bitMap.length; i++) {
            for (int j = 0; j < bitMap[i].length; j++) {
                bitMap[i][j] = new Pixel(numberOfChannels);
            }
        }
    }

    public BitMap(BitMap another) {
        bitMap = new Pixel[another.bitMap.length][another.bitMap[0].length];
        for (int i = 0; i < bitMap.length; i++) {
            for (int j = 0; j < bitMap[i].length; j++) {
                bitMap[i][j] = new Pixel(another.bitMap[i][j]);
            }
        }
    }

    public void setPixel(int y, int x, Pixel elem) {
        if (bitMap[0][0].getNumberOfChannels() != elem.getNumberOfChannels()) {
            throw new InvalidParameterException("Amount of channels mismatch.");
        }

        bitMap[y][x] = elem;
    }

    public Pixel getPixel(int y, int x) {
        return bitMap[y][x];
    }

    public BitMap applyOperator(Operator operator) {
        BitMap result = new BitMap(this);

        for (int y = 0; y < bitMap.length; y++) {
            for (int x = 0; x < bitMap[y].length; x++) {
                for (int c = 0; c < bitMap[y][x].getNumberOfChannels(); c++) {
                    double sum = 0;

                    for (int i = y - operator.getSizeY() / 2; i <= y + operator.getSizeY() / 2; i++) {
                        for (int j = x - operator.getSizeX() / 2; j <= x + operator.getSizeX() / 2; j++) {
                            if (i >= 0 && i < bitMap.length && j >= 0 && j < bitMap[y].length) {
                                sum += (bitMap[i][j].getChannel(c) & 0xff) * operator.getCoefficient(
                                        i - (y - operator.getSizeY() / 2),
                                        j - (x - operator.getSizeX() / 2)
                                );
                            }
                        }
                    }

                    result.bitMap[y][x].setChannel(c, Pixel.clump(sum));
                }
            }
        }

        return result;
    }

    // computes bitmap1 by applying operator1 to this, bitmap2 by applying operator2 to this,
    // after what unites it pixel by pixel using composition
    public BitMap applyOperatorComposition(Operator operator1, Operator operator2, BiFunction<Pixel, Pixel, Pixel> composition) {
        BitMap bitMap1 = applyOperator(operator1);
        BitMap bitMap2 = applyOperator(operator2);

        for (int y = 0; y < bitMap2.bitMap.length; y++) {
            for (int x = 0; x < bitMap2.bitMap[y].length; x++) {
                bitMap2.bitMap[y][x] = composition.apply(bitMap1.bitMap[y][x], bitMap2.bitMap[y][x]);
            }
        }

        return bitMap2;
    }

    // chooses the medial value in the given region for the pixel
    // if given region size is even by one of the coordinate it
    // casts to the nearest bigger odd value because of impossibility of
    // choosing center of region by even coordinate
    public BitMap averagePixelRegion(int regionHeight, int regionWidth) {
        if (!(0 < regionHeight && regionHeight <= bitMap.length)) {
            throw new InvalidParameterException("Incorrect region height: " +
                    (regionHeight > 0 ? "too big for this image" : "negative values are not allowed"));
        }

        if (!(0 < regionWidth && regionWidth <= bitMap[0].length)) {
            throw new InvalidParameterException("Incorrect region width: " +
                    (regionWidth > 0 ? "too big for this image" : "negative values are not allowed"));
        }

        BitMap result = new BitMap(this);

        for (int y = 0; y < bitMap.length; y++) {
            for (int x = 0; x < bitMap[y].length; x++) {
                int bottom = Math.max(y - regionHeight / 2, 0);
                int top = Math.min(y + regionHeight / 2, bitMap.length - 1);
                int left = Math.max(x - regionWidth / 2, 0);
                int right = Math.min(x + regionWidth / 2, bitMap[y].length - 1);

                int currRegionHeight = top - bottom + 1;
                int currRegionWidth = right - left + 1;

                Pixel[] temp = new Pixel[currRegionHeight * currRegionWidth];
                for (int i = 0; i < currRegionHeight; i++) {
                    System.arraycopy(bitMap[bottom + i], left, temp, i * currRegionWidth, currRegionWidth);
                }

                for (int c = 0; c < bitMap[y][x].getNumberOfChannels(); c++) {
                    int channelNumber = c;
                    Arrays.sort(temp, Comparator.comparingInt(a -> a.getChannel(channelNumber) & 0xff));

                    result.bitMap[y][x].setChannel(c, temp[temp.length / 2].getChannel(c));
                }
            }
        }

        return result;
    }

    // averages first n channels
    public BitMap averageChannels(int n) {
        BitMap result = new BitMap(this);

        for (int y = 0; y < bitMap.length; y++) {
            for (int x = 0; x < bitMap[y].length; x++) {
                int sum = 0;

                for (int c = 0; c < n; c++) {
                    sum += bitMap[y][x].getChannel(c) & 0xff;
                }

                for (int c = 0; c < n; c++) {
                    result.bitMap[y][x].setChannel(c, (byte) (sum / n));
                }
            }
        }

        return result;
    }

}
