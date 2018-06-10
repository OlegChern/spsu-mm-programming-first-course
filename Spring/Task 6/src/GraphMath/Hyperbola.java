package GraphMath;

public class Hyperbola extends Curve {

    private double a;
    private double b;

    public Hyperbola(double a, double b) {
        this.a = a;
        this.b = b;
    }

    private boolean checkDomain(double x) {
        return (x*x - a*a) > 0 || equals(Math.abs(x), a);
    }

    @Override
    public Point[] getPoint(double x) {
        if (checkDomain(x)) {
            double temp = x*x - a*a;
            double y = equals(temp, 0) ? 0 : (b / a) * Math.sqrt(temp);
            return new Point[]{new Point(x, y), new Point(x, -y)};
        }
        return new Point[0];
    }

    public String toString() {
        return getClass().getName() + " (a = " + a + ", b = " + b + ")";
    }
}
