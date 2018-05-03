package sample;


public class FuncParabollicRight{
    private boolean positivness;
    public FuncParabollicRight(){
        positivness = true;
    }
    public double getValue(double X) {
        if (positivness) {
            return (Math.sqrt(X * X * X));
        }
        else {
            return -(Math.sqrt(X * X * X));
        }
    }
    public void changePositivness(){
        positivness = false;
    }
}
