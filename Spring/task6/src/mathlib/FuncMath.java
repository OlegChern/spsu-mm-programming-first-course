package mathlib;

import java.util.Vector;


public abstract class FuncMath {
    protected Function func;
    protected double Xcur;
    protected double Xmax;
    protected double step;
    protected Borders borders;
    protected static final double MAX_Y = 12;
    protected static final double MIN_Y = -12;
    protected static final double MAX_X = 5;
    protected static final double MIN_X = -5;
    protected static final double DEFAULT_STEP = 0.05;
    protected static final double DEFAULT_POINT_X = 0;
    protected static final double DEFAULT_POINT_Y = 0;
    protected static final double DEFAULT_SCROLL = 1;


    public void Scaling(double x, double y, double scroll) {
        Borders newBorders = new Borders(x + MAX_X / scroll, x + MIN_X / scroll, y + MAX_Y / scroll, y + MIN_Y / scroll);
        Xmax = newBorders.getXmax();
        Xcur = Xmax;
        setBorders(newBorders);
        setStep(step / scroll);
    }

    public Borders giveResolution(){
        return borders;
    }

    private void setBorders(Borders borders) {
        this.borders = borders;
    }

    private void setStep(double step) {
        this.step = step;
    }

    public double getStep() {
        return step;
    }

    public static double getDefaultScroll() {
        return DEFAULT_SCROLL;
    }

    public static double getDefaultPointX() {
        return DEFAULT_POINT_X;
    }

    public static double getDefaultPointY() {
        return DEFAULT_POINT_Y;
    }

    public static double getDefaultStep() {
        return DEFAULT_STEP;
    }

    public static Borders getDefaultResolution() {
        return new Borders(MAX_X, MIN_X, MAX_Y, MIN_Y);
    }

    public Vector<FuncSeries> giveSeries(double X, double Y, double scroll) {
        Scaling(X, Y, scroll);
        int i = 1;
        Vector <FuncSeries> series = new Vector<>();
        Vector <Point> points = new Vector<>();
        //positive part
        boolean flagStep = true;
        double oldStep = step;
        for (double j = borders.getXmin(); j < borders.getXmax() + step; j += step) {
            if (func.getValue(j, true, step) <= borders.getYmax() && func.getValue(j, true, step) >= borders.getYmin()) {
                if (Math.abs(func.getDeadPoint() - func.getValue(j, true, step)) <= func.getDeadSphereRadius() && scroll >= 3) {
                    if (flagStep) {
                        oldStep = step;
                        step *= func.getEnrichStepCoeff();
                        flagStep = false;
                    }
                    points.add(new Point(j, func.getValue(j, true, step)));
                } else {
                    flagStep = true;
                    step = oldStep;
                    points.add(new Point(j, func.getValue(j, true, step)));
                }
            } else if (points.size() > 0) {
                FuncSeries tmp = new FuncSeries(points, "positive " + i);
                i++;
                series.add(tmp);
                points = new Vector<>();
            }
        }
        if (points.size() > 0 && (series.size() == 0 || !series.elementAt(series.size() - 1).getPoints().equals(points))) {
            FuncSeries tmp = new FuncSeries(points, "positive " + i);
            series.add(tmp);
        }
        i = 1;
        //negative part
        points = new Vector<>();
        flagStep = true;
        step = oldStep;
        for (double j = borders.getXmin(); j < borders.getXmax() + step; j += step) {
            if (func.getValue(j, false, step) <= borders.getYmax() && func.getValue(j, false, step) >= borders.getYmin()) {
                if (Math.abs(func.getDeadPoint() - func.getValue(j, false, step)) <= func.getDeadSphereRadius() && scroll >= 3) {
                    if (flagStep) {
                        oldStep = step;
                        step *= func.getEnrichStepCoeff();
                        flagStep = false;
                    }
                    points.add(new Point(j, func.getValue(j, false, step)));
                } else {
                    flagStep = true;
                    step = oldStep;
                    points.add(new Point(j, func.getValue(j, false, step)));
                }
            } else if (points.size() > 0) {
                FuncSeries tmp = new FuncSeries(points, "negative " + i);
                i++;
                series.add(tmp);
                points = new Vector<>();
            }
        }
        step = oldStep;
        if (points.size() > 0 && (series.size() == 0 || !series.elementAt(series.size() - 1).getPoints().equals(points))) {
            FuncSeries tmp = new FuncSeries(points, "negative " + i);
            series.add(tmp);
        }
        return series;
    }
}