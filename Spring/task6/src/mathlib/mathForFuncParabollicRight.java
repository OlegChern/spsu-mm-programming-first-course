package mathlib;

public class mathForFuncParabollicRight extends FuncMath{

    public mathForFuncParabollicRight() {
        this.func = new FuncParabollicRight();
        step = DEFAULT_STEP;
        Xmax = MAX_X;
        Xcur = Xmax;
        borders = new Borders(MAX_X, MIN_X, MAX_Y, MIN_Y);
    }
}
