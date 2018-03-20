#pragma once
class Member : public Cards
{
protected:
    int count;
    int countOfTakenCards;
public:
    Member()
    {
        refill();
    }
    ~Member(){}
    int getCount()
    {
        return count;
    }
    void refill()
    {
        for (int i = 0; i < 13; i++)
        {
            for (int j; j < 4; j++)
            {
                condition[i][j] = 0;
            }
        }
        count = 0;
        countOfTakenCards = 0;
    }
    void TakeCard(CardDeck* deck)
    {
        pair <int, int> card = deck->GiveCard();
        condition[card.first][card.second] = 1;
        if (card.first < 8)
        {
            count += (card.first + 2);
            countOfTakenCards++;
        }
        else if (card.first != 13)
        {
            count += 10;
            countOfTakenCards++;
        }
        else
        {
            if (count + 11 > 21)
            {
                count++;
                countOfTakenCards++;
            }
            else
            {
                count += 11;
                countOfTakenCards++;
            }
        }
    }
};


class Player : public Member
{
protected:
    int cash;
public:
    Player(int money = START_CASH)
    {
        refill();
        cash = money;
    }
    ~Player(){}
    void changeCash(int money)
    {
        cash += money;
    }
    int showCash()
    {
        return cash;
    }
};



class SillyBot : public Player
{
public:
    SillyBot(int money = START_CASH) : Player(money){}
    ~SillyBot(){}
    int MakeDecision()
    {
        if (count <= 11 || (countOfTakenCards == 2 && (condition[13][0] > 0 || condition[13][1] > 0 || condition[13][2] > 0 || condition[13][3] > 0)))
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
        cash -= MEDIUM_BET;
        return MEDIUM_BET;
    }
};

class CleverBot : public Player
{
    int CheatCount;
public:
    CleverBot(int money) : Player(money)
    {
        CheatCount = 0;
    }
    ~CleverBot(){}
    int MakeDecision()
    {
        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (condition[i][j] != 0)
                {
                    if (i <= 4)
                    {
                        CheatCount--;
                    }
                    else if (i > 7)
                    {
                        CheatCount++;
                    }
                }
            }
        }
        if (CheatCount > 10 && (count <= 13 || (countOfTakenCards == 2 && (condition[13][0] > 0 || condition[13][1] > 0 || condition[13][2] > 0 || condition[13][3] > 0))))
        {
            return 1;
        }
        else if (count <= 11 || (countOfTakenCards == 2 && (condition[13][0] > 0 || condition[13][1] > 0 || condition[13][2] > 0 || condition[13][3] > 0)))
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
