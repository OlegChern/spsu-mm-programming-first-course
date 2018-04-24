using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    public class Card
    {
        public string Suit { get; set; }
        public string Name { get; set; }
        public int Value { get; set; }
        public Card(string name, string suit)
        {
            Suit = suit;
            Name = name;
            if ((Name == "В") || (Name == "Д") || (Name == "К"))
            {
                Value = 10;
            }
            else if (Name == "Т")
            {
                Value = 11;
            }
            else
            {
                Value = Int32.Parse(Name);
            }
        }
        public void Print()
        {
            Console.BackgroundColor = ConsoleColor.White;
            if ((Suit == "♥") || (Suit == "♦"))
            {
                Console.ForegroundColor = ConsoleColor.Red;
            }
            else
            {
                Console.ForegroundColor = ConsoleColor.Black;
            }
            var left = Console.CursorLeft;
            var top = Console.CursorTop;
            if (Name != "10")
            {
                Console.Write("{0} ", Name);
            }
            else
            {
                Console.Write("{0}", Name);
            }
            Console.SetCursorPosition(left, top + 1);
            Console.Write(" {0}", Suit);
            Console.SetCursorPosition(left + 3, top);
            Console.ResetColor();
        }
    }
}
