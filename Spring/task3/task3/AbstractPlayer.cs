using System;
using System.Collections.Generic;

namespace task3
{
    abstract class AbstractPlayer
    {
        // I'll just trust nothing goes wrong with that public setter...
        public uint Money { get; set; }
        public string Name { get; }

        public abstract uint MakeInitialBet();

        public abstract Action ChooseAction(Dealer dealer, Hand hand);

        public bool CanPerform(Action action, Hand hand)
        {
            switch (action)
            {
                case Action.Stand:
                case Action.Hit:
                    return true;
                case Action.Double:
                    return hand.InitialBet <= Money;
                case Action.Split:
                    return Card.IsPair(hand.Cards) && hand.InitialBet <= Money;
                case Action.Surrender:
                    return hand.Cards.Count == 2;
                default:
                    throw new NotImplementedException();
            }
        }

        public List<Action> GetPossibleActions(Hand hand)
        {
            var list = new List<Action>();
            foreach (Action action in Enum.GetValues(typeof(Action)))
            {
                if (CanPerform(action, hand))
                {
                    list.Add(action);
                }
            }
            return list;
        }

        public static void WriteCards(List<Card> hand, string message = null)
        {
            if (message != null)
            {
                Console.Write(message);
            }
            for (int i = 0; i < hand.Count; i++)
            {
                Console.Write(hand[i]);
                if (i == hand.Count - 2)
                {
                    Console.Write(" and ");
                }
                else if (i != hand.Count - 1)
                {
                    Console.Write(", ");
                }
            }
        }

        /// <summary>
        /// Different from Money_set due to writing into console
        /// </summary>
        /// <param name="added">can be negative</param>
        public void GiveMoney(int added)
        {
            long newSum = Money + added;
            if (newSum < 0 || newSum > uint.MaxValue)
            {
                throw new ArgumentException($"{Name} can't afford to pay that!");
            }
            Money = (uint)(newSum);
            Console.WriteLine("{0} now {1} {2}$", Name, Name == "You" ? "have" : "has", Money);
        }

        public AbstractPlayer(uint initialMoney, string name)
        {
            Money = initialMoney;
            Name = name;
        }

        public override string ToString()
        {
            return Name;
        }
    }
}
