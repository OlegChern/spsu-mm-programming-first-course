public interface Coder {

    String decode(String src) throws Exception;
    String encode(String src) throws Exception;
}
