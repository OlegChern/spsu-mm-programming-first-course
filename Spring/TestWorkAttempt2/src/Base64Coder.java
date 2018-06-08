import com.sun.org.apache.xml.internal.security.exceptions.Base64DecodingException;
import com.sun.org.apache.xml.internal.security.utils.Base64;

public class Base64Coder implements Coder {

    @Override
    public String decode(String src) throws Base64DecodingException {
        return new String(Base64.decode(src));
    }

    @Override
    public String encode(String src) {
        byte[] toBeEncoded = src.getBytes();
        return Base64.encode(toBeEncoded);
    }
}
