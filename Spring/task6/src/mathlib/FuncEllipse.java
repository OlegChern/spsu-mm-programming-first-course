package mathlib;

public class FuncEllipse implements function {

    public static final String FuncEllipseName = "x^2 +y^2/2 = 1";

    public double getValue(double X, boolean positivness, double step) {
        if (positivness) {
            if (!Double.isNaN(Math.sqrt(2 - 2 * X * X))) {
                return (Math.sqrt(2 - 2 * X * X));
            } else if (step + (2 - 2 * X * X) > 0) {
                return 0;
            } else {
                return (Math.sqrt(2 - 2 * X * X));
            }
        } else {
            if (!Double.isNaN(Math.sqrt(2 - 2 * X * X))) {
                return -(Math.sqrt(2 - 2 * X * X));
            } else if (step + (2 - 2 * X * X) > 0) {
                return 0;
            } else {
                return -(Math.sqrt(2 - 2 * X * X));
            }
        }
    }
}