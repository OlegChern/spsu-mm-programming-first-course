package com.company;

import java.util.Random;

import static com.company.Game.*;

public class SillyBot extends Player {

    public SillyBot(int cash) {
        this.cash = cash;
    }

    public int[] makeBet() {
        int[] bet = new int[3];
        Random random = new Random();
        bet[0] = BET_ON_NUMBER;
        bet[1] = random.nextInt(37);
        bet[2] = SILLY_BOT_BET;
        return bet;
    }
}
