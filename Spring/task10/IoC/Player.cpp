#pragma once
#include "stdafx.h"
#include "Player.h"

Player::Player(int money)
{
	refill();
	cash = money;
}

Player::~Player()
{
}

void Player::addToCash(int money)
{
	cash += money;
}

int Player::getCash()
{
	return cash;
}

bool Player::check()
{
	for (int i = 0; i < 4; i++)
		if (memberCards.count({ NUM_OF_VALUES, i }) != 0)
			return 1;
	return 0;
}
