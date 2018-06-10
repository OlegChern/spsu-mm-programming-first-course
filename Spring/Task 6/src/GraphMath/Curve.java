package GraphMath;

public abstract class Curve {

    private static double accuracy;

    public abstract Point[] getPoint(double x);

    boolean equals(double num1, double num2) {
        return Math.abs(num2 - num1) < accuracy;
    }

    public static void setAccuracy(double newAccuracy) {
        accuracy = newAccuracy;
    }
}
