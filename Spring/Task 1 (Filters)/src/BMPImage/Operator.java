package BMPImage;

import java.security.InvalidParameterException;

public class Operator {

    private final double[][] coefficients;
    private final int sizeX;
    private final int sizeY;

    public Operator(double[][] coefficients) {
        int sizeX = coefficients[0].length;
        for (double[] line : coefficients) {
            if (line.length != sizeX) {
                throw new InvalidParameterException("Coefficients array must be rectangle");
            }
        }

        this.coefficients = coefficients;
        this.sizeY = coefficients.length;
        this.sizeX = sizeX;
    }

    public double getCoefficient(int i, int j) {
        return coefficients[i][j];
    }

    public int getSizeY() {
        return sizeY;
    }

    public int getSizeX() {
        return sizeX;
    }
}
