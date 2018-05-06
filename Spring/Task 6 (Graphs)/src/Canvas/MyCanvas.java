package Canvas;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.geom.Point2D;
import java.util.Arrays;


/**
 * Canvas for plots paintings.
 * <p>
 * To paint a plot {@linkplain #setPlot(Plottable)} must be called with desired plot
 * as argument and then {@linkplain #repaint()} must be invoked to display results.
 * <p>
 * Internally, the plot is painted using {@linkplain #paintPlot(Graphics2D, Plottable)} via
 * {@linkplain Plottable} interface.
 * <p>
 * <p>
 * The canvas supports zooming (in and out):
 *
 * @see #zoomIn()
 * @see #zoomOut()
 * and mouse dragging:
 * @see #MyCanvas()
 */
public class MyCanvas extends JPanel {
    
    private Dimension size;
    private Point2D.Double centerCoefficients = new Point2D.Double(0.5, 0.5);
    private Point center;
    
    private Plottable plot;
    
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
    private Point lastMousePosition;
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
    
    public MyCanvas() {
        super();
        
        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                lastMousePosition = e.getPoint();
            }
        });
        addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                if (dist2Between(e.getPoint(), lastMousePosition) >= MINIMUM_MOUSE_MOTION_DISTANCE2) {
                    double diffX = e.getPoint().getX() - lastMousePosition.getX();
                    double diffY = e.getPoint().getY() - lastMousePosition.getY();
                    
                    centerCoefficients.x += diffX / size.getWidth();
                    centerCoefficients.y += diffY / size.getHeight();
                    
                    updateCenter(size);
                    lastMousePosition = e.getPoint();
                    repaint();
                }
            }
        });
    }
    
    /**
     * Updates the coordinates of origin according to the given size.
     *
     * @param newSize New size of the component
     */
    private void updateCenter(Dimension newSize) {
        center = new Point(
                (int) Math.round(centerCoefficients.x * newSize.width),
                (int) Math.round(centerCoefficients.y * newSize.height)
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
     * To paint it immediately {@linkplain #repaint()} must be called after
     * this method invocation.
     *
     * @param plot new plot
     */
    public void setPlot(Plottable plot) {
        this.plot = plot;
    }
    
    /**
     * Zooms in field if {@linkplain #pixelsPerOneDivision} is not bigger than
     * {@linkplain #MAX_PIXELS_PER_ONE_DIVISION}.
     */
    public void zoomIn() {
        if (pixelsPerOneDivision + SCALE_STEP <= MAX_PIXELS_PER_ONE_DIVISION) {
            pixelsPerOneDivision += SCALE_STEP;
        }
        repaint();
    }
    
    /**
     * Zooms out field if {@linkplain #pixelsPerOneDivision} is not smaller than
     * {@linkplain #MIN_PIXELS_PER_ONE_DIVISION}.
     */
    public void zoomOut() {
        if (pixelsPerOneDivision - SCALE_STEP >= MIN_PIXELS_PER_ONE_DIVISION) {
            pixelsPerOneDivision -= SCALE_STEP;
        }
        repaint();
    }
    
    //region Painting methods
    
    /**
     * Main method responsible for the component painting.
     *
     * @param g Graphics context
     */
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        
        Dimension currentSize = getSize();
        if (size == null || !size.equals(currentSize)) {
            size = getSize();
            updateCenter(currentSize);
        }
        
        setBackground(Color.WHITE);
        paintGrid((Graphics2D) g);
        if (plot != null) {
            paintPlot((Graphics2D) g, plot);
        }
    }
    
    /**
     * Converts a pixel to the real point this pixel represents.
     *
     * @param p Pixel to convert
     * @return Real point this pixel represents
     */
    private Point2D.Double convertPixelToRealPoint(Point p) {
        return new Point2D.Double(
                (p.x - center.getX()) / pixelsPerOneDivision,
                (center.getY() - p.y) / pixelsPerOneDivision
        );
    }
    
    /**
     * Converts a real point to the pixel that represents its area.
     *
     * @param p Real point to convert
     * @return Pixel that represents given pixel area
     */
    private Point convertRealPointToPixel(Point2D.Double p) {
        return new Point(
                center.x + (int) Math.round(p.x * pixelsPerOneDivision),
                center.y - (int) Math.round(p.y * pixelsPerOneDivision)
        );
    }
    
    /**
     * Checks given pixel carefully in a zoom. It is invoked usually near the edges of the plot
     * which are especially potential of the accuracy loss.
     * <p>
     * Normally, pixel x-coordinate converts to the real point it represents using
     * {@linkplain #convertPixelToRealPoint(Point)} and gets points of plot
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
    private Point[] checkInZoom(Plottable shape, int x) {
        for (int dx = -ZOOM_REGION / 2; dx < ZOOM_REGION / 2; dx++) {
            double realX = (x * ZOOM_REGION + dx - center.getX() * ZOOM_REGION) / (pixelsPerOneDivision * ZOOM_REGION);
            Point[] plotPoints = Arrays.stream(shape.getPointsByX(realX))
                    .map(this::convertRealPointToPixel)
                    .distinct()
                    .toArray(Point[]::new);
            if (plotPoints.length > 0) {
                return plotPoints;
            }
        }
        
        return new Point[0];
    }
    
    /**
     * Returns a square of the distance between two pixels.
     *
     * @param a First pixel
     * @param b Second pixel
     * @return square of the distance between given pixels
     */
    private int dist2Between(Point a, Point b) {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    }
    
    /**
     * Gets an array of the points and paints lines between any points in it if the
     * distance between them is not bigger than {@linkplain #MAX_DISTANCE_BETWEEN_NEIGHBORS}.
     *
     * @param g      Graphics context where line are painted
     * @param points Array which points are to be connected by lines
     */
    private void paintLinesBetweenNeighbors(Graphics2D g, Point[] points) {
        for (int i = 0; i < points.length; i++) {
            for (int j = i + 1; j < points.length; j++) {
                if (dist2Between(points[i], points[j]) <= MAX_DISTANCE2_BETWEEN_NEIGHBORS) {
                    g.drawLine(points[i].x, points[i].y, points[j].x, points[j].y);
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
     * @param g     Graphics context where plot is too be painted
     * @param shape Plot to be painted.
     */
    private void paintPlot(Graphics2D g, Plottable shape) {
        g.setColor(Color.BLUE);
        g.setStroke(new BasicStroke(1));
        
        Point[] previous = new Point[0];
        
        for (int x = 0; x < size.width; x++) {
            double realX = convertPixelToRealPoint(new Point(x, 0)).getX();
            Point[] plotPoints = Arrays.stream(shape.getPointsByX(realX))
                    .map(this::convertRealPointToPixel)
                    .distinct() // removes pixels duplicates
                    .toArray(Point[]::new);
            
            if (plotPoints.length > 0 && previous.length == 0) {
                previous = checkInZoom(shape, x - 1);
                for (Point foundPoint : previous) {
                    g.drawLine(foundPoint.x, foundPoint.y, foundPoint.x, foundPoint.y);
                }
                paintLinesBetweenNeighbors(g, previous.length > 0 ? previous : plotPoints);
            }
            
            if (plotPoints.length == 0 && previous.length > 0) {
                plotPoints = checkInZoom(shape, x);
                paintLinesBetweenNeighbors(g, plotPoints.length > 0 ? plotPoints : previous);
            }
            
            // Lines will be drawn from the points in the first array to the points of the second array.
            // To draw more potential lines the first array is considered to be bigger than the second one.
            Point[] biggest = plotPoints.length > previous.length ? plotPoints : previous;
            Point[] other = plotPoints.length > previous.length ? previous : plotPoints;
            
            for (Point point : biggest) {
                if (other.length == 0) {
                    g.drawLine(point.x, point.y, point.x, point.y);
                } else {
                    Point closest = other[0];
                    for (int i = 1; i < other.length; i++) {
                        if (dist2Between(other[i], point) < dist2Between(closest, point)) {
                            closest = other[i];
                        }
                    }
                    
                    if (dist2Between(closest, point) < MAX_DISTANCE2_BETWEEN_NEIGHBORS) {
                        g.drawLine(closest.x, closest.y, point.x, point.y);
                    }
                }
            }
            
            previous = plotPoints;
        }
    }
    
    /**
     * Helper-method of {@linkplain #paintGrid(Graphics2D)} implementation.
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
     *
     * @param g Graphics context
     */
    private void paintGrid(Graphics2D g) {
        //region Paints auxiliary lines with numbers
        g.setStroke(new BasicStroke(1));
        int fontSize = Math.min(Math.max(pixelsPerOneDivision / 3, 10), 25);
        g.setFont(new Font("TimesRoman", Font.PLAIN, fontSize));
        
        int leftVerticalLine = center.x % pixelsPerOneDivision;
        int leftVerticalLineNumber = (leftVerticalLine - center.x) / pixelsPerOneDivision;
        for (int verticalLine = leftVerticalLine, i = leftVerticalLineNumber;
             verticalLine < size.width;
             verticalLine += pixelsPerOneDivision, i++) {
            
            if (i != 0) {
                g.setColor(Color.LIGHT_GRAY);
                g.drawLine(verticalLine, 0, verticalLine, size.height);
                g.setColor(Color.BLACK);
                g.drawString(
                        Integer.toString(i),
                        verticalLine - fontSize / 2 - (i < 0 ? fontSize / 4 : 0),
                        center.y + fontSize
                );
            }
        }
        int topHorizontalLine = center.y % pixelsPerOneDivision;
        int topHorizontalLineNumber = (center.y - topHorizontalLine) / pixelsPerOneDivision;
        for (int horizontalLine = topHorizontalLine, i = topHorizontalLineNumber;
             horizontalLine < size.height;
             horizontalLine += pixelsPerOneDivision, i--) {
            
            if (i != 0) {
                g.setColor(Color.LIGHT_GRAY);
                g.drawLine(0, horizontalLine, size.width, horizontalLine);
                g.setColor(Color.BLACK);
                g.drawString(
                        Integer.toString(i),
                        center.x - fontSize / 4 - digitsCount(i) * fontSize * 7 / 10 - (i < 0 ? fontSize / 4 : 0),
                        horizontalLine + fontSize / 3
                );
            }
        }
        //endregion
        
        //region Paints axises and center
        g.setColor(Color.GRAY);
        g.setStroke(new BasicStroke(2));
        g.drawLine(0, center.y, size.width, center.y);
        g.drawLine(center.x, 0, center.x, size.height);
        g.setColor(Color.BLACK);
        g.drawString(Integer.toString(0), center.x - fontSize, center.y + fontSize);
        //endregion
    }
    //endregion
}
