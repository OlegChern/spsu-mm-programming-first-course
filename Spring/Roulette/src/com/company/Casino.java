package com.company;

import static com.company.Game.*;

public class Casino {
    private Player[] players;
    private int[][] bets;
    private int spinResult;

    public void setPlayers(Player[] players) {
        this.players = players;
    }

    public void setBets() {
        bets = new int[players.length][3];
        for (int i = 0; i < players.length; i++) {
            int[] bet = players[i].makeBet();
            for (int j = 0; j < 3; j++) {
                bets[i][j] = bet[j];
            }
            players[i].payCash(bet[2]);
        }
    }

    public void setSpinResult(int spinResult) {
        this.spinResult = spinResult;
    }

    public void payBets() {
        if (spinResult != 0) {
            for (int i = 0; i < bets.length; i++) {
                switch (bets[i][0]) {
                    case 1:
                        if ((bets[i][1] == RED_BET && spinResult % 2 != 0) || (bets[i][1] == BLACK_BET && spinResult % 2 == 0)) {
                            pay(players[i], bets[i][2] * COLOUR_WIN_COEF);
                        }
                        break;
                    case 2:
                        if ((bets[i][1] == FIRST_DOZEN_BET && spinResult <= 12) || (bets[i][1] == SECOND_DOZEN_BET && spinResult > 12 && spinResult <= 24) || (bets[i][1] == THIRD_DOZEN_BET && spinResult > 24)) {
                            pay(players[i], bets[i][2] * DOZEN_WIN_COEF);
                        }
                        break;
                    case 3:
                        if ((bets[i][1] == LITTLE_NUMBER_BET && spinResult <= 18) ||(bets[i][1] == BIG_NUMBER_BET && spinResult > 18)) {
                            pay(players[i], bets[i][2] * SIZE_WIN_COEF);
                        }
                        break;
                    case 4:
                        if (bets[i][1] == spinResult) {
                            pay(players[i], bets[i][2] * ONE_NUMBER_WIN_COEF);
                        }
                        break;
                }
            }
        }
    }

    public void pay(Player player, int sum) {
        player.addCash(sum);
    }
}
