package Shapes;


import Canvas.Plottable;
import Utils.Computations;

import java.awt.geom.Point2D;


public class Hyperbola implements Plottable {
    private double a;
    private double b;
    
    public Hyperbola(double a, double b) {
        if (!checkParameters(a, b)) {
            throw new IllegalArgumentException("a, b must be positive, given a: " + a + " b: " + b);
        }
        this.a = a;
        this.b = b;
    }
    
    @Override
    public Point2D.Double[] getPointsByX(double x) {
        if (satisfiesDomain(x)) {
            double t = x * x - a * a;
            double y = Computations.equal(t, 0) ? 0 : b / a * Math.sqrt(t);
            return new Point2D.Double[]{new Point2D.Double(x, y), new Point2D.Double(x, -y)};
        }
    
        return new Point2D.Double[0];
    }
    
    public boolean satisfiesDomain(double x) {
        return x < -a || a < x || Computations.equal(x, -a) || Computations.equal(x, a);
    }
    
    private boolean checkParameters(double a, double b) {
        return a > 0 && b > 0;
    }
    
    public double getA() {
        return a;
    }
    
    public void setA(double a) {
        if (!checkParameters(a, b)) {
            throw new IllegalArgumentException("a must be positive, given a: " + a);
        }
        this.a = a;
    }
    
    public double getB() {
        return b;
    }
    
    public void setB(double b) {
        if (!checkParameters(a, b)) {
            throw new IllegalArgumentException("b must be positive, given b: " + b);
        }
        this.b = b;
    }
    
    @Override
    public String toString() {
        String aRepr = (a % 1 == 0) ? Integer.toString(new Double(a).intValue()) : Double.toString(a);
        String bRepr = (b % 1 == 0) ? Integer.toString(new Double(b).intValue()) : Double.toString(b);
        return "Hyperbola: x²/" + aRepr + "² - y²/" + bRepr + "² = 1";
    }
}
