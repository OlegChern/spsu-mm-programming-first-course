#include "stdafx.h"
#pragma once
#include "BlackJack.h"

template<class T>
BlackJack<T>::BlackJack()
{
	bet = 0;
	deck = new CardDeck(NUMBER_OF_DECKS);
}

template<class T>
BlackJack<T>::~BlackJack()
{
}

template<class T>
void BlackJack<T>::round(T * bot)
{
	int botTakeCard = 1;
	bet = bot->placeBet();
	for (int i = 0; i < 2; i++)
	{
		bot->takeCard(deck);
		casino.takeCard(deck);
	}
	if (bot->getCount() == 21 && casino.getCount() != 21)
	{
		bot->addToCash(payBlackJack(bet));
	}
	else if ((bot->getCount() == 21) && (casino.getCount() == 21))
	{
		bot->addToCash(payCountWin(bet));
	}
	else
	{
		while (botTakeCard != 0 && bot->getCount() < 21)
		{
			botTakeCard = bot->makeDecision();
			if (botTakeCard == 1)
			{
				bot->takeCard(deck);
			}
		}
		if (bot->getCount() <= 21)
		{
			while (casino.getCount() < 17)
			{
				casino.takeCard(deck);
			}
			if (casino.getCount() > 21)
			{
				bot->addToCash(payCountWin(bet));
			}
			else
			{
				if (bot->getCount() > casino.getCount())
				{
					bot->addToCash(payCountWin(bet));
				}
			}
		}
	}
}

template<class T>
void BlackJack<T>::game(T * bot, int numOfRounds)
{
	for (int i = 0; i < numOfRounds; i++)
	{
		round(bot);
		bot->refill();
		casino.refill();
	}
}

template<class T>
int BlackJack<T>::payBlackJack(int bet)
{
	return bet / 2 * 5;
}

template<class T>
int BlackJack<T>::payCountWin(int bet)
{
	return bet * 2;
}

