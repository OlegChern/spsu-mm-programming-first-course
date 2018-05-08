package Shapes;


public class Parabola implements Plottable {
    private double p;
    
    public Parabola(double p) {
        this.p = p;
    }
    
    @Override
    public Point[] getPointsByX(double x) {
        if (satisfiesDomain(x)) {
            double t = 2 * p * x;
            double y = Computations.equal(t, 0) ? 0 : Math.sqrt(t);
            return new Point[]{new Point(x, y), new Point(x, -y)};
        }
    
        return new Point[0];
    }
    
    public boolean satisfiesDomain(double x) {
        return x * p > 0 || Computations.equal(x * p, 0);
    }
    
    public double getP() {
        return p;
    }
    
    public void setP(double p) {
        this.p = p;
    }
    
    @Override
    public String toString() {
        String pRepr = (p % 1 == 0) ? Integer.toString(new Double(2 * p).intValue()) : Double.toString(2 * p);
        return "Parabola: y² = " + pRepr + " * x";
    }
}
