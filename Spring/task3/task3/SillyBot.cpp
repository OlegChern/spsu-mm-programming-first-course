#pragma once
#include "stdafx.h"
#include "SillyBot.h"

SillyBot::~SillyBot()
{
}

int SillyBot::makeDecision()
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

int SillyBot::placeBet()
{
	cash -= MEDIUM_BET;
	return MEDIUM_BET;
}
