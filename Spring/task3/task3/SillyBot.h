#pragma once
#include "stdafx.h"
#include "Player.h"

class SillyBot : public Player
{
public:
	SillyBot(int money = START_CASH) : Player(money) {}
	~SillyBot();
	int makeDecision();
	int placeBet();
};