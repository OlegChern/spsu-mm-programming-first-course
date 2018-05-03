package sample;

public class mathForFuncParabollicRight{
    private FuncParabollicRight func;
    private double Xcur;
    private double Xmax;
    private double step;
    private double[] borders;
    private static final double MAX_Y = 12;
    private static final double MIN_Y = -12;
    private static final double MAX_X = 5;
    private static final double MIN_X = -5;
    mathForFuncParabollicRight() {
        this.func = new FuncParabollicRight();
        step = 0.1;
        Xmax = MAX_X;
        Xcur = Xmax;
        borders = new double[4];
        borders[0] = MIN_Y;
        borders[1] = MAX_Y;
        borders[2] = MIN_X;
        borders[3] = MAX_X;
    }
    public double[] giveResolution(){
        return borders;
    }

    private void setBorders(double[] borders) {
        this.borders = borders;
    }

    private void setStep(double step) {
        this.step = step;
    }

    public double getStep() {
        return step;
    }

    public double[] givePoint(){
        double[] point = new double[2];
        point[0] = Xcur;
        point[1] = func.getValue(Xcur);
        //System.out.println(point[0] + " " + point[1]);
        if (point[0] < 0.1){
            func.changePositivness();
            step = -step;
        }
        Xcur -= step;
        return point;
    }

    public void Scaling(double x, double y, double scroll) {
        double[] newBorders = new double[4];
        newBorders[3] = x + MAX_X / scroll;
        newBorders[2] = x + MIN_X / scroll;
        newBorders[1] = y + MAX_Y / scroll;
        newBorders[0] = y + MIN_Y / scroll;
        Xmax = newBorders[3];
        Xcur = Xmax;
        setBorders(newBorders);
        setStep(step / scroll);
    }
}