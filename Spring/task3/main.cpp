#define HIGH_BET 20
#define MEDIUM_BET 10
#define LOW_BET 4
#define START_CASH 400
#define COUNT_OF_PLAYERS 1 // don't touch
#define NUMBER_OF_DECKS 8
#define NUMBER_OF_ROUNDS 40
#define NUM_OF_SUITS 4  // don't touch
#define NUM_OF_VALUES 13
#include "BlackJack.cpp"
using namespace std;

main()
{
    srand(time(NULL));
    FILE* out = fopen("out.txt", "w");
    cout << "----------------RULES---------------\n\n1) Blackjack is payed 3:2\n2) Equal points mean that casino wins if player doesn't have 21\n3) In all other ways player wins in 1:1";
    cout <<"\nStatistics shows that idiots are lucky!! You can find it in extra file. If you want to try yourself you should change name of class in main.cpp in two places\nPossible classes:\n1) SillyBot\n2) CleverBot\n";
    for (int i = 0; i < 100; i++)
    {
        SillyBot Bot(START_CASH);
        BlackJack <SillyBot> game;
        game.Game(&Bot, NUMBER_OF_ROUNDS);
        fprintf(out, "%d\n", Bot.getCash());
    }
    return 0;
}
