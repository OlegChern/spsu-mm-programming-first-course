import java.io.PrintWriter;

public class Commentator {
    private PrintWriter pw;
    private boolean isMute;
    
    public Commentator(PrintWriter pw) {
        this.pw = pw;
        this.isMute = false;
    }
    
    public void comment(String player, String action) {
        if (pw != null && !isMute) {
            pw.println(player + " " + action);
        }
    }
    
    public void comment(String message) {
        if (pw != null && !isMute) {
            pw.println(message);
        }
    }
    
    public boolean isMute() {
        return isMute;
    }
    
    public void mute(boolean mute) {
        isMute = mute;
    }
}
