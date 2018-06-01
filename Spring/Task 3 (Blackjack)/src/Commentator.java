import java.io.PrintWriter;

public class Commentator {
    private PrintWriter pw;
    
    public Commentator(PrintWriter pw) {
        this.pw = pw;
    }
    
    public void comment(String player, String action) {
        if (pw != null) {
            pw.println(player + " " + action);
        }
    }
    
    public void comment(String message) {
        if (pw != null) {
            pw.println(message);
        }
    }
}
