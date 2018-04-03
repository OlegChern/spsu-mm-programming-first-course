using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Task_3
{
    internal class Deck
    {
        private const int NumberOfDecks = 8;
        private const int NumberOfCards = 13;
        public static readonly int DeckSize = NumberOfCards * NumberOfDecks;
        private int _cardsInDeckNow = NumberOfCards * NumberOfDecks;

        private int _two = NumberOfDecks;
        private int _three = NumberOfDecks;
        private int _four = NumberOfDecks;
        private int _five = NumberOfDecks;
        private int _six = NumberOfDecks;
        private int _seven = NumberOfDecks;
        private int _eight = NumberOfDecks;
        private int _nine = NumberOfDecks;
        private int _ten = NumberOfDecks;
        private int _jack = NumberOfDecks;
        private int _queen = NumberOfDecks;
        private int _king = NumberOfDecks;
        private int _ace = NumberOfDecks;

        public int TakeRandomCard(Random r)
        {
            int selectedValue = 0;
            int indCardPos = r.Next(_cardsInDeckNow);

            selectedValue += _two;

            if (selectedValue > indCardPos)
            {
                _cardsInDeckNow--;
                _two--;
                return (int)CardsValue.Two;
            }

            selectedValue += _three;

            if (selectedValue > indCardPos)
            {
                _cardsInDeckNow--;
                _three--;
                return (int)CardsValue.Three;
            }

            selectedValue += _four;

            if (selectedValue  > indCardPos)
            {
                _cardsInDeckNow--;
                _four--;
                return (int)CardsValue.Four;
            }

            selectedValue += _five;

            if (selectedValue  > indCardPos)
            {
                _cardsInDeckNow--;
                _five--;
                return (int)CardsValue.Five;
            }

            selectedValue += _six;

            if (selectedValue  > indCardPos)
            {
                _cardsInDeckNow--;
                _six--;
                return (int)CardsValue.Six;
            }

            selectedValue += _seven;

            if (selectedValue  > indCardPos)
            {
                _cardsInDeckNow--;
                _seven--;
                return (int)CardsValue.Seven;
            }

            selectedValue += _eight;

            if (selectedValue  > indCardPos)
            {
                _cardsInDeckNow--;
                _eight--;
                return (int)CardsValue.Eight;
            }

            selectedValue += _nine;

            if (selectedValue  > indCardPos)
            {
                _cardsInDeckNow--;
                _nine--;
                return (int)CardsValue.Nine;
            }

            selectedValue += _ten;

            if (selectedValue  > indCardPos)
            {
                _cardsInDeckNow--;
                _ten--;
                return (int)CardsValue.Ten;
            }

            selectedValue += _jack;

            if (selectedValue  > indCardPos)
            {
                _cardsInDeckNow--;
                _jack--;
                return (int)CardsValue.Jack;
            }

            selectedValue += _queen;

            if (selectedValue  > indCardPos)
            {
                _cardsInDeckNow--;
                _queen--;
                return (int)CardsValue.Queen;
            }

            selectedValue += _king;

            if (selectedValue  > indCardPos)
            {
                _cardsInDeckNow--;
                _king--;
                return (int)CardsValue.King;
            }

            selectedValue += _ace;

            if (selectedValue  > indCardPos)
            {
                _cardsInDeckNow--;
                _ace--;
                return (int)CardsValue.Ace;
            }

            return -1;
        }

    }
}
