package GraphMath;

public class Circle extends Ellipse {

    public Circle(int r) {
        super(r, r);
    }

    @Override
    public String toString() {
        return getClass().getName() + " (R = " + a + " )";
    }
}
