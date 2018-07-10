package mathlib;


public class FuncParabollicRight implements Function{

    public static final String FuncParabollicRightName = "x^2-y^3=0";

    public double getValue(double X, boolean positivness, double step) {
        if (positivness) {
            return (Math.sqrt(X * X * X));
        }
        else {
            return -(Math.sqrt(X * X * X));
        }
    }
}
