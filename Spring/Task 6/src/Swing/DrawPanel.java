package Swing;

import GraphMath.*;
import GraphMath.Point;

import javax.swing.*;
import java.awt.*;

public class DrawPanel extends JPanel {

    private static final double DEFAULT_ACCURACY = 0.01;

    private static final int DEFAULT_SCALE_DIVISION = 10;
    private static final int DEFAULT_INDENT = 50;
    private static final int DEFAULT_HATCH_SIZE = 2;

    private static final int HATCH_COEFFICIENT = 10;
    private static final int SCALE_STEP = 3;

    private static final int MIN_ZOOM_SCALE = -3;
    private static final int MAX_ZOOM_SCALE = 66;
    private static final int DEFAULT_ZOOM_SCALE = 30;

    private Point centre;
    private int currentZoom;
    private int indentX, indentY;
    private int scaleDivision;
    private int hatchSize;

    private Curve currentCurve;

    DrawPanel() {
        setBackground(Color.WHITE);
        centre = new Point(getWidth() / 2, getHeight() / 2);
        currentZoom = DEFAULT_ZOOM_SCALE;
        Curve.setAccuracy(DEFAULT_ACCURACY);

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

    @Override
    public void paint(Graphics g) {
        super.paint(g);

        adjustParameters();
        updateCentre();

        drawAxis(g);
        drawCurve(currentCurve, g);
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

    private void drawAxis(Graphics g) {
        g.setColor(Color.BLACK);

        // Drawing X-axis
        g.drawLine((int) centre.x, (int) centre.y, indentX, (int) centre.y);
        g.drawLine((int) centre.x, (int) centre.y, getWidth() - indentX, (int) centre.y);

        // Drawing Y-axis
        g.drawLine((int) centre.x, (int) centre.y, (int) centre.x, indentY);
        g.drawLine((int) centre.x, (int) centre.y, (int) centre.x, getHeight() - indentY);

        // Drawing Divisions for X-axis
        for (int i = (int) centre.x + scaleDivision, k = 1; i < getWidth() - indentX; i += scaleDivision, k++) {
            g.drawLine(i, (int) centre.y + hatchSize, i, (int) centre.y - hatchSize);
        }

        for (int i = (int) centre.x - scaleDivision, k = -1; i > indentX; i -= scaleDivision, k--) {
            g.drawLine(i, (int) centre.y + hatchSize, i, (int) centre.y - hatchSize);
        }

        // Drawing Divisions for Y-axis
        for (int i = (int) centre.y - scaleDivision, k = 1; i > indentY; i -= scaleDivision, k++) {
            g.drawLine((int) centre.x + hatchSize, i, (int) centre.x - hatchSize, i);
        }

        for (int i = (int) centre.y + scaleDivision, k = -1; i < getHeight() - indentY - scaleDivision; i += scaleDivision, k--) {
            g.drawLine((int) centre.x + hatchSize, i, (int) centre.x - hatchSize, i);
        }
    }

    private double convertXtoVirtual(int x) {
        return (x - centre.x) / scaleDivision;
    }

    private double convertYtoReal(double y) {
        return centre.y + y * scaleDivision;
    }

    private void drawCurve(Curve curve, Graphics g) {
        g.setColor(Color.blue);
        Point[] previous = new Point[0];
        for (int i = indentX; i <= getWidth() - indentX; i++) {
            Point[] current = curve.getPoint(convertXtoVirtual(i));
            if (current.length != 0) {
                for (Point currentPoint: current) {
                    currentPoint.x = i;
                    currentPoint.y = convertYtoReal(currentPoint.y);
                }
                if (previous.length != 0) {
                    g.drawLine((int) current[0].x, (int) current[0].y, (int) previous[0].x, (int) previous[0].y);
                    g.drawLine((int) current[1].x, (int) current[1].y, (int) previous[1].x, (int) previous[1].y);
                }
            }
            previous = current;
        }
    }
}