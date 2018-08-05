#pragma once
#include "stdafx.h"
#include "CleverBot.h"

CleverBot::~CleverBot()
{
}

int CleverBot::makeDecision()
{
	for (int i = 0; i < NUM_OF_VALUES; i++)
	{
		for (int j = 0; j < NUM_OF_SUITS; j++)
		{
			if (memberCards.count({ i, j }) != 0)
			{
				if (i <= NUM_OF_VALUES - 9)
				{
					cheatCount--;
				}
				else if (i > NUM_OF_VALUES - 6)
				{
					cheatCount++;
				}
			}
		}
	}
	if (cheatCount > 10 && (count <= 13 || check()))
	{
		return 1;
	}
	else if (count <= 11 || (countOfTakenCards == 2 && check()))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int CleverBot::placeBet()
{
	if (cheatCount >= 0)
	{
		cash -= MEDIUM_BET;
		return MEDIUM_BET;
	}
	else
	{
		cash -= LOW_BET;
		return LOW_BET;
	}
}
