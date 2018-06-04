package Filters;

public class FilterApplier {

    private FilterType type;
    private String additionalArg;
    private BmpImage image;

    private static final int[][] gauss3x3 = {{1, 2, 1},
            {2, 4, 2},
            {1, 2, 1}};

    private static final int[][] gauss5x5 = {{1, 4, 6, 4, 1},
            {4, 16, 24, 16, 4},
            {6, 24, 36, 24, 6},
            {4, 16, 24, 16, 4},
            {1, 4, 6, 4, 1}};

    private static final int[][] sobelX = {{1, 2, 1},
            {0, 0, 0},
            {-1, -2, -1}};

    private static final int[][] sobelY = {{-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}};

    FilterApplier(BmpImage image, FilterType filter, String arg) {
        this.image = image;
        this.type = filter;
        this.additionalArg = arg;
    }

    public void ApplyFilter() {
        BitMap map = image.getMap();
        BitMap newMap = image.getNewMap();
        int height = image.getHeight();
        int width = image.getWidth();

        switch (type) {

            case Grey: {
                for (int i = 2; i < height + 2; i++)
                    for (int j = 2; j < width + 2; j++) {
                        applyGrey(map, newMap, i, j);
                    }
                break;
            }

            case Median: {
                for (int i = 2; i < height + 2; i++)
                    for (int j = 2; j < width + 2; j++) {
                        applyMedian(map, newMap, i, j);
                    }
                break;
            }
            case Gauss: {
                for (int i = 2; i < height + 2; i++)
                    for (int j = 2; j < width + 2; j++) {
                        applyGauss(map, newMap, i, j);
                    }
                break;
            }
            case Sobel: {
                for (int i = 2; i < height + 2; i++)
                    for (int j = 2; j < width + 2; j++) {
                        applySobel(map, newMap, i, j);
                    }
                break;
            }

        }
    }

    private void applyGrey(BitMap map, BitMap newMap, Integer posy, Integer posx) {
        Pixel temp = map.getPixel(posy, posx);

        int blue = temp.getBlue();
        if (blue < 0) blue &= 0xff;

        int green = temp.getGreen();
        if (green < 0) green &= 0xff;

        int red = temp.getRed();
        if (red < 0) red &= 0xff;


        byte average = (byte) ((blue + red + green) / 3);
        newMap.getPixel(posy, posx).setPixel(average, average, average);
    }

    private void applyMedian(BitMap map, BitMap newMap, Integer posy, Integer posx) {
        Pixel median = map.getMedianPixel(posy, posx);
        newMap.getPixel(posy, posx).setPixel(median.getBlue(), median.getGreen(), median.getRed());
    }

    private void applyGauss(BitMap map, BitMap newMap, Integer posy, Integer posx) {

        int resultSumBlue = 0;
        int resultSumGreen = 0;
        int resultSumRed = 0;

        int option = additionalArg.equals("3") ? 3 : 5;
        int div = option == 3 ? 16 : 256;

        Pixel[][] region = map.getRegion(posy, posx, option);
        for (int i = 0; i < option; i++)
            for (int j = 0; j < option; j++) {

                int blue = region[i][j].getBlue();
                if (blue < 0) blue &= 0xff;

                int green = region[i][j].getGreen();
                if (green < 0) green &= 0xff;

                int red = region[i][j].getRed();
                if (red < 0) red &= 0xff;

                resultSumBlue += blue * (option == 3 ? gauss3x3[j][i] : gauss5x5[j][i]);
                resultSumGreen += green * (option == 3 ? gauss3x3[j][i] : gauss5x5[j][i]);
                resultSumRed += red * (option == 3 ? gauss3x3[j][i] : gauss5x5[j][i]);
            }


        resultSumBlue /= div;
        resultSumGreen /= div;
        resultSumRed /= div;

        newMap.getPixel(posy, posx).setPixel((byte) resultSumBlue, (byte) resultSumGreen, (byte) resultSumRed);
    }

    private void applySobel(BitMap map, BitMap newMap, Integer posy, Integer posx) {

        int resultSumBlueX = 0;
        int resultSumGreenX = 0;
        int resultSumRedX = 0;

        int resultSumBlueY = 0;
        int resultSumGreenY = 0;
        int resultSumRedY = 0;

        boolean isX = additionalArg.contains("x");
        boolean isY = additionalArg.contains("y");

        Pixel[][] region = map.getRegion(posy, posx, 3);
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {

                int blue = region[i][j].getBlue();
                if (blue < 0) blue &= 0xff;

                int green = region[i][j].getGreen();
                if (green < 0) green &= 0xff;

                int red = region[i][j].getRed();
                if (red < 0) red &= 0xff;

                if (isX) {
                    resultSumBlueX += blue * sobelX[j][i];
                    resultSumGreenX += green * sobelX[j][i];
                    resultSumRedX += red * sobelX[j][i];
                }
                if (isY) {
                    resultSumBlueY += blue * sobelY[j][i];
                    resultSumGreenY += green * sobelY[j][i];
                    resultSumRedY += red * sobelY[j][i];
                }

            }

        int resultBlue;
        int resultRed;
        int resultGreen;

        if (isX && isY) {
            resultBlue = (int) Math.sqrt(resultSumBlueX * resultSumBlueX + resultSumBlueY * resultSumBlueY);
            resultGreen = (int) Math.sqrt(resultSumGreenX * resultSumGreenX + resultSumGreenY * resultSumGreenY);
            resultRed = (int) Math.sqrt(resultSumRedX * resultSumRedX + resultSumRedY * resultSumRedY);
        } else if (isX) {
            resultBlue = resultSumBlueX;
            resultGreen = resultSumGreenX;
            resultRed = resultSumRedX;
        } else {
            resultBlue = resultSumBlueY;
            resultGreen = resultSumGreenY;
            resultRed = resultSumRedY;
        }

        if (resultBlue > 255) resultBlue = 255;
        if (resultGreen > 255) resultGreen = 255;
        if (resultRed > 255) resultRed = 255;

        if (resultBlue < 0) resultBlue = 0;
        if (resultGreen < 0) resultGreen = 0;
        if (resultRed < 0) resultRed = 0;

        newMap.getPixel(posy, posx).setPixel((byte) resultBlue, (byte) resultGreen, (byte) resultRed);
    }


}
