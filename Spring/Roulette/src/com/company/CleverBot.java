package com.company;

import static com.company.Game.BET_ON_COLOUR;
import static com.company.Game.CLEVER_BOT_BET;
import static com.company.Game.RED_BET;

public class CleverBot extends Player {
    private int oldCash;
    private int count;

    public CleverBot(int cash) {
        this.cash = cash;
        oldCash = cash;
        count = 1;
    }

    public int[] makeBet() {
        int[] bet = new int[3];
        bet[0] = BET_ON_COLOUR;
        bet[1] = RED_BET;
        if (oldCash > cash) {
            count *= 2;
        } else {
            count = 1;
        }
        bet[2] = CLEVER_BOT_BET * count;
        oldCash = cash;
        return bet;
    }
}
