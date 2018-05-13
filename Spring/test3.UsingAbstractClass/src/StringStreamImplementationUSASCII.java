public class StringStreamImplementationUSASCII extends StringStream {
    public byte[] write(String s)
    {
        byte[] output;
        try {
            output = s.getBytes("US-ASCII");
            return output;
        } catch (java.io.UnsupportedEncodingException e) {
            System.out.println("Wrong bytes for US-ASCII");
            return null;
        }
    }
    public String read(byte[] input) {
        try {
            return new String(input, "US-ASCII");
        } catch (java.io.UnsupportedEncodingException e) {
            System.out.println("Wrong bytes for US-ASCII");
            return null;
        }
    }
}