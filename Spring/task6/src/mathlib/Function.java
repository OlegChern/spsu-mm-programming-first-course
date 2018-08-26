package mathlib;

public interface Function {
    double getValue(double X, boolean positivness, double step);
    double getDeadPoint();
    double getDeadSphereRadius();
    double getEnrichStepCoeff();
}
