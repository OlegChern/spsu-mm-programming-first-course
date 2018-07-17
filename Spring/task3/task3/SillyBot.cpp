#pragma once
#include "stdafx.h"
#include "Player.cpp"

class SillyBot : public Player
{
public:
	SillyBot(int money = START_CASH) : Player(money) {}

	~SillyBot() {}

	int MakeDecision()
	{
		if (count <= 11 || (countOfTakenCards == 2 && check()))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	int PlaceBet()
	{
		cash -= MEDIUM_BET;
		return MEDIUM_BET;
	}
};