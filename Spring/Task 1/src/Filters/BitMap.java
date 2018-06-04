package Filters;

public class BitMap {

    private Pixel[][] pixels;
    private Integer channelNumber;

    BitMap(Integer channels, Integer height, Integer width) {
        this.pixels = new Pixel[height + 4][width + 4];
        this.channelNumber = channels;

        for (int k = 0; k < 2; k++)
            for (int i = 0; i < height + 4; i++) {
                pixels[i][k] = new Pixel(channels);
                pixels[i][k].setPixel((byte) 255, (byte) 255, (byte) 255);

                pixels[i][width + 2 + k] = new Pixel(channels);
                pixels[i][width + 2 + k].setPixel((byte) 255, (byte) 255, (byte) 255);
            }

        for (int k = 0; k < 2; k++)
            for (int j = 0; j < width + 4; j++) {
                pixels[k][j] = new Pixel(channels);
                pixels[k][j].setPixel((byte) 255, (byte) 255, (byte) 255);

                pixels[height + 2 + k][j] = new Pixel(channels);
                pixels[height + 2 + k][j].setPixel((byte) 255, (byte) 255, (byte) 255);
            }

        for (int i = 2; i < height + 2; i++)
            for (int j = 2; j < width + 2; j++) {
                pixels[i][j] = new Pixel(channels);
            }

    }

    public Pixel getPixel(Integer posy, Integer posx) {
        return pixels[posy][posx];
    }


    public Pixel[][] getRegion(Integer posy, Integer posx, Integer size) {
        Pixel[][] tempRegion = new Pixel[size][size];

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++) {
                tempRegion[i][j] = pixels[i + posy - size / 2][j + posx - size / 2];
            }

        return tempRegion;
    }

    public Pixel getMedianPixel(Integer posx, Integer posy) {
        Pixel[][] region = getRegion(posx, posy, 3);

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                region[i][j] = region[i][j].copyPixel();
            }

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {

                if ((region[j / 3][j % 3].getBlue()) > (region[i / 3][i % 3].getBlue()))
                    Pixel.swapBlue(region[j / 3][j % 3], region[i / 3][i % 3]);

                if ((region[j / 3][j % 3].getGreen()) > (region[i / 3][i % 3].getGreen()))
                    Pixel.swapGreen(region[j / 3][j % 3], region[i / 3][i % 3]);

                if ((region[j / 3][j % 3].getRed()) > (region[i / 3][i % 3].getRed()))
                    Pixel.swapRed(region[j / 3][j % 3], region[i / 3][i % 3]);
            }
        }
        return region[1][1];
    }


}
