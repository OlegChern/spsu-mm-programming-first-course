package BMPImage;

public class Pixel {

    private byte[] channels;

    public Pixel(int numberOfChannels) {
        this.channels = new byte[numberOfChannels];
    }

    public Pixel(byte[] channels) {
        this.channels = channels;
    }

    public Pixel(Pixel another) {
        channels = new byte[another.channels.length];
        System.arraycopy(another.channels, 0, channels, 0, another.channels.length);
    }

    public int getNumberOfChannels() {
        return channels.length;
    }

    public byte getChannel(int i) {
        return channels[i];
    }

    public void setChannel(int i, byte v) {
        channels[i] = v;
    }

    public static byte clump(double v) {
        if (v > 255)
            return (byte) 255;

        if (v < 0)
            return (byte) 0;

        return (byte) v;
    }
}
