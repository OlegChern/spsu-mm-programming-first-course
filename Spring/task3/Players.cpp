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
        for (int i = 0; i < NUM_OF_VALUES; i++)
        {
            for (int j; j < NUM_OF_SUITS; j++)
            {
                condition[i][j] = 0;
            }
        }
        count = 0;
    }
    void TakeCard(CardDeck* deck)
    {
        pair <int, int> card = deck->GetCard();
        condition[card.first][card.second] = 1;
        if (card.first < NUM_OF_VALUES - 5)
        {
            count += (card.first + 2);
            countOfTakenCards++;
        }
        else if (card.first != NUM_OF_VALUES)
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
    void addToCash(int money)
    {
        cash += money;
    }
    int getCash()
    {
        return cash;
    }
};
