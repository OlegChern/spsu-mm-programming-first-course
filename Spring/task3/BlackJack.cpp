#include <bits/stdc++.h>
#pragma once
using namespace std;
#include "cards.cpp"
#include "Players.cpp"

template <class T>
class BlackJack
{
    int bets[COUNT_OF_PLAYERS];
    Member Casino;
    CardDeck* deck;
public:
    BlackJack()
    {
        for (int i = 0; i < COUNT_OF_PLAYERS; i++)
        {
            bets[i] = 0;
        }
        deck = new CardDeck(NUMBER_OF_DECKS);
    }
    ~BlackJack(){}
    void Round(T* Bot)
    {
        int sol_1 = 1;
        bets[0] = Bot->PlaceBet();
        for (int i = 0; i < 2; i++)
        {
            Bot->TakeCard(deck);
            Casino.TakeCard(deck);
        }
        if (Bot->getCount() == 21 && Casino.getCount() != 21)
        {
            Bot->changeCash(bets[0] / 2 * 5);
        }
        else if ((Bot->getCount() == 21) && (Casino.getCount() == 21))
        {
            Bot->changeCash(bets[0] * 2);
        }
        else
        {
            while (sol_1 != 0 && Bot->getCount() < 21)
            {
                sol_1 = Bot->MakeDecision();
                if (sol_1 == 1)
                {
                    Bot->TakeCard(deck);
                }
            }
            if (Bot->getCount() <= 21)
            {
                while (Casino.getCount() < 17)
                {
                    Casino.TakeCard(deck);
                }
                if (Casino.getCount() > 21)
                {
                    Bot->changeCash(bets[0] * 2);
                }
                else
                {
                    if (Bot->getCount() > Casino.getCount())
                    {
                        Bot->changeCash(bets[0] * 2);
                    }
                }
            }
        }
    }
    void Game(T* Bot, int numOfRounds)
    {
        for (int i = 0; i < numOfRounds; i++)
        {
            Round(Bot);
            Bot->refill();
            Casino.refill();
        }
    }
};
