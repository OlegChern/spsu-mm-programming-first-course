using System;
using System.Collections.Generic;

namespace Task3
{
    public enum Suit
    {
        Hearts,
        Diamonds,
        Clubs,
        Spades
    }

    public enum Value
    {
        Two = 2,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King,
        Ace
    }

    public struct Card
    {
        public Suit suit;
        public Value value;

        public override string ToString()
        {
            return $"{value} of {suit}";
        }

        public uint Score()
        {
            if (value == Value.Ace)
            {
                return 11;
            }
            if (value <= Value.Ten)
            {
                return (uint)value;
            }
            return 10;
        }

        public static uint GetScore(List<Card> list)
        {
            uint result = 0;
            uint aces = 0;
            foreach (var card in list)
            {
                if (card.value == Value.Ace)
                {
                    aces++;
                }
                else
                {
                    result += card.Score();
                }
            }

            if (result + aces > 21)
            {
                return result + aces;
            }

            // Now, total aces can give
            //     aces + M * 10
            // where M in [0..aces]
            // Hence, score is
            //     result + aces + M * 10
            // We want this value to be <= 21
            //     result + aces + M * 10 <= 21
            //     M <= (21 - result - aces) / 10
            
            uint m = (21 - result - aces) / 10;

            if (m > aces)
            {
                m = aces;
            }

#if DEBUG
            if (m < 0 || result + aces + m * 10 > 21)
            {
                throw new Exception("Error: unexpected code behaviour");
            }
#endif
            return result + aces + m * 10;
        }

        public static List<Card> ShuffledDecks(uint decks)
        {
            var list = CreateDecks(decks);
            var random = new Random();
            for (int i = list.Count - 1; i > 0; --i)
            {
                int j = random.Next(i + 1);
                var tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
            return list;
        }

        private static List<Card> CreateDecks(uint decks)
        {
            var list = new List<Card>();
            foreach (Suit suit in Enum.GetValues(typeof(Suit)))
            {
                foreach (Value value in Enum.GetValues(typeof(Value)))
                {
                    var card = new Card
                    {
                        suit = suit,
                        value = value
                    };
                    for (int i = 0; i < decks; i++)
                    {
                        list.Add(card);
                    }
                }
            }
            return list;
        }

        public static bool IsPair(List<Card> hand)
        {
            return hand.Count == 2 && hand[0].Score() == hand[1].Score();
        }
    }
}
