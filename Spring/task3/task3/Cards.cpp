#pragma once
#include "stdafx.h"
#define HIGH_BET 20
#define MEDIUM_BET 10
#define LOW_BET 4
#define START_CASH 400
#define COUNT_OF_PLAYERS 1 // don't touch
#define NUMBER_OF_DECKS 8
#define NUMBER_OF_ROUNDS 40
#define NUM_OF_SUITS 4  // don't touch
#define NUM_OF_VALUES 13

class CardDeck
{
	int countOfDecks;
	int condition[NUM_OF_VALUES][NUM_OF_SUITS];
public:
	CardDeck(int numberOfDecks)
	{
		countOfDecks = numberOfDecks;
		refill();
	}

	~CardDeck() {}

	pair <int, int> GetCard()
	{
		pair <int, int> card;
		int tmp1, tmp2;
		while (1)
		{
			tmp1 = rand() % NUM_OF_VALUES;
			tmp2 = rand() % NUM_OF_SUITS;
			if (condition[tmp1][tmp2] > 0)
			{
				card.first = tmp1;
				card.second = tmp2;
				condition[tmp1][tmp2]--;
				break;
			}
		}
		return card;
	}

	void refill()
	{
		for (int i = 0; i < NUM_OF_VALUES; i++)
		{
			for (int j = 0; j < NUM_OF_SUITS; j++)
			{
				condition[i][j] = countOfDecks;
			}
		}
	}
};