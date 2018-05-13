import java.util.Scanner;

public class Main
{
    public static double CheckBot(Player bot)
    {
        double result = 0;
        BlackJack blackjack;

        for (int i = 0; i < 100; i++)
        {
            blackjack = new BlackJack(bot, null);
            for (int j = 0; j < 40; j++)
            {
                blackjack.PlayBlackjack(false);
                blackjack.Reset();
            }
            result += bot.Money;
            bot.ChangeAmountOfMoney(-bot.Money);
        }

        return result / 100;
    }

    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        System.out.println("Checking Bots:");
        System.out.println("Smart bot: " + CheckBot(new SmartBot(0)));
        System.out.println("Like Dealer bot: " +  CheckBot(new LikeDealerBot(0)));
        System.out.println("1 - play without bot");
        System.out.println("2 - play with SmartBot");
        System.out.println("3 - play with LikeDealerBot");
        int input = in.nextInt();
        BlackJack blackjack;
        Human realPlayer = new Human("You", 1000);
        if (input == 1)
        {
            blackjack = new BlackJack(realPlayer, null);
        }
        else if (input == 2)
        {
            blackjack = new BlackJack(realPlayer, new SmartBot(1000));
        }
        else
        {
            blackjack = new BlackJack(realPlayer, new LikeDealerBot(1000));
        }

        blackjack.PrintMoney();

        boolean stop = false;
        while (!stop)
        {
            blackjack.Reset();
            System.out.println("Game is on");
            blackjack.PlayBlackjack(true);
            blackjack.PrintResult();
            System.out.println("Continue play - 1");
            System.out.println("Stop game - 2");
            int res = in.nextInt();
            if(res == 1)
            {
                stop = false;
            }
            else
            {
                stop = true;
            }
        }

        System.out.println("Results:");
        blackjack.PrintMoney();
    }
}

