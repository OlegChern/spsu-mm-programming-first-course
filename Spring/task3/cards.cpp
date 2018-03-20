#pragma once

class Cards
{
protected:
    int condition[13][4];
};

class CardDeck : public Cards
{
    int countOfDecks;
public:
    CardDeck(int numberOfDecks)
    {
        countOfDecks = numberOfDecks;
        refill();
    }
    ~CardDeck(){}
    
    pair <int, int> GiveCard()
    {
        pair <int, int> card;
        int tmp1, tmp2;
        while (1)
        {
            tmp1 = rand() % 13;
            tmp2 = rand() % 4;
            if (condition[tmp1][tmp2] > 0)
            {
                card.first = tmp1;
                card.second = tmp2;
                break;
            }
        }
        return card;
    }
    
    void refill()
    {
        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                condition[i][j] = countOfDecks;
            }
        }
    }
    
};
