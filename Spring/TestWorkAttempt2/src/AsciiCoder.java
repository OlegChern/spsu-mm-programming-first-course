import java.nio.charset.StandardCharsets;
import java.util.stream.Collectors;

public class AsciiCoder implements Coder {

    @Override
    public String decode(String src) {
        return new String(src
                .chars()
                .mapToObj(c -> Character.toString((char) c))
                .collect(Collectors.joining())
                .toCharArray()
        );
    }

    @Override
    public String encode(String src) {
        byte[] toBeEncoded = src.getBytes(StandardCharsets.US_ASCII);
        return new String(toBeEncoded);
    }
}
