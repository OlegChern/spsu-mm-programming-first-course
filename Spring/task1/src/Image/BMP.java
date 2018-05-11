package Image;

import java.security.InvalidParameterException;
import java.util.Arrays;
import java.util.Comparator;
import java.util.function.BiFunction;

public class BMP {

    private Pixel[][] BMP;


    public BMP(int height, int width, int numberOfChannels) {
        BMP = new Pixel[height][width];
        for (int i = 0; i < BMP.length; i++) {
            for (int j = 0; j < BMP[i].length; j++) {
                BMP[i][j] = new Pixel(numberOfChannels);
            }
        }
    }

    public BMP(BMP another) {
        BMP = new Pixel[another.BMP.length][another.BMP[0].length];
        for (int i = 0; i < BMP.length; i++) {
            for (int j = 0; j < BMP[i].length; j++) {
                BMP[i][j] = new Pixel(another.BMP[i][j]);
            }
        }
    }

    public void setPixel(int y, int x, Pixel element) {
        if (BMP[0][0].getNumberOfChannels() != element.getNumberOfChannels()) {
            throw new InvalidParameterException("Amount of channels mismatch.");
        }

        BMP[y][x] = element;
    }

    public Pixel getPixel(int y, int x) {
        return BMP[y][x];
    }


    public BMP applyFilter(Filter filter) {
        BMP result = new BMP(this);

        for (int y = 0; y < BMP.length; y++) {
            for (int x = 0; x < BMP[y].length; x++) {
                for (int c = 0; c < BMP[y][x].getNumberOfChannels(); c++) {
                    double sum = 0;

                    for (int i = y - filter.getSizeY() / 2; i <= y + filter.getSizeY() / 2; i++) {
                        for (int j = x - filter.getSizeX() / 2; j <= x + filter.getSizeX() / 2; j++) {
                            if (i >= 0 && i < BMP.length && j >= 0 && j < BMP[y].length) {
                                sum += (BMP[i][j].getChannel(c) & 0xff) * filter.getCoefficient(i - (y - filter.getSizeY() / 2), j - (x - filter.getSizeX() / 2));
                            }
                        }
                    }

                    result.BMP[y][x].setChannel(c, Pixel.clump(sum));
                }
            }
        }

        return result;
    }

    public BMP applyOperatorComposition(Filter filter1, Filter filter2, BiFunction<Pixel, Pixel, Pixel> composition) {
        BMP bitMap1 = applyFilter(filter1);
        BMP bitMap2 = applyFilter(filter2);

        for (int y = 0; y < bitMap2.BMP.length; y++) {
            for (int x = 0; x < bitMap2.BMP[y].length; x++) {
                bitMap2.BMP[y][x] = composition.apply(bitMap1.BMP[y][x], bitMap2.BMP[y][x]);
            }
        }

        return bitMap2;
    }

    public BMP averagePixelRegion(int regionHeight, int regionWidth) {
        if (!(0 < regionHeight && regionHeight <= BMP.length)) {
            throw new InvalidParameterException("Incorrect region height: " +
                    (regionHeight > 0 ? "too big for this image" : "negative values are not allowed"));
        }

        if (!(0 < regionWidth && regionWidth <= BMP[0].length)) {
            throw new InvalidParameterException("Incorrect region width: " +
                    (regionWidth > 0 ? "too big for this image" : "negative values are not allowed"));
        }

        BMP result = new BMP(this);

        for (int y = 0; y < BMP.length; y++) {
            for (int x = 0; x < BMP[y].length; x++) {
                int bottom = Math.max(y - regionHeight / 2, 0);
                int top = Math.min(y + regionHeight / 2, BMP.length - 1);
                int left = Math.max(x - regionWidth / 2, 0);
                int right = Math.min(x + regionWidth / 2, BMP[y].length - 1);

                int currRegionHeight = top - bottom + 1;
                int currRegionWidth = right - left + 1;

                Pixel[] temp = new Pixel[currRegionHeight * currRegionWidth];
                for (int i = 0; i < currRegionHeight; i++) {
                    System.arraycopy(BMP[bottom + i], left, temp, i * currRegionWidth, currRegionWidth);
                }

                for (int c = 0; c < BMP[y][x].getNumberOfChannels(); c++) {
                    int channelNumber = c;
                    Arrays.sort(temp, Comparator.comparingInt(a -> a.getChannel(channelNumber) & 0xff));

                    result.BMP[y][x].setChannel(c, temp[temp.length / 2].getChannel(c));
                }
            }
        }

        return result;
    }

    public BMP averageChannels(int n) {
        BMP result = new BMP(this);

        for (int y = 0; y < BMP.length; y++) {
            for (int x = 0; x < BMP[y].length; x++) {
                int sum = 0;

                for (int c = 0; c < n; c++) {
                    sum += BMP[y][x].getChannel(c) & 0xff;
                }

                for (int c = 0; c < n; c++) {
                    result.BMP[y][x].setChannel(c, (byte) (sum / n));
                }
            }
        }

        return result;
    }

}