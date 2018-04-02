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
        public static readonly int DeckSize = NumberOfDecks * NumberOfCards;
        private static int CardsInDeckNow = DeckSize;

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
                return 2;
            }

            SelectedValue += _three;

            if (SelectedValue > IndCardPos)
            {
                CardsInDeckNow--;
                _three--;
                return 3;
            }

            SelectedValue += _four;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _four--;
                return 4;
            }

            SelectedValue += _five;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _five--;
                return 5;
            }

            SelectedValue += _six;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _six--;
                return 6;
            }

            SelectedValue += _seven;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _seven--;
                return 7;
            }

            SelectedValue += _eight;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _eight--;
                return 8;
            }

            SelectedValue += _nine;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _nine--;
                return 9;
            }

            SelectedValue += _ten;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _ten--;
                return 10;
            }

            SelectedValue += _jack;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _jack--;
                return 10;
            }

            SelectedValue += _queen;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _queen--;
                return 10;
            }

            SelectedValue += _king;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _king--;
                return 10;
            }

            SelectedValue += _ace;

            if (SelectedValue  > IndCardPos)
            {
                CardsInDeckNow--;
                _ace--;
                return 11;
            }

            return -1;
        }

    }
}
