#pragma once
#include "stdafx.h"
#include "Player.h"

class CleverBot : public Player
{
	int cheatCount;
public:
	string name;
	CleverBot()
	{
	}
	CleverBot(int money) : Player(money)
	{
		cheatCount = 0;
		name = "Bot";
	}
	~CleverBot();
	int makeDecision();
	int placeBet();
};