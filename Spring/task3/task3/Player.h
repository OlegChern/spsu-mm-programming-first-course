#pragma once
#include "stdafx.h"
#include "Member.h"

class Player : public Member
{
protected:
	int cash;
public:
	Player(int money = START_CASH);
	~Player();
	virtual int placeBet() = 0;
	virtual int makeDecision() = 0;
	void addToCash(int money);
	int getCash();
	bool check();
};