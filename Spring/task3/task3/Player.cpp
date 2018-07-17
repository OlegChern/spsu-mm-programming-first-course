#pragma once
#include "stdafx.h"
#include "Member.cpp"

class Player : public Member
{
protected:
	int cash;
public:
	Player(int money = START_CASH)
	{
		refill();
		cash = money;
	}

	~Player() {}

	void addToCash(int money)
	{
		cash += money;
	}

	int getCash()
	{
		return cash;
	}

	bool check()
	{
		for (int i = 0; i < 4; i++)
			if (MemberCards.count({ NUM_OF_VALUES, i }) != 0)
				return 1;
		return 0;
	}
};