#pragma once
#include "stdafx.h"
class CardDeck
{
	int countOfDecks;
	int condition[NUM_OF_VALUES][NUM_OF_SUITS];
public:
	CardDeck(int numberOfDecks);
	~CardDeck();
	pair <int, int> getCard();
	void refill();
};