#pragma once
#include "stdafx.h"
#include "BlackJack.cpp"

int main()
{
	srand(time(NULL));
	cout << "----------------RULES---------------\n\n1) Blackjack is payed 3:2\n2) Equal points mean that casino wins if player doesn't have 21\n3) In all other ways player wins in 1:1";
	cout << "\nStatistics shows that SillyBots are lucky!! \nPossible classes:\n1) SillyBot\n2) CleverBot\n";
	for (int i = 0; i < 50; i++)
	{
		CleverBot bot(START_CASH);
		BlackJack <Player> gameStart;
		gameStart.game(&bot, NUMBER_OF_ROUNDS);
		cout << bot.getCash() << "\n";
	}
	system("pause");
	return 0;
}