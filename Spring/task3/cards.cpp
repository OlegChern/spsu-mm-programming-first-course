#pragma once
class Cards
{
protected:
    enum suit {hearts, tambourine, peak, cross}; // will be used in next versions
    enum value {two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace}; //will be used in next versions
    int condition[NUM_OF_VALUES][NUM_OF_SUITS];
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
    pair <int, int> GetCard()
    {
        pair <int, int> card;
        int tmp1, tmp2;
        while (1)
        {
            tmp1 = rand() % NUM_OF_VALUES;
            tmp2 = rand() % NUM_OF_SUITS;
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
        for (int i = 0; i < NUM_OF_VALUES; i++)
        {
            for (int j = 0; j < NUM_OF_SUITS; j++)
            {
                condition[i][j] = countOfDecks;
            }
        }
    }
};
