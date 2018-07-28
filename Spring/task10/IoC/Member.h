#pragma once
#include "stdafx.h"
#include "Cards.h"

class Member
{
protected:
	int count;
	int countOfTakenCards;
	set <pair<int, int> > memberCards;
public:
	Member();
	~Member();
	int getCount();
	void refill();
	void takeCard(CardDeck* deck);
};