import BlackjackGame.*;

import org.picocontainer.DefaultPicoContainer;
import org.picocontainer.MutablePicoContainer;

public class Main {

    public static void main(String[] args) {
        MutablePicoContainer pico = new DefaultPicoContainer();

        pico.addComponent(NormalBot.class);
        pico.addComponent(AdvancedBot.class);
        pico.addComponent(Dealer.class);
        pico.addComponent(Deck.class);
        pico.addComponent(BlackjackTable.class);

        BlackjackTable blackjack = pico.getComponent(BlackjackTable.class);
        blackjack.addPlayer(pico.getComponent(NormalBot.class), "Normy", 1000);
        blackjack.addPlayer(pico.getComponent(AdvancedBot.class), "Expy", 1000);

        for (int i = 0; i < 40; i++) {
            blackjack.NewRound();
        }

        System.out.println(blackjack.getStatistics());

    }
}

