package mathlib;

import java.util.Vector;

public class FuncSeries {
    private Vector<Point> points;
    private String seriesName;

    public FuncSeries(Vector<Point> points, String seriesName) {
        this.points = points;
        this.seriesName = seriesName;
    }

    public Vector<Point> getPoints() {
        return points;
    }

    public String getSeriesName() {
        return seriesName;
    }
}
