package BlackjackGame;

import java.util.ArrayList;

public class BlackjackTable implements Observer {

    private Deck currentDeck;

    private Player dealer;
    private ArrayList<Player> players;

    private ArrayList<Player> playersFinished;
    private ArrayList<Player> playersSurrendered;

    private boolean dealerInPlay;


    public BlackjackTable() {

        this.dealer = new Dealer(this);

        this.players = new ArrayList<>();
        this.playersSurrendered = new ArrayList<>();
        this.playersFinished = new ArrayList<>();

        this.currentDeck = new Deck();
        this.dealerInPlay = false;

    }


    private void reshuffle() {
        currentDeck = new Deck();
    }

    private void giveStartingHand() {

        for (int i = 0; i < 2; i++) {

            dealer.hand.add(currentDeck.Pop());
            for (Player currentPlayer : players) {
                currentPlayer.hand.add(currentDeck.Pop());
            }
        }
    }

    private void giveCard(Player player) {
        player.hand.add(currentDeck.Pop());
    }

    public void addPlayer(Player newPlayer) {
        this.players.add(newPlayer);
    }

    public void NewRound() {

        if (this.players.isEmpty()) return;

        playersFinished.clear();
        playersSurrendered.clear();

        if (this.currentDeck.getCurrentSize() < this.currentDeck.getDefaultSize() * 2 / 3) reshuffle();

        dealerInPlay = true;

        for (Player currentPlayer : players) {
            currentPlayer.MakeBet();
        }

        giveStartingHand();

        for (Player currentPlayer : players) {
            while (!(playersFinished.contains(currentPlayer) || playersSurrendered.contains(currentPlayer)))
                currentPlayer.Play();
        }

        while (dealerInPlay)
            dealer.Play();

        for (Player currentPlayer : playersFinished)
            playerFinish(currentPlayer);

        for (Player currentPlayer : playersSurrendered)
            playerSurrender(currentPlayer);

        dealer.clearHand();

        for (int i = 0; i < players.size(); i++)
            if (players.get(i).getMoney() <= 0) players.remove(players.get(i));
    }

    private void playerFinish(Player player) {

        if (checkIfBlackJack(player)) return;

        Integer playerScore = player.getScore();
        Integer dealerScore = dealer.getScore();

        if (dealerScore > 21) {

            if (playerScore < dealerScore)
                player.winMoney(player.getCurrentStake());
            else
                player.loseMoney(player.getCurrentStake());

        } else if (playerScore <= 21 && playerScore > dealerScore) {
            player.winMoney(player.getCurrentStake());

        } else if (!playerScore.equals(dealerScore)) {
            player.loseMoney(player.getCurrentStake());
        }

        player.clearHand();
    }

    private void playerSurrender(Player player) {

        player.loseMoney(player.getCurrentStake() / 2);
        player.clearHand();
    }

    private boolean checkIfBlackJack(Player player) {

        if (player.hand.size() == 2 && player.getScore() == 21)
            if (!(dealer.hand.size() == 2 && dealer.getScore() == 21)) {
                player.winMoney((player.getCurrentStake() * 3) / 2);
                player.clearHand();
                return true;
            }

            return false;
    }


    @Override
    public void onNotify(GameEvent event) {

        Player tempPlayer = event.getEventSource();
        switch (event.getType()) {

            case HIT: {
                giveCard(tempPlayer);
                break;
            }

            case SURRENDER: {
                playersSurrendered.add(tempPlayer);
                break;
            }

            case STAND: {
                playersFinished.add(tempPlayer);
                break;
            }

            case DOUBLE: {
                tempPlayer.doubleDown();
                giveCard(tempPlayer);
                playersFinished.add(tempPlayer);
                break;
            }

            case DEALERFINISH: {
                dealerInPlay = false;
                break;
            }
        }
    }
}
