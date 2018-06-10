package JavaFX;

import GraphMath.*;
import GraphMath.Point;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;


public class DrawCanvas extends Canvas {

    private static final double DEFAULT_ACCURACY = 0.1;
    private static final int DEFAULT_SCALE_DIVISION = 10;
    private static final int DEFAULT_INDENT = 50;
    private static final int DEFAULT_HATCH_SIZE = 2;

    private static final int HATCH_COEFFICIENT = 10;
    private static final int SCALE_STEP = 3;

    private static final int MIN_ZOOM_SCALE = 0;
    private static final int MAX_ZOOM_SCALE = 75;
    private static final int DEFAULT_ZOOM_SCALE = 30;

    private Point centre;
    private int currentZoom;
    private int indentX, indentY;
    private int scaleDivision;
    private int hatchSize;

    private Curve currentCurve;

    DrawCanvas(double width, double height) {
        super(width, height);
        centre = new Point(getWidth() / 2, getHeight() / 2);
        Curve.setAccuracy(DEFAULT_ACCURACY);

        widthProperty().addListener(change -> repaint());
        heightProperty().addListener(change -> repaint());

        currentZoom = DEFAULT_ZOOM_SCALE;

        indentX = DEFAULT_INDENT;
        indentY = DEFAULT_INDENT;

        hatchSize = DEFAULT_HATCH_SIZE;
        scaleDivision = DEFAULT_SCALE_DIVISION;
    }

    public void zoomIn() {
        if (currentZoom + SCALE_STEP <= MAX_ZOOM_SCALE) {
            currentZoom += SCALE_STEP;
            repaint();
        }
    }

    public void zoomOut() {
        if (currentZoom - SCALE_STEP >= MIN_ZOOM_SCALE) {
            currentZoom -= SCALE_STEP;
            repaint();
        }
    }

    public void zoomDefault() {
        currentZoom = DEFAULT_ZOOM_SCALE;
        repaint();
    }

    public void setCurve(Curve curve) {
        currentCurve = curve;
    }

    public void repaint() {
        adjustParameters();
        updateCentre();
        clear();
        drawAxis();
        drawCurve(currentCurve);
    }

    private void clear() {
        getGraphicsContext2D().clearRect(0, 0, getWidth(), getHeight());
    }

    private void adjustParameters() {
        indentX = DEFAULT_INDENT - currentZoom;
        indentY = DEFAULT_INDENT - currentZoom;
        scaleDivision = DEFAULT_SCALE_DIVISION + currentZoom;
        hatchSize = DEFAULT_HATCH_SIZE + (currentZoom / HATCH_COEFFICIENT);
    }

    private void updateCentre() {
        centre = new Point(getWidth() / 2, getHeight() / 2);
    }

    private void drawAxis() {
        GraphicsContext g = getGraphicsContext2D();
        g.setStroke(Color.BLACK);

        // Drawing X-axis
        g.strokeLine(centre.x, centre.y, indentX, centre.y);
        g.strokeLine(centre.x, centre.y, getWidth() - indentX, centre.y);

        // Drawing Y-axis
        g.strokeLine(centre.x, centre.y, centre.x, indentY);
        g.strokeLine(centre.x, centre.y, centre.x, getHeight() - indentY);

        // Drawing Divisions for X-axis
        for (int i = (int) centre.x + scaleDivision, k = 1; i < getWidth() - indentX; i += scaleDivision, k++) {
            g.strokeLine(i, centre.y + hatchSize, i, centre.y - hatchSize);
        }

        for (int i = (int) centre.x - scaleDivision, k = -1; i > indentX; i -= scaleDivision, k--) {
            g.strokeLine(i, centre.y + hatchSize, i, centre.y - hatchSize);
        }

        // Drawing Divisions for Y-axis
        for (int i = (int) centre.y - scaleDivision, k = 1; i > indentY; i -= scaleDivision, k++) {
            g.strokeLine(centre.x + hatchSize, i, centre.x - hatchSize, i);
        }

        for (int i = (int) centre.y + scaleDivision, k = -1; i < getHeight() - indentY - scaleDivision; i += scaleDivision, k--) {
            g.strokeLine(centre.x + hatchSize, i, centre.x - hatchSize, i);
        }
    }

    private double convertXtoVirtual(int x) {
        return (x - centre.x) / scaleDivision;
    }

    private double convertYtoReal(double y) {
        return centre.y + Math.round(y * scaleDivision);
    }

    private void drawCurve(Curve curve) {
        GraphicsContext g = getGraphicsContext2D();
        g.setStroke(Color.BLUE);
        Point[] previous = new Point[0];
        int ending = (int) (getWidth() - indentX);
        for (int i = indentX; i <= ending ; i++) {
            Point[] current = curve.getPoint(convertXtoVirtual(i));
            if (current.length != 0) {
                for (Point currentPoint : current) {
                    currentPoint.x = i;
                    currentPoint.y = convertYtoReal(currentPoint.y);
                }
                if (previous.length != 0) {
                    g.strokeLine(current[0].x, current[0].y, previous[0].x, previous[0].y);
                    g.strokeLine(current[1].x, current[1].y, previous[1].x, previous[1].y);
                }
            }
            previous = current;
        }
    }
}
