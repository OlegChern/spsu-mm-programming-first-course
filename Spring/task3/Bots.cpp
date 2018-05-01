#pragma once

class SillyBot : public Player
{
public:
    SillyBot(int money = START_CASH) : Player(money){}
    ~SillyBot(){}
    int MakeDecision()
    {
        if (count <= 11 || (countOfTakenCards == 2 && (condition[NUM_OF_VALUES][0] > 0 || condition[NUM_OF_VALUES][1] > 0 || condition[NUM_OF_VALUES][2] > 0 || condition[NUM_OF_VALUES][3] > 0)))
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
    int CheatCount; // special field for counting values of cards for special strategy
public:
    CleverBot(int money) : Player(money)
    {
        CheatCount = 0;
    }
    ~CleverBot(){}
    int MakeDecision()
    {
        for (int i = 0; i < NUM_OF_VALUES; i++)
        {
            for (int j = 0; j < NUM_OF_SUITS; j++)
            {
                if (condition[i][j] != 0)
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
        if (CheatCount > 10 && (count <= 13 || (countOfTakenCards == 2 && (condition[NUM_OF_VALUES][0] > 0 || condition[NUM_OF_VALUES][1] > 0 || condition[NUM_OF_VALUES][2] > 0 || condition[NUM_OF_VALUES][3] > 0))))
        {
            return 1;
        }
        else if (count <= 11 || (countOfTakenCards == 2 && (condition[NUM_OF_VALUES][0] > 0 || condition[NUM_OF_VALUES][1] > 0 || condition[NUM_OF_VALUES][2] > 0 || condition[NUM_OF_VALUES][3] > 0)))
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
