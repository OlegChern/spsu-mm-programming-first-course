#pragma once
#include "stdafx.h"
#include "Member.h"

Member::Member()
{
	refill();
}

Member::~Member()
{
}

int Member::getCount()
{
	return count;
}

void Member::refill()
{
	memberCards.clear();
	count = 0;
}

void Member::takeCard(CardDeck * deck)
{
	pair <int, int> card = deck->getCard();
	memberCards.insert(card);
	if (card.first < NUM_OF_VALUES - 5)
	{
		count += (card.first + 2);
		countOfTakenCards++;
	}
	else if (card.first != NUM_OF_VALUES)
	{
		count += 10;
		countOfTakenCards++;
	}
	else
	{
		if (count + 11 > 21)
		{
			count++;
			countOfTakenCards++;
		}
		else
		{
			count += 11;
			countOfTakenCards++;
		}
	}
}
