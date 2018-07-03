import java.util.Scanner;
import org.picocontainer.DefaultPicoContainer;
import org.picocontainer.MutablePicoContainer;

public class Main {

    public static final int START_CASH = 200;

    public static void main(String[] args) {
        int tmp, count;
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter number of players");
        count = sc.nextInt();
        Player[] players = new Player[count];
        for (int i = 0; i < count; i++) {
            System.out.println("Enter type of next player:\n1. SillyBot\n2. CleverBot");
            tmp = sc.nextInt();
            switch (tmp) {
                case 1:
                    players[i] = new SillyBot(START_CASH);
                    break;
                case 2:
                    players[i] = new CleverBot(START_CASH);
            }
        }
        MutablePicoContainer pico = new DefaultPicoContainer();
        pico.addComponent(Casino.class);
        pico.addComponent(Roulette.class);
        pico.addComponent(Game.class);
        Game game = (Game) pico.getComponent(Game.class);
        game.setPlayers(players);
        for (int i = 0; i < 40; i++) {
            game.Round();
        }
        for (int i = 0; i < count; i++) {
            System.out.println("Player number " + (i + 1) + " now has " + players[i].showCash() + " dollars");
        }
    }
}