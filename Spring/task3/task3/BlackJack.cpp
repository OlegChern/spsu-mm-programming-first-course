#pragma once
#include "stdafx.h"
#include "Cards.cpp"
#include "Player.cpp"
#include "SillyBot.cpp"
#include "CleverBot.cpp"

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

	~BlackJack() {}

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
			Bot->addToCash(PayBlackJack(bets[0]));
		}
		else if ((Bot->getCount() == 21) && (Casino.getCount() == 21))
		{
			Bot->addToCash(Pay21And21(bets[0]));
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
					Bot->addToCash(PayCasinoTooMuch(bets[0]));
				}
				else
				{
					if (Bot->getCount() > Casino.getCount())
					{
						Bot->addToCash(PayCountWin(bets[0]));
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

	static int PayBlackJack(int bet)
	{
		return bet / 2 * 5;
	}

	static int Pay21And21(int bet)
	{
		return bet * 2;
	}

	static int PayCasinoTooMuch(int bet)
	{
		return bet * 2;
	}
	static int PayCountWin(int bet)
	{
		return bet * 2;
	}
};