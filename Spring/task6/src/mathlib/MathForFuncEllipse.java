package mathlib;

public class MathForFuncEllipse extends FuncMath{
    public MathForFuncEllipse() {
        this.func = new FuncEllipse();
        step = DEFAULT_STEP;
        Xmax = MAX_X;
        Xcur = Xmax;
        borders = new Borders(MAX_X, MIN_X, MAX_Y, MIN_Y);
    }
}