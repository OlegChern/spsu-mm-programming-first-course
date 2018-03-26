using System;
using System.Collections.Generic;
using System.Linq;

namespace Task3
{
    static class Program
    {
        const uint InitialMoney = 100;
        const uint MaxPlayers = 10;

        static void PressAnyKey()
        {
            Console.Write("Press any key to continue...");
            Console.ReadKey();
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
                    default:
                        throw new ArgumentOutOfRangeException();
                }
            }

            var deck = Card.ShuffledDecks(8);

            Console.WriteLine();

            Round(players, deck, 1, new List<AbstractPlayer>());

            Console.ReadKey();
        }

        static int CountTypes<T>(IEnumerable<AbstractPlayer> players) where T : AbstractPlayer
        {
            return players.OfType<T>().Count();
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
            switch (s[0])
            {
                case 'Y':
                case 'y':
                    return true;
                case 'N':
                case 'n':
                    return false;
                default:
                    Console.Write("Error. ");
                    return Confirm(message);
            }
        }

        static void Round(IList<AbstractPlayer> players, IList<Card> deck, int roundNumber, List<AbstractPlayer> lost)
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
                Console.WriteLine(hands[i].Owner.Name == "You" ? "Your turn!" : $"Turn of {hands[i].Owner.Name}.");
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
                        Console.WriteLine($"{hand.Owner.Name} {(hand.Owner.Name == "You" ? "have" : "has")} blackjack!");
                        Console.WriteLine($"{hand.Owner.Name} {(hand.Owner.Name == "You" ? "get" : "gets")} repaid 3:2!");
                        hand.Owner.GiveMoney((int)hand.InitialBet * 5 / 2);
                        Console.WriteLine();
                    }
                    else
                    {
                        Console.WriteLine($"{hand.Owner.Name} {(hand.Owner.Name == "You" ? "get" : "gets")} repaid 1:1!");
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
                        Console.WriteLine($"{hand.Owner.Name} {(hand.Owner.Name == "You" ? "have" : "has")} equal score with dealer. {hand.InitialBet}$ bet is returned.");
                        hand.Owner.GiveMoney((int)hand.InitialBet);
                        Console.WriteLine();
                    }
                    else if (score > dealer.Score())
                    {
                        Console.WriteLine($"{hand.Owner.Name} {(hand.Owner.Name == "You" ? "beat" : "beats")} the dealer!");
                        Console.WriteLine($"{hand.Owner.Name} {(hand.Owner.Name == "You" ? "get" : "gets")} repaid 1:1!");
                        hand.Owner.GiveMoney((int)hand.InitialBet * 2);
                        Console.WriteLine();
                    }
                    else
                    {
                        Console.WriteLine($"{hand.Owner.Name} lost.");
                        Console.WriteLine();
                    }
                }
            }

            PressAnyKey();
            Round(players, deck, roundNumber + 1, lost);
        }

        static void WriteList<T>(IReadOnlyList<T> list, string message = null)
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

            if (Card.GetScore(hand.Cards) <= 21)
            {
                return PlayerState.Playing;
            }

            Console.WriteLine("{0} {1} above 21... Bet removed.", hand.Owner.Name, hand.Owner.Name == "You" ? "are" : "is");
            Console.WriteLine();
            return PlayerState.Lost;
        }

        /// <summary>
        /// Let a player decide what to do
        /// </summary>
        /// <returns>
        /// Whether hand should stay in hands or not
        /// </returns>
        static bool PerformActions(IList<Hand> hands, IList<Card> deck, int index, Dealer dealer)
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
                default:
                    throw new ArgumentOutOfRangeException();
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
                    throw new ArgumentOutOfRangeException();
            }
        }

        static void GiveCard(IList<Hand> hands, IList<Card> deck, int index)
        {
            Console.WriteLine($"New card is {deck[0]}.");
            hands[index].Cards.Add(deck[0]);
            deck.RemoveAt(0);
            // Console.WriteLine($"New Score is {Card.GetScore(hands[index].Cards)}.");
        }

        static List<Hand> GetHands(IList<AbstractPlayer> players, IReadOnlyList<uint> bets, IList<Card> deck)
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

        static uint[] GetInitialBets(IList<AbstractPlayer> players)
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
