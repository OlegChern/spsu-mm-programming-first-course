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
            Clear += () => Console.Clear();
            Clear += () => Console.Write("Ваши фишки: {0}", Chips);
            Clear();
        }

        public void MakeBet()
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
                Clear();
                Clear += () =>
                {
                    Console.SetCursorPosition(10, 12);
                    Console.Write("Ваша ставка: {0}", Bet);
                };
                Clear();
              
            }
            catch
            {
                Clear();
                Console.SetCursorPosition(10, 11);
                Console.Write("Ошибка! Попробуйте еще раз.");
                MakeBet();
            }
        }              
        public override bool IsNext(Deck deck)
        {            
            Console.SetCursorPosition(10, 16);
            Console.Write("Взять еще карту? Да/Нет: ");
            var answer = Console.ReadLine();
            if (answer == "Да")
            {
                HitMe(deck);
                Clear();
                return true;
            }
            else if (answer == "Нет")
            {
                Clear();
                return false;
            }
            else
            {
                Clear();
                Console.SetCursorPosition(10, 14);
                Console.Write("Ошибка! Попробуйте еще раз.");
                return IsNext(deck);
            }
        }
        public bool TakeProfit()
        {            
            Console.SetCursorPosition(3, 16);
            Console.Write("Забрать выигрыш в размере ставки? Да/Нет (Если нет игра продолжится) : ");
            var answer = Console.ReadLine();
            if (answer == "Да")
            {
                return true;
            }
            else if (answer == "Нет")
            {
                return false;
            }
            else
            {
                Clear();
                Console.SetCursorPosition(10, 14);
                Console.Write("Ошибка! Попробуйте еще раз.");
                return TakeProfit();
            }
        }

        public event Action Clear;       
        public void GetClear()
        {
            Clear();
        }
    }
}
