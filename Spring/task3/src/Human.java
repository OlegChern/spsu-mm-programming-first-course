import java.util.Scanner;

public class Human extends Player {
    public Human(String name, int money) {
        super(name, money);
    }

    @Override
    public Action Play(Card dealersFirstCard) {
        System.out.println("Your turn");
        Scanner in = new Scanner(System.in);
        System.out.println("1 - hit");
        System.out.println("2 - stand");
        int input = in.nextInt();
        if (input == 1)
            return Action.HIT;
        else
            return Action.STAND;
    }
}
