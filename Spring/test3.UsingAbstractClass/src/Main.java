import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);

        System.out.println("Enter what you want to encode");
        String s = in.nextLine();
        System.out.println("Write 1 for UTF 8 or 2 for ASCII (USA)");
        int k = in.nextInt();
        if (k == 1) {
            StringStream utf = new StringStreamImplementationUTF8();
            System.out.println(utf.read(utf.write(s)));
        } else {
            StringStream ascii = new StringStreamImplementationUSASCII();
            System.out.println(ascii.read(ascii.write(s)));
        }
    }
}
