import BlackjackGame.*;

public class Main {

    public static void main(String[] args) {

        BlackjackTable testTable = new BlackjackTable();

        Player testPlayer = new NormalBot(1000, testTable);
        testTable.addPlayer(testPlayer);

        Player testAdvanced = new AdvancedBot(1000, testTable);
        testTable.addPlayer(testAdvanced);

        System.out.println("Initially, players have 1000 credits to spend playing.\n" +
                "They aim to play 40 games (or less if they run out of money).\n" +
                "Normy is an ordinary player whose decision making is quite simple\n" +
                "Expy is an experienced player who makes decisions based on some conditions.\n ");

        for (int i = 0; i < 40; i++) {
            testTable.NewRound();
        }

        System.out.println(testPlayer.getStatistic("Normy"));
        System.out.println(testAdvanced.getStatistic("Expy"));

    }
}
