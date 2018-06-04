package Filters;

import java.nio.ByteBuffer;

public class Pixel {

    private byte[] colours;

    Pixel(Integer channelNumber) {
        this.colours = new byte[channelNumber];
    }

    public byte getBlue() {
        return colours[0];
    }

    public byte getGreen() {
        return colours[1];
    }

    public byte getRed() {
        return colours[2];
    }

    private void setBlue(byte blue) {
        colours[0] = blue;
    }

    private void setGreen(byte green) {
        colours[1] = green;
    }

    private void setRed(byte red) {
        colours[2] = red;
    }

    public void setPixel(byte blue, byte green, byte red) {
        this.colours[0] = blue;
        this.colours[1] = green;
        this.colours[2] = red;
    }

    public void setPixel(Pixel anotherOne) {
        this.setPixel(anotherOne.getBlue(), anotherOne.getGreen(), anotherOne.getRed());
    }

    public Pixel copyPixel() {
        Pixel result = new Pixel(colours.length);
        result.setPixel(this.getBlue(), this.getGreen(), this.getRed());
        return result;
    }

    public static void swapBlue(Pixel p1, Pixel p2) {
        byte temp = p1.getBlue();
        p1.setBlue(p2.getBlue());
        p2.setBlue(temp);
    }

    public static void swapGreen(Pixel p1, Pixel p2) {
        byte temp = p1.getGreen();
        p1.setGreen(p2.getGreen());
        p2.setGreen(temp);
    }

    public static void swapRed(Pixel p1, Pixel p2) {
        byte temp = p1.getRed();
        p1.setRed(p2.getRed());
        p2.setRed(temp);
    }

    public void putPixel(ByteBuffer buffer, Integer channels) {
        buffer.put(getBlue());
        buffer.put(getGreen());
        buffer.put(getRed());
        if (channels == 4) buffer.put((byte) 0);
    }
}
