import javax.swing.SwingUtilities;
import javafx.application.Application;

public class Main {
    
    public static void main(String[] args) {
        /* Swing Application */
//        SwingUtilities.invokeLater(SwingApplication.Plots::new);
    
        /* JavaFX Application */
        Application.launch(JavaFXApplication.Plots.class, args);
    }
}
