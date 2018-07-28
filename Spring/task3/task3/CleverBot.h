#pragma once
#include "stdafx.h"
#include "Player.h"

class CleverBot : public Player
{
	int cheatCount;
public:
	CleverBot(int money) : Player(money)
	{
		cheatCount = 0;
	}
	~CleverBot();
	int makeDecision();
	int placeBet();
};