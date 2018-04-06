package BMPImage;

import java.nio.ByteOrder;

public interface ByteArrayConvertable {
    byte[] toByteArray(ByteOrder byteOrder);
    void fromByteArray(byte[] bytes, ByteOrder byteOrder);
}
