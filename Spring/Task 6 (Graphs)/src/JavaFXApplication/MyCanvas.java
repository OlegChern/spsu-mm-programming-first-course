package JavaFXApplication;

import Shapes.Plottable;


import javafx.geometry.Point2D;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;

import java.util.Arrays;


/**
 * Class for plots paintings based on JavaFX API.
 * <p>
 * To paint a plot {@linkplain #setPlot(Plottable)} must be called with desired plot
 * as argument and then {@linkplain #repaintAll()} must be invoked to display results.
 * <p>
 * Internally, the plot is painted using {@linkplain #paintPlot(Plottable)} via
 * {@linkplain Plottable} interface.
 * <p>
 * <p>
 * The canvas supports zooming (in and out):
 *
 * @see #zoomIn()
 * @see #zoomOut()
 * and mouse dragging:
 * @see #MyCanvas(double, double)
 */
public class MyCanvas extends Canvas {
    
    private Point2D centerCoefficientsRelativeToCanvasSize = new Point2D(0.5, 0.5);
    private Point2D center;
    
    private Plottable plot;
    private Color plotColor = Color.BLUE;
    
    /**
     * Variables and constants which are responsible for the scale.
     */
    private int pixelsPerOneDivision = 40;
    private static final int MIN_PIXELS_PER_ONE_DIVISION = 20;
    private static final int MAX_PIXELS_PER_ONE_DIVISION = 100;
    private static final int SCALE_STEP = 5;
    
    /**
     * Variables and constants which are responsible for the mouse dragging.
     * To increase performance and exclude hanging up, changes are
     * applied only if a dragging distance was more than
     * {@linkplain #MINIMUM_MOUSE_MOTION_DISTANCE}
     */
    private Point2D lastMousePosition;
    private static final int MINIMUM_MOUSE_MOTION_DISTANCE = 10;
    private static final int MINIMUM_MOUSE_MOTION_DISTANCE2 =
            MINIMUM_MOUSE_MOTION_DISTANCE * MINIMUM_MOUSE_MOTION_DISTANCE;
    
    /**
     * Edges of plots are zones of the potential loss of the accuracy.
     * It explores more carefully in a zoom: that means that
     * a pixel divides in {@linkplain #ZOOM_REGION} parts and
     * if any of it satisfies plot than whole pixel is considered
     * as satisfied plot.
     *
     * @see #checkInZoom(Plottable, int)
     */
    private static final int ZOOM_REGION = 100;
    
    /**
     * Generally, the canvas can not determine whether nearest points must be
     * connected by line or not so it do it only if distance between points
     * is not bigger than {@linkplain #MAX_DISTANCE_BETWEEN_NEIGHBORS}.
     */
    private static final int MAX_DISTANCE_BETWEEN_NEIGHBORS = 40;
    private static final int MAX_DISTANCE2_BETWEEN_NEIGHBORS =
            MAX_DISTANCE_BETWEEN_NEIGHBORS * MAX_DISTANCE_BETWEEN_NEIGHBORS;
    
    public MyCanvas(double width, double height) {
        super(width, height);
        
        updateCenter();
        
        // updates center on window resizing
        widthProperty().addListener((observable, oldValue, newValue) -> {
            updateCenter();
            repaintAll();
        });
        heightProperty().addListener((observable, oldValue, newValue) -> {
            updateCenter();
            repaintAll();
        });
        
        // tracks mouse position for the plot dragging
        setOnMousePressed(e -> lastMousePosition = new Point2D(e.getSceneX(), e.getSceneY()));
        setOnMouseDragged(e -> {
            Point2D clickPoint = new Point2D(e.getSceneX(), e.getSceneY());
            
            if (dist2Between(clickPoint, lastMousePosition) >= MINIMUM_MOUSE_MOTION_DISTANCE2) {
                double diffX = clickPoint.getX() - lastMousePosition.getX();
                double diffY = clickPoint.getY() - lastMousePosition.getY();
                
                centerCoefficientsRelativeToCanvasSize =
                        centerCoefficientsRelativeToCanvasSize.add(new Point2D(diffX / getWidth(), diffY / getHeight()));
                
                updateCenter();
                lastMousePosition = clickPoint;
            }
            
            repaintAll();
        });
    }
    
    /**
     * Updates the coordinates of origin according to the current size.
     */
    private void updateCenter() {
        center = new Point2D(
                Math.round(centerCoefficientsRelativeToCanvasSize.getX() * getWidth()),
                Math.round(centerCoefficientsRelativeToCanvasSize.getY() * getHeight())
        );
    }
    
    /**
     * Returns a current plot.
     *
     * @return current plot
     */
    public Plottable getPlot() {
        return plot;
    }
    
    /**
     * Sets new plot to be painted.
     * To paint it immediately {@linkplain #repaintAll()} must be called after
     * this method invocation.
     *
     * @param plot new plot
     */
    public void setPlot(Plottable plot) {
        this.plot = plot;
    }
    
    /**
     * Returns selected {@linkplain #plotColor}.
     *
     * @return
     */
    public Color getPlotColor() {
        return plotColor;
    }
    
    /**
     * Sets new plot color.
     *
     * @param plotColor new plot color
     */
    public void setPlotColor(Color plotColor) {
        this.plotColor = plotColor;
    }
    
    /**
     * Zooms in field if {@linkplain #pixelsPerOneDivision} is not bigger than
     * {@linkplain #MAX_PIXELS_PER_ONE_DIVISION}.
     */
    public void zoomIn() {
        if (pixelsPerOneDivision + SCALE_STEP <= MAX_PIXELS_PER_ONE_DIVISION) {
            pixelsPerOneDivision += SCALE_STEP;
        }
        repaintAll();
    }
    
    /**
     * Zooms out field if {@linkplain #pixelsPerOneDivision} is not smaller than
     * {@linkplain #MIN_PIXELS_PER_ONE_DIVISION}.
     */
    public void zoomOut() {
        if (pixelsPerOneDivision - SCALE_STEP >= MIN_PIXELS_PER_ONE_DIVISION) {
            pixelsPerOneDivision -= SCALE_STEP;
        }
        repaintAll();
    }
    
    //region Painting methods
    
    public void clearCanvas() {
        getGraphicsContext2D().clearRect(0, 0, getWidth(), getHeight());
    }
    
    public void paintAll() {
        paintGrid();
        paintPlot(getPlot());
    }
    
    public void repaintAll() {
        clearCanvas();
        paintAll();
    }
    
    /**
     * Converts a pixel to the real point this pixel represents.
     *
     * @param p Pixel to convert
     * @return Real point this pixel represents
     */
    private Point2D convertPixelToRealPoint(Point2D p) {
        return new Point2D(
                (p.getX() - center.getX()) / pixelsPerOneDivision,
                (center.getY() - p.getY()) / pixelsPerOneDivision
        );
    }
    
    /**
     * Converts a real point to the pixel that represents its area.
     *
     * @param p Real point to convert
     * @return Pixel that represents given pixel area
     */
    private Point2D convertRealPointToPixel(Point2D p) {
        return new Point2D(
                center.getX() + Math.round(p.getX() * pixelsPerOneDivision),
                center.getY() - Math.round(p.getY() * pixelsPerOneDivision)
        );
    }
    
    /**
     * Checks given pixel carefully in a zoom. It is invoked usually near the edges of the plot
     * which are especially potential of the accuracy loss.
     * <p>
     * Normally, pixel x-coordinate converts to the real point it represents using
     * {@linkplain #convertPixelToRealPoint(Point2D)} and gets points of plot
     * on the line x = realPoint. But on the edges of the plot it might be not found
     * because of the not enough accuracy. So it is where {@linkplain #checkInZoom(Plottable, int)}
     * come to game.
     * <p>
     * Given pixel divides in {@linkplain #ZOOM_REGION} real points with small interval
     * between them and if any of it satisfies plot (some plot points on the
     * line x = particularRealPoint were found) then this result is considered as a
     * result of whole pixel.
     *
     * @param shape Plot which point must be checked
     * @param x     X coordinate of the pixel to be checked in a zoom on plot satisfaction
     * @return Points if they were found in some particular point of empty array otherwise
     */
    private Point2D[] checkInZoom(Plottable shape, int x) {
        for (int dx = -ZOOM_REGION / 2; dx < ZOOM_REGION / 2; dx++) {
            double realX = (x * ZOOM_REGION + dx - center.getX() * ZOOM_REGION) / (pixelsPerOneDivision * ZOOM_REGION);
            Point2D[] plotPoints = Arrays.stream(shape.getPointsByX(realX))
                    .map(p -> new Point2D(p.x, p.y))
                    .map(this::convertRealPointToPixel)
                    .distinct()
                    .toArray(Point2D[]::new);
            if (plotPoints.length > 0) {
                return plotPoints;
            }
        }
        
        return new Point2D[0];
    }
    
    /**
     * Returns a square of the distance between two points.
     *
     * @param a First point
     * @param b Second point
     * @return square of the distance between given points
     */
    private double dist2Between(Point2D a, Point2D b) {
        return (a.getX() - b.getX()) * (a.getX() - b.getX()) + (a.getY() - b.getY()) * (a.getY() - b.getY());
    }
    
    /**
     * Gets an array of the points and paints lines between any points in it if the
     * distance between them is not bigger than {@linkplain #MAX_DISTANCE_BETWEEN_NEIGHBORS}.
     *
     * @param points Array which points are to be connected by lines
     */
    private void paintLinesBetweenNeighbors(Point2D[] points) {
        GraphicsContext g = getGraphicsContext2D();
        
        for (int i = 0; i < points.length; i++) {
            for (int j = i + 1; j < points.length; j++) {
                if (dist2Between(points[i], points[j]) <= MAX_DISTANCE2_BETWEEN_NEIGHBORS) {
                    g.strokeLine(points[i].getX(), points[i].getY(), points[j].getX(), points[j].getY());
                }
            }
        }
    }
    
    /**
     * Main method of the plot painting.
     * <p>
     * It verifies each vertical line of the field on the intersection with the plot
     * via {@linkplain Plottable#getPointsByX(double)} and paints gotten points.
     * <p>
     * Points that are nearer than {@linkplain #MAX_DISTANCE_BETWEEN_NEIGHBORS} are
     * considered as neighbours of the plot and are connected by lines.
     * <p>
     * Edges of the plot are explored carefully using {@linkplain #checkInZoom(Plottable, int)}.
     *
     * @param shape Plot to be painted. If it {@code null} nothing is applied.
     */
    public void paintPlot(Plottable shape) {
        if (shape == null) {
            return;
        }
        
        GraphicsContext g = getGraphicsContext2D();
        
        g.setStroke(plotColor);
        g.setLineWidth(1);
        
        int width = (int) getWidth();
        Point2D[] previous = new Point2D[0];
        
        for (int x = 0; x < width; x++) {
            double realX = convertPixelToRealPoint(new Point2D(x, 0)).getX();
            Point2D[] plotPoints = Arrays.stream(shape.getPointsByX(realX))
                    .map(p -> new Point2D(p.x, p.y))
                    .map(this::convertRealPointToPixel)
                    .distinct() // removes pixels duplicates
                    .toArray(Point2D[]::new);
            
            if (plotPoints.length > 0 && previous.length == 0) {
                previous = checkInZoom(shape, x - 1);
                for (Point2D foundPoint : previous) {
                    g.strokeLine(foundPoint.getX(), foundPoint.getY(), foundPoint.getX(), foundPoint.getY());
                }
                paintLinesBetweenNeighbors(previous.length > 0 ? previous : plotPoints);
            }
            
            if (plotPoints.length == 0 && previous.length > 0) {
                plotPoints = checkInZoom(shape, x);
                paintLinesBetweenNeighbors(plotPoints.length > 0 ? plotPoints : previous);
            }
            
            // Lines will be drawn from the points in the first array to the points of the second array.
            // To draw more potential lines the first array is considered to be bigger than the second one.
            Point2D[] biggest = plotPoints.length > previous.length ? plotPoints : previous;
            Point2D[] other = plotPoints.length > previous.length ? previous : plotPoints;
            
            for (Point2D point : biggest) {
                if (other.length == 0) {
                    g.strokeLine(point.getX(), point.getY(), point.getX(), point.getY());
                } else {
                    Point2D closest = other[0];
                    for (int i = 1; i < other.length; i++) {
                        if (dist2Between(other[i], point) < dist2Between(closest, point)) {
                            closest = other[i];
                        }
                    }
                    
                    if (dist2Between(closest, point) < MAX_DISTANCE2_BETWEEN_NEIGHBORS) {
                        g.strokeLine(closest.getX(), closest.getY(), point.getX(), point.getY());
                    }
                }
            }
            
            previous = plotPoints;
        }
    }
    
    /**
     * Helper-method of {@linkplain #paintGrid()} implementation.
     * Returns digit length of the given number.
     *
     * @param n Number which length is to be calculated
     * @return Digit length of the given number
     */
    private static int digitsCount(int n) {
        return (int) Math.floor(Math.log10(Math.abs(n))) + 1;
    }
    
    /**
     * Paints a grid of the field with main axises and auxiliary lines with numbers.
     */
    private void paintGrid() {
        GraphicsContext g = getGraphicsContext2D();
        
        //region Paints auxiliary lines with numbers
        g.setLineWidth(1);
        int fontSize = Math.min(Math.max(pixelsPerOneDivision / 3, 10), 25);
        g.setFont(new Font("TimesRoman", fontSize));
        
        int width = (int) getWidth();
        int height = (int) getHeight();
        
        int leftVerticalLine = ((int) Math.round(center.getX())) % pixelsPerOneDivision;
        int leftVerticalLineNumber = (leftVerticalLine - ((int) Math.round(center.getX()))) / pixelsPerOneDivision;
        for (int verticalLine = leftVerticalLine, i = leftVerticalLineNumber;
             verticalLine < width;
             verticalLine += pixelsPerOneDivision, i++) {
            
            if (i != 0) {
                g.setStroke(Color.LIGHTGRAY);
                g.strokeLine(verticalLine, 0, verticalLine, height);
                g.setStroke(Color.BLACK);
                g.fillText(
                        Integer.toString(i),
                        verticalLine - fontSize / 2 - (i < 0 ? fontSize / 4 : 0),
                        center.getY() + fontSize
                );
            }
        }
        int topHorizontalLine = ((int) Math.round(center.getY())) % pixelsPerOneDivision;
        int topHorizontalLineNumber = (((int) Math.round(center.getY())) - topHorizontalLine) / pixelsPerOneDivision;
        for (int horizontalLine = topHorizontalLine, i = topHorizontalLineNumber;
             horizontalLine < height;
             horizontalLine += pixelsPerOneDivision, i--) {
            
            if (i != 0) {
                g.setStroke(Color.LIGHTGRAY);
                g.strokeLine(0, horizontalLine, width, horizontalLine);
                g.setStroke(Color.BLACK);
                g.fillText(
                        Integer.toString(i),
                        center.getX() - fontSize / 4 - digitsCount(i) * fontSize * 7 / 10 - (i < 0 ? fontSize / 4 : 0),
                        horizontalLine + fontSize / 3
                );
            }
        }
        //endregion
        
        //region Paints axises and center
        g.setStroke(Color.GRAY);
        g.setLineWidth(2);
        g.strokeLine(0, center.getY(), width, center.getY());
        g.strokeLine(center.getX(), 0, center.getX(), height);
        g.setStroke(Color.BLACK);
        g.fillText(Integer.toString(0), center.getX() - fontSize, center.getY() + fontSize);
        //endregion
    }
    //endregion
}
