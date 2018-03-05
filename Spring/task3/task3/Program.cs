using System;
using System.Collections.Generic;
using System.Linq;

namespace task3
{
    class Program
    {
        public const uint InitialMoney = 100;
        public const uint MaxPlayers = 10;

        public static void PressAnyKey()
        {
            Console.Write("Press any key to continue...");
            var key = Console.ReadKey();
            int currentLineCursor = Console.CursorTop;
            Console.SetCursorPosition(0, Console.CursorTop);
            Console.Write(new string(' ', Console.WindowWidth));
            Console.SetCursorPosition(0, currentLineCursor);

        }

        static void Main()
        {
            Console.WriteLine("==-== BlackJack ==-==");
            Console.WriteLine();
            uint playerCount = GetPlayerCount();
            bool humanParticipates = Confirm("Will you particiate in game? [y/n]: ");

            var players = new List<AbstractPlayer>();

            uint nonHumanplayers;
            if (humanParticipates)
            {
                players.Add(new HumanPlayer(InitialMoney));
                nonHumanplayers = playerCount - 1;
            }

            else
            {
                nonHumanplayers = playerCount;
            }

            var random = new Random();
            for (int i = 0; i < nonHumanplayers; i++)
            {
                // Can possibly support more bots
                switch (random.Next(1, 3))
                {
                    case 1:
                        int number = CountTypes<BotPlayer1>(players);
                        players.Add(new BotPlayer1(InitialMoney, $"Bot 1{(number == 0 ? "" : $" #{number + 1}")}"));
                        break;
                    case 2:
                        number = CountTypes<BotPlayer2>(players);
                        players.Add(new BotPlayer2(InitialMoney, $"Bot 2{(number == 0 ? "" : $" #{number + 1}")}"));
                        break;
                }
            }

            var deck = Card.ShuffledDecks(8);

            Console.WriteLine();

            Round(players, deck, 1, new List<AbstractPlayer>());

            Console.ReadKey();
        }

        static int CountTypes<T>(List<AbstractPlayer> players) where T : AbstractPlayer
        {
            int result = 0;
            foreach (var player in players)
            {
                if (player is T)
                {
                    result++;
                }
            }
            return result;
        }

        static uint GetPlayerCount()
        {
            Console.Write("Please, enter number of players: ");
            if (uint.TryParse(Console.ReadLine(), out uint result) && result > 0 && result <= MaxPlayers)
            {
                return result;
            }
            Console.Write("Error. ");
            return GetPlayerCount();
        }

        static bool Confirm(string message)
        {
            Console.Write(message);
            string s = Console.ReadLine();
            if (s[0] == 'Y' || s[0] == 'y')
            {
                return true;
            }
            else if (s[0] == 'N' || s[0] == 'n')
            {
                return false;
            }
            else
            {
                Console.Write("Error. ");
                return Confirm(message);
            }
        }

        static void Round(List<AbstractPlayer> players, List<Card> deck, int roundNumber, List<AbstractPlayer> lost)
        {
            int i = 0;
            while (i < players.Count)
            {
                if (players[i].Money == 0)
                {
                    lost.Add(players[i]);
                    players.RemoveAt(i);
                }
                else
                {
                    i++;
                }
            }
            if (!players.Any())
            {
                return;
            }
            // Following formula ensures that players
            // can pick as many cards from the deck as they want
            if (deck.Count < (players.Count + 1) * 11)
            {
                deck = Card.ShuffledDecks(8);
            }

            Console.WriteLine($"==-== Round {roundNumber} ==-==");
            if (lost.Any())
            {
                WriteList(lost, "(");
                Console.WriteLine(" have lost all their money)");
            }
            Console.WriteLine();

            var bets = GetInitialBets(players);

            Console.WriteLine();

            var hands = GetHands(players, bets, deck);
            var dealer = new Dealer(deck);
            Console.WriteLine($"Dealer's card is {dealer.FirstCard} (score: {dealer.FirstCard.Score()})");
            Console.WriteLine();

            i = 0;
            while (i < hands.Count)
            {
                if (hands[i].Owner.Name == "You")
                {
                    Console.WriteLine("Your turn!");
                }
                else
                {
                    Console.WriteLine($"Turn of {hands[i].Owner.Name}.");
                }
                if (!PerformActions(hands, deck, i, dealer))
                {
                    hands.RemoveAt(i);
                }
                else
                {
                    i++;
                }
                PressAnyKey();
            }

            Console.WriteLine();
            Console.WriteLine("Dealer collects cards:");

            dealer.TakeEnoughCards(deck);

            dealer.WriteCards();
            Console.WriteLine($" ({dealer.Score()})");
            Console.WriteLine();

            if (dealer.Score() > 21)
            {
                Console.WriteLine("Dealer lost!");
                foreach (var hand in hands)
                {
                    if (Card.GetScore(hand.Cards) == 21 && hand.Cards.Count == 2)
                    {
                        Console.WriteLine("{0} {1} blackjack!", hand.Owner.Name, hand.Owner.Name == "You" ? "have" : "has");
                        Console.WriteLine("{0} {1} repaid 3:2!", hand.Owner.Name, hand.Owner.Name == "You" ? "get" : "gets");
                        hand.Owner.GiveMoney((int)hand.InitialBet * 5 / 2);
                        Console.WriteLine();
                    }
                    else
                    {
                        Console.WriteLine("{0} {1} repaid 1:1!", hand.Owner.Name, hand.Owner.Name == "You" ? "get" : "gets");
                        hand.Owner.GiveMoney((int)hand.InitialBet * 2);
                        Console.WriteLine();
                    }
                }
            }
            else
            {
                foreach (var hand in hands)
                {

                    uint score = Card.GetScore(hand.Cards);

                    if (score == dealer.Score())
                    {
                        Console.WriteLine("{0} {1} equal score with dealer. {2}$ bet is returned.",
                            hand.Owner.Name, hand.Owner.Name == "You" ? "have" : "has",
                            hand.InitialBet);
                        hand.Owner.GiveMoney((int)hand.InitialBet);
                        Console.WriteLine();
                    }
                    else if (score > dealer.Score())
                    {
                        Console.WriteLine("{0} {1} the dealer!", hand.Owner.Name, hand.Owner.Name == "You" ? "beat" : "beats");
                        Console.WriteLine("{0} {1} repaid 1:1!", hand.Owner.Name, hand.Owner.Name == "You" ? "get" : "gets");
                        hand.Owner.GiveMoney((int)hand.InitialBet * 2);
                        Console.WriteLine();
                    }
                    else
                    {
                        Console.WriteLine("{0} lost.", hand.Owner.Name);
                        Console.WriteLine();
                    }
                }
            }

            PressAnyKey();
            Round(players, deck, roundNumber + 1, lost);
        }

        public static void WriteList<T>(List<T> list, string message = null)
        {
            if (message != null)
            {
                Console.Write(message);
            }
            for (int i = 0; i < list.Count; i++)
            {
                Console.Write((list[i]));
                if (i == list.Count - 2)
                {
                    Console.Write(" and ");
                }
                else if (i != list.Count - 1)
                {
                    Console.Write(", ");
                }
            }
        }

        /// <summary>
        /// Checks that hand is valid and should stay in game
        /// </summary>
        /// <returns>
        /// whether player can stay in game or not
        /// </returns>
        static PlayerState CheckScore(Hand hand, Dealer dealer)
        {
            if (Card.GetScore(hand.Cards) == 21 && hand.Cards.Count == 2)
            {
                Console.WriteLine("{0} {1} blackjack!", hand.Owner.Name, hand.Owner.Name == "You" ? "have" : "has");
                if (dealer.FirstCard.Score() != 10 || dealer.FirstCard.Score() == 11)
                {
                    Console.WriteLine($"Dealer has {dealer.FirstCard.Score()} though");
                    Console.WriteLine();
                    return PlayerState.BlackJack;
                }
                Console.WriteLine("{0} {1} repaid 3:2!", hand.Owner.Name, hand.Owner.Name == "You" ? "get" : "gets");
                hand.Owner.GiveMoney((int)hand.InitialBet * 5 / 2);
                Console.WriteLine();
                return PlayerState.Won;
            }
            if (Card.GetScore(hand.Cards) > 21)
            {
                Console.WriteLine("{0} {1} above 21... Bet removed.", hand.Owner.Name, hand.Owner.Name == "You" ? "are" : "is");
                Console.WriteLine();
                return PlayerState.Lost;
            }
            return PlayerState.Playing;
        }

        /// <summary>
        /// Let a player decide what to do
        /// </summary>
        /// <returns>
        /// Whether hand should stay in hands or not
        /// </returns>
        static bool PerformActions(List<Hand> hands, List<Card> deck, int index, Dealer dealer)
        {
            AbstractPlayer.WriteCards(hands[index].Cards, "Current hand: ");
            Console.WriteLine($" (score: {Card.GetScore(hands[index].Cards)})");
            switch (CheckScore(hands[index], dealer))
            {
                case PlayerState.Playing:
                    break;
                case PlayerState.Won:
                    return false;
                case PlayerState.Lost:
                    return false;
                case PlayerState.BlackJack:
                    return true;
            }

            var action = hands[index].Owner.ChooseAction(dealer, hands[index]);
            Console.WriteLine();
            switch (action)
            {
                case Action.Stand:
                    return true;
                case Action.Hit:
                    GiveCard(hands, deck, index);
                    Console.WriteLine();
                    return PerformActions(hands, deck, index, dealer);
                case Action.Double:
                    hands[index].Owner.GiveMoney((int)-hands[index].InitialBet);
                    Console.WriteLine();
                    GiveCard(hands, deck, index);
                    Console.WriteLine();
                    var state = CheckScore(hands[index], dealer);
                    return state == PlayerState.Playing;
                case Action.Split:
                    hands[index].Owner.GiveMoney((int)-hands[index].InitialBet);
                    Console.WriteLine();
                    Console.WriteLine($"Card added to first hand: {deck[0]}");
                    Console.WriteLine($"Card added to second hand: {deck[1]}");
                    var half = new Hand(
                        hands[index].Owner,
                        new List<Card>
                        {
                            hands[index].Cards[0],
                            deck[1]
                        },
                        hands[index].InitialBet
                    );
                    hands.Insert(index + 1, half);
                    hands[index].Cards.RemoveAt(0);
                    hands[index].Cards.Add(deck[0]);
                    deck.RemoveAt(0);
                    deck.RemoveAt(0);
                    return PerformActions(hands, deck, index, dealer);
                case Action.Surrender:
                    hands[index].Owner.GiveMoney((int)hands[index].InitialBet / 2);
                    Console.WriteLine();
                    return false;
                default:
                    throw new NotImplementedException();
            }
        }

        static void GiveCard(List<Hand> hands, List<Card> deck, int index)
        {
            Console.WriteLine($"New card is {deck[0]}.");
            hands[index].Cards.Add(deck[0]);
            deck.RemoveAt(0);
            // Console.WriteLine($"New Score is {Card.GetScore(hands[index].Cards)}.");
        }

        static List<Hand> GetHands(List<AbstractPlayer> players, uint[] bets, List<Card> deck)
        {
            var hands = new List<Hand>();
            for (int i = 0; i < players.Count; i++)
            {
                hands.Add(new Hand(
                    players[i],
                    new List<Card>
                    {
                        deck[0],
                        deck[1]
                    },
                    bets[i]
                ));
                Console.WriteLine($"{players[i].Name} got {deck[0]} and {deck[1]} (score: {Card.GetScore(hands[i].Cards)})");
                deck.RemoveAt(0);
                deck.RemoveAt(0);
            }
            return hands;
        }

        static uint[] GetInitialBets(List<AbstractPlayer> players)
        {
            uint[] bets = new uint[players.Count];
            for (int i = 0; i < players.Count; i++)
            {
                bets[i] = players[i].MakeInitialBet();
            }
            return bets;
        }
    }
}
