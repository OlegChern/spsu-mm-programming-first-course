import java.util.Random;

public class Roulette {
    public int spin() {
        Random random = new Random();
        return random.nextInt(Casino.AMOUNT_OF_NUMBERS);
    }
}
