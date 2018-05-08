package Shapes;

public class Computations {
    
    private Computations() {
    }
    
    public static double accuracy = 0.01;
    
    public static boolean equal(double a, double b) {
        return Math.abs(a - b) < accuracy;
    }
    
    public static double getAccuracy() {
        return accuracy;
    }
    
    public static void setAccuracy(double accuracy) {
        Computations.accuracy = accuracy;
    }
}
