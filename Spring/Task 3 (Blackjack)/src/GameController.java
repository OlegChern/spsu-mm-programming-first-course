import java.util.*;
import java.util.concurrent.atomic.AtomicBoolean;


public class GameController {
    private Map<String, Gambler> players;
    
    public static final int INFINITE_GAME = -1;
    private int duration;
    
    public static final int DEFAULT_DECKS_COUNT = 8;
    private ShuffleMachine shuffleMachine;
    
    public static final int DEFAULT_MINIMUM_BET = 5;
    private int minimumBet;
    
    public static final Commentator DEFAULT_COMMENTATOR = null;
    private Commentator commentator;
    
    public GameController() {
        players = new HashMap<>();
        duration = INFINITE_GAME;
        shuffleMachine = new ShuffleMachine(DEFAULT_DECKS_COUNT);
        minimumBet = DEFAULT_MINIMUM_BET;
        commentator = DEFAULT_COMMENTATOR;
    }
    
    public void registerPlayer(Player player, String name, double money) throws RegistrationFailedException {
        if (player == null) {
            throw new NullPointerException();
        }
        if (money <= 0) {
            throw new IllegalArgumentException("money must be positive, given value: " + money);
        }
        
        if (players.containsKey(name)) {
            throw new RegistrationFailedException("That name is already engaged");
        }
        players.put(name, new Gambler(player, money));
    }
    
    public void setDuration(int matchCount) {
        if (matchCount <= 0 && matchCount != INFINITE_GAME) {
            throw new IllegalArgumentException(
                    "duration must be positive or GameController.INFINITE_GAME, given value: " + matchCount);
        }
        
        this.duration = matchCount;
    }
    
    public void setDecksCount(int decksCount) {
        if (decksCount <= 0) {
            throw new IllegalArgumentException("decksCount must be positive, given value: " + decksCount);
        }
        
        shuffleMachine = new ShuffleMachine(decksCount);
    }
    
    public void setMinimumBet(int minimumBet) {
        if (minimumBet < 0) {
            throw new IllegalArgumentException("minimumBet must not be negative, given value: " + minimumBet);
        }
        this.minimumBet = minimumBet;
    }
    
    public void setCommentator(Commentator commentator) {
        this.commentator = commentator;
    }
    
    public void play() {
        if (players.isEmpty()) {
            throw new IllegalStateException("No players in game");
        }
        
        for (int i = 0; i < duration; i = (duration == INFINITE_GAME ? i : i + 1)) {
            playMatch();
        }
        
        commentator.comment("\nFinal results:");
        players.forEach((name, gambler) -> {
            double delta = gambler.money - gambler.startMoney;
            commentator.comment(name, "have " + gambler.money + ", " + (delta >= 0 ? "earned " : "lost ") + Math.abs(delta));
        });
    }
    
    private void playMatch() {
        
        // players make bets and get cards
        Map<String, PlayerState> states = new HashMap<>();
        players.forEach((name, gambler) -> {
            if (gambler.money >= minimumBet) {
                double bet = gambler.player.makeBet(gambler.money, minimumBet);
                if (bet > gambler.money) {
                    commentator.comment(name, "FOULED: made bet bigger than money he (she) has, he (she) misses match");
                    return;
                }
                if (bet < minimumBet) {
                    commentator.comment(name, "FOULED: made bet smaller than minimum one, he (she) misses match");
                    return;
                }
                gambler.money -= bet;
                commentator.comment(name, "makes bet: " + bet + ", money left: " + gambler.money);
                
                states.put(name, new PlayerState(new Hand(bet, shuffleMachine.next(2))));
            }
        });
        
        // dealer get his cards
        Card dealerOpenCard = shuffleMachine.next();
        Card dealerSecretCard = shuffleMachine.next();
        
        GameState gameState = new GameState(states, dealerOpenCard.copy());
        GameState gameStateCopy = gameState.copy();
        
        AtomicBoolean allBust = new AtomicBoolean(true);
        
        // players game
        states.forEach((name, state) -> {
            for (ListIterator<Hand> iterator = state.getHands().listIterator(); iterator.hasNext(); ) {
                Hand hand = iterator.next();
                Gambler player = players.get(name);
                String playerName = name + " hand " + (iterator.previousIndex() + 1);
                
                commentator.comment(playerName, "starts with " + hand);
                
                if (hand.hasBlackjack()) {
                    commentator.comment(playerName, "has BlackJack!");
                    continue;
                }
                
                HAND_PROCESSING:
                while (true) {
                    gameState.copyTo(gameStateCopy);
                    Action action = players.get(name).player.act(hand.copy(), gameStateCopy);
                    
                    switch (action) {
                        case DOUBLE:
                            if (player.money < hand.getBet()) {
                                commentator.comment(
                                        playerName, "FOULED: he (she) does not have enough money to double bet, bet is lost");
                                hand.setHasFouled(true);
                                break HAND_PROCESSING;
                            }
                            player.money -= hand.getBet();
                            hand.doubleBet();
                            // drops down
                        case HIT:
                            commentator.comment(playerName, action == Action.DOUBLE ? "doubles" : "hits");
                            Card newCard = shuffleMachine.next();
                            hand.takeCard(newCard);
                            commentator.comment(playerName, "got " + newCard + ", score: " + hand.getScore());
                            if (hand.isBust()) {
                                commentator.comment(playerName, "bust");
                                break HAND_PROCESSING;
                            }
                            if (hand.getScore() == 21) {
                                break HAND_PROCESSING;
                            }
                            
                            if (action == Action.DOUBLE) {
                                break HAND_PROCESSING;
                            } else {
                                break;
                            }
                        case STAND:
                            commentator.comment(playerName, "stands, final score " + hand.getScore());
                            break HAND_PROCESSING;
                        case SPLIT:
                            if (!hand.isSplittable()) {
                                commentator.comment(playerName, "FOULED: hand can not be split, bet is lost");
                                hand.setHasFouled(true);
                                break HAND_PROCESSING;
                            }
                            if (player.money < hand.getBet()) {
                                commentator.comment(
                                        playerName, "FOULED: he (she) does not have enough money to double bet, bet is lost");
                                hand.setHasFouled(true);
                                break HAND_PROCESSING;
                            }
                            
                            player.money -= hand.getBet();
                            
                            commentator.comment(playerName, "splits");
                            
                            Hand newHand = hand.split();
                            Card newCardToCurrentHand = shuffleMachine.next();
                            hand.takeCard(newCardToCurrentHand);
                            commentator.comment(playerName, "got " + newCardToCurrentHand + ", score: " + hand.getScore());
                            
                            Card newCardToNewHand = shuffleMachine.next();
                            newHand.takeCard(newCardToNewHand);
                            commentator.comment(name, "got " + newCardToNewHand + " to the split hand");
                            
                            iterator.add(newHand);
                            iterator.previous();
                    }
                }
                
                hand.setHasPlayed(true);
                allBust.set(allBust.get() & hand.isBust());
            }
        });
        
        // now it dealer's turn
        commentator.comment("All players gamed");
        Hand dealerHand = new Hand(0, new Card[]{dealerOpenCard, dealerSecretCard});
        if (!allBust.get()) {
            commentator.comment("Dealer's second card is " + dealerSecretCard + ", score: " + dealerHand.getScore());
            
            while (dealerHand.getScore() < 17) {
                Card card = shuffleMachine.next();
                dealerHand.takeCard(card);
                commentator.comment("Dealer", "got " + card + ", score: " + dealerHand.getScore());
            }
            
            if (dealerHand.hasBlackjack()) {
                commentator.comment("Dealer", "has BlackJack!");
            } else if (dealerHand.isBust()) {
                commentator.comment("Dealer", "bust");
            }
        }
        
        // finally, bets are processed
        states.forEach((name, state) -> {
            for (ListIterator<Hand> iterator = state.getHands().listIterator(); iterator.hasNext(); ) {
                Hand hand = iterator.next();
                Gambler player = players.get(name);
                String playerName = name + " hand " + (iterator.previousIndex() + 1);
                
                if (!hand.hasFouled() && !hand.isBust()) {
                    if (hand.hasBlackjack()) {
                        commentator.comment(playerName, "wins 3:2 " + (hand.getBet() * 1.5));
                        player.money += hand.getBet() + hand.getBet() * 1.5;
                        
                    } else if (dealerHand.isBust() || hand.getScore() > dealerHand.getScore()) {
                        commentator.comment(playerName, "wins 1:1 " + hand.getBet());
                        player.money += hand.getBet() * 2;
                        
                    } else if (hand.getScore() == dealerHand.getScore()) {
                        commentator.comment(playerName, "gets his bet back " + hand.getBet());
                        player.money += hand.getBet();
                    } else {
                        commentator.comment(playerName, "loses bet " + hand.getBet());
                    }
                } else {
                    commentator.comment(playerName, "loses bet " + hand.getBet());
                }
            }
        });
    }
    
    private class Gambler {
        Player player;
        final double startMoney;
        double money;
        
        public Gambler(Player player, double money) {
            this.player = player;
            this.startMoney = money;
            this.money = money;
        }
    }
}
