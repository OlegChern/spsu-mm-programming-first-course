package mathlib;

public class FuncEllipse implements Function {

    public static final String FuncEllipseName = "x^2 +y^2/2 = 1";
    private static final double EnrichStepCoeff = 0.1;
    private static final double DeadSphereRadius = 0.4;

    @Override
    public double getDeadPoint() {
        return 0;
    }

    @Override
    public double getDeadSphereRadius() {
        return DeadSphereRadius;
    }

    @Override
    public double getEnrichStepCoeff() {
        return EnrichStepCoeff;
    }

    @Override
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