#pragma once
#include "stdafx.h"
#include "Cards.cpp"

class Member
{
protected:
	int count;
	int countOfTakenCards;
	set <pair<int, int> > MemberCards;
public:
	Member()
	{
		refill();
	}

	~Member() {}

	int getCount()
	{
		return count;
	}

	void refill()
	{
		MemberCards.clear();
		count = 0;
	}

	void TakeCard(CardDeck* deck)
	{
		pair <int, int> card = deck->GetCard();
		MemberCards.insert(card);
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
};
