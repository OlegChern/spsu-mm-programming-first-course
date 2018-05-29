import java.io.PrintWriter;

public class Commentator {
    private PrintWriter pw;
    
    public Commentator(PrintWriter pw) {
        this.pw = pw;
    }
    
    public void comment(String player, String action) {
        pw.println(player + " " + action);
    }
    
    public void comment(String message) {
        pw.println(message);
    }
}
