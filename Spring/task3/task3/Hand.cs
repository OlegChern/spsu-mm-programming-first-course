using System.Collections.Generic;

namespace task3
{
    class Hand
    {
        public AbstractPlayer Owner { get; private set; }
        public List<Card> Cards { get; set; }
        public uint InitialBet { get; private set; }

        public Hand(AbstractPlayer owner, List<Card> cards, uint initialBet)
        {
            Owner = owner;
            Cards = cards;
            InitialBet = initialBet;
        }
    }
}
