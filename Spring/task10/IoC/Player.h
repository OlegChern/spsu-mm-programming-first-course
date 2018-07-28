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
	void addToCash(int money);
	int getCash();
	bool check();
};