package Shapes;


public class EllipticCurve implements Plottable {
    private double a;
    private double b;
    
    public EllipticCurve(double a, double b) {
        this.a = a;
        this.b = b;
    }
    
    
    
    @Override
    public Point[] getPointsByX(double x) {
        if (satisfiesDomain(x)) {
            double t = x * x * x + a * x + b;
            double y = Computations.equal(t, 0) ? 0 : Math.sqrt(t);
            return new Point[]{new Point(x, y), new Point(x, -y)};
        }
        
        return new Point[0];
    }
    
    public boolean satisfiesDomain(double x) {
        return x * x * x + a * x + b >= 0 || Computations.equal(x * x * x + a * x + b, 0);
    }
    
    public double getA() {
        return a;
    }
    
    public void setA(double a) {
        this.a = a;
    }
    
    public double getB() {
        return b;
    }
    
    public void setB(double b) {
        this.b = b;
    }
    
    @Override
    public String toString() {
        String aRepr = (a % 1 == 0) ? Integer.toString(new Double(Math.abs(a)).intValue()) : Double.toString(Math.abs(a));
        String bRepr = (b % 1 == 0) ? Integer.toString(new Double(Math.abs(b)).intValue()) : Double.toString(Math.abs(b));
        return "EllipticCurve: y² = x³" +
                (a == 0 ? "" : ((a > 0 ? " + " : " - ") + aRepr + " * x")) +
                (b == 0 ? "" : ((b > 0 ? " + " : " - ") + bRepr));
    }
}
