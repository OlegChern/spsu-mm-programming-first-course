import java.io.File;

public class Program {

    private Reader reader;
    private Writer writer;

    private Coder coder;

    private String originalData;

    private String decodedData;
    private String encodedData;

    public Program(String inputPath, String outputPath, CoderTypes type) throws Exception{

        reader = new Reader(new File(inputPath));
        writer = new Writer(new File(outputPath));
        originalData = reader.readFile();

        if (type == CoderTypes.base64) {
            coder = new Base64Coder();
            decodedData = coder.decode(originalData);
            encodedData = coder.encode(decodedData);
        }
        else {
            coder = new AsciiCoder();
            decodedData = coder.decode(originalData);
            encodedData = coder.encode(decodedData);
        }
    }

    public void printDecodedText() {
        System.out.println(decodedData);
    }

    public void printEncodedText() {
        System.out.println(encodedData);
    }

    public void printOriginalData() {
        System.out.println(originalData);
    }

    public static String decodeAsciiString(String str) {
        return new AsciiCoder().decode(str);
    }

    public static String encodeAsciiString(String str) {
        return new AsciiCoder().encode(str);
    }

    public static String decodeBase64String(String str) throws Exception {
        return new Base64Coder().decode(str);
    }

    public static String encodeBase64String(String str) {
        return new Base64Coder().encode(str);
    }


}
