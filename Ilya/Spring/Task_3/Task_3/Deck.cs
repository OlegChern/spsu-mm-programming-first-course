using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Task_3
{
    class Deck
    {
        static readonly int NumberOfDecks = 8;
        static readonly int NumberOfCards = 13;
        public static readonly int DeckSize = NumberOfCards * NumberOfDecks;
        private int CardsInDeckNow = NumberOfCards * NumberOfDecks;

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
            int SelectedValue = 0;
            int IndCardPos = r.Next(CardsInDeckNow);

            SelectedValue += _two;

            if (SelectedValue > IndCardPos)
            {
                CardsInDeckNow--;
                _two--;
                return (int)CardsValue.Two;
            }

            SelectedValue += _three;

            if (SelectedValue > IndCardPos)
            {
                CardsInDeckNow--;
                _three--;
                return (int)CardsValue.Three;
            }

            SelectedValue += _four;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _four--;
                return (int)CardsValue.Four;
            }

            SelectedValue += _five;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _five--;
                return (int)CardsValue.Five;
            }

            SelectedValue += _six;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _six--;
                return (int)CardsValue.Six;
            }

            SelectedValue += _seven;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _seven--;
                return (int)CardsValue.Seven;
            }

            SelectedValue += _eight;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _eight--;
                return (int)CardsValue.Eight;
            }

            SelectedValue += _nine;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _nine--;
                return (int)CardsValue.Nine;
            }

            SelectedValue += _ten;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _ten--;
                return (int)CardsValue.Ten;
            }

            SelectedValue += _jack;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _jack--;
                return (int)CardsValue.Jack;
            }

            SelectedValue += _queen;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _queen--;
                return (int)CardsValue.Queen;
            }

            SelectedValue += _king;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _king--;
                return (int)CardsValue.King;
            }

            SelectedValue += _ace;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _ace--;
                return (int)CardsValue.Ace;
            }

            return -1;
        }

    }
}
