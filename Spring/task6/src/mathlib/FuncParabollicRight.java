package mathlib;


public class FuncParabollicRight implements Function{

    public static final String FuncParabollicRightName = "x^2-y^3=0";

    @Override
    public double getDeadSphereRadius() {
        return 0;
    }

    @Override
    public double getDeadPoint() {
        return -1;
    }

    @Override
    public double getEnrichStepCoeff() {
        return 1;
    }

    @Override
    public double getValue(double X, boolean positivness, double step) {
        if (positivness) {
            return (Math.sqrt(X * X * X));
        }
        else {
            return -(Math.sqrt(X * X * X));
        }
    }
}
