package GraphMath;

public class Parabola extends Curve {

    private double p;

    public Parabola(double p) {
        this.p = p;
    }

    @Override
    public Point[] getPoint(double x) {
        if (checkDomain(x)) {
            double temp = Math.sqrt(2 * p * x);
            return new Point[]{new Point(x, temp), new Point(x, -temp)};
        }
        return new Point[0];
    }

    private boolean checkDomain(double x) {
        return x * p > 0 || equals(x * p, 0);
    }

    public String toString() {
        return getClass().getName() + " (p = " + p + ")";
    }
}
