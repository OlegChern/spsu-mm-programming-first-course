public class Main {

    public static void main(String[] args) throws Exception {
        String test = "Test String 1234567890-";

        System.out.println(Program.encodeBase64String(test));
        System.out.println(Program.decodeAsciiString(test));
    }
}
