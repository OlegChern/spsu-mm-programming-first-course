using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    public class Player : Human, IPlayer
    {
        public Player() : base()
        {
            Chips = 1000;
        }

        public bool MakeBet()
        {          
            Console.SetCursorPosition(10, 12);
            Console.Write("Введите вашу ставку: ");
            try
            {
                var bet = Int32.Parse(Console.ReadLine());
                Bet = bet;
                if ((Bet > Chips) || (Bet <= 0))
                {
                    throw new ArgumentException();
                }
                return true;
            }
            catch
            {
                return false;
            }
        }              

        public override string IsNext()
        {
            Console.SetCursorPosition(10, 16);
            Console.Write("Взять еще карту? Да/Нет: ");
            return Console.ReadLine();
        }

        public string TakeProfit()
        {
            Console.SetCursorPosition(3, 16);
            Console.Write("Забрать выигрыш в размере ставки? Да/Нет (Если нет игра продолжится) : ");
            return Console.ReadLine();
        }            
    }
}
