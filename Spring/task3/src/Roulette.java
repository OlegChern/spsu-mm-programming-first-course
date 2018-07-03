import java.util.Random;

public class Roulette {
    public int spin() {
        Random random = new Random();
        return random.nextInt(37);
    }
}
