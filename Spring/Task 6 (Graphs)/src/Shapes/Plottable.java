package Shapes;

import SwingApplication.MyCanvas;

/**
 * Main interface for plots paintings.
 * All shapes must implement this method to be able to be painted on the {@linkplain MyCanvas}.
 *
 * The only method {@linkplain #getPointsByX(double)} must return the points of the shape with
 * x-coordinate equal to the given one. Or in other words, it must return the result of the intersection
 * of a shape and a line x = givenX.
 */
public interface Plottable {
    Point[] getPointsByX(double x);
}
