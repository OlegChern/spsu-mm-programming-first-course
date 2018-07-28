#pragma once
#include "stdafx.h"
#include "Cards.h"

CardDeck::CardDeck(int numberOfDecks)
{
	countOfDecks = numberOfDecks;
	refill();
}

CardDeck::~CardDeck()
{
}

pair<int, int> CardDeck::getCard()
{
	pair <int, int> card;
	int randValue, randSuit;
	while (1)
	{
		randValue = rand() % NUM_OF_VALUES;
		randSuit = rand() % NUM_OF_SUITS;
		if (condition[randValue][randSuit] > 0)
		{
			card.first = randValue;
			card.second = randSuit;
			condition[randValue][randSuit]--;
			break;
		}
	}
	return card;
}

void CardDeck::refill()
{
	for (int i = 0; i < NUM_OF_VALUES; i++)
	{
		for (int j = 0; j < NUM_OF_SUITS; j++)
		{
			condition[i][j] = countOfDecks;
		}
	}
}
