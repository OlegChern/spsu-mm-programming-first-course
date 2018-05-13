import java.util.Scanner;

public class Main {
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);

        System.out.println("Enter what you want to encode");
        String s = in.nextLine();
        StringStreamImplementationUTF8 utf = new StringStreamImplementationUTF8();
        StringStreamImplementationUSASCII ascii = new StringStreamImplementationUSASCII();
        System.out.println(utf.read(utf.write(s)));
        System.out.println(ascii.read(ascii.write(s)));
    }
}

