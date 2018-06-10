package GraphMath;

public class Ellipse extends Curve {

    double a;
    private double b;

    public Ellipse(double a, double b) {
        this.a = a;
        this.b = b;
    }

    private boolean checkDomain(double x) {
        return (x < a && x > -a) || equals(Math.abs(x), a);
    }

    @Override
    public Point[] getPoint(double x) {
        if (checkDomain(x)) {
            double temp = a * a - x * x;
            double y = equals(temp, 0) ? 0 : (a / b) * Math.sqrt(temp);
            return new Point[]{new Point(x, y), new Point(x, -y)};
        }
        return new Point[0];
    }

    public String toString() {
        return getClass().getName() + " (a = " + a + ", b = " + b + ")";
    }
}
