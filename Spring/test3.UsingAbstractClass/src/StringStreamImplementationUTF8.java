public class StringStreamImplementationUTF8 extends StringStream{
    public byte[] write(String s)
    {
        byte[] output;
        try {
            output = s.getBytes("UTF-8");
            return output;
        } catch (java.io.UnsupportedEncodingException e) {
            System.out.println("Wrong bytes for UTF-8");
            return null;
        }
    }
    public String read(byte[] input) {
        try {
            return new String(input, "UTF-8");
        } catch (java.io.UnsupportedEncodingException e) {
            System.out.println("Wrong bytes for UTF-8");
            return null;
        }
    }
}