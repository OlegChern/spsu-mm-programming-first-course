#include "stdafx.h"
#pragma once
#include "Cards.h"
#include "Player.h"
#include "SillyBot.h"
#include "CleverBot.h"

template <class T>
class BlackJack
{
private:
	int bet;
	Member casino;
	CardDeck* deck;
public:
	BlackJack();
	~BlackJack();
	void round(T* bot);
	void game(T* bot, int numOfRounds);
	static int payBlackJack(int bet);
	static int payCountWin(int bet);
};