public interface StringStream {
    byte[] write(String s);
    String read(byte[] input);
}