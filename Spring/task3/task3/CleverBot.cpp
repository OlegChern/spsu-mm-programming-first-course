#pragma once
#include "stdafx.h"
#include "Player.cpp"

class CleverBot : public Player
{
	int CheatCount; // special field for counting values of cards for special strategy
public:
	CleverBot(int money) : Player(money)
	{
		CheatCount = 0;
	}

	~CleverBot() {}

	int MakeDecision()
	{
		for (int i = 0; i < NUM_OF_VALUES; i++)
		{
			for (int j = 0; j < NUM_OF_SUITS; j++)
			{
				if (MemberCards.count({ i, j }) != 0)
				{
					if (i <= NUM_OF_VALUES - 9)
					{
						CheatCount--;
					}
					else if (i > NUM_OF_VALUES - 6)
					{
						CheatCount++;
					}
				}
			}
		}
		if (CheatCount > 10 && (count <= 13 || check()))
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

	int PlaceBet()
	{
		if (CheatCount >= 0)
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

};