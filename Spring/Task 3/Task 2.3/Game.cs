using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BlackJack
{
    public class Game<T>
        where T : Human, IPlayer
    {
        public Dealer Dealer { get; set; }

        public T Player { get; set; }

        public Deck Deck { get; set; }

        public bool ExitGame { get; set; }

        public Game(T player)
        {
            Dealer = new Dealer();
            Deck = new Deck();
            Player = player;
            ExitGame = false;
            Clear += () =>
            {
                if (!Player.IsBot)
                {
                    Console.Clear();
                    Console.Write("Ваши фишки: {0}", Player.Chips);
                    PrintCards();
                }
            };
        }

        public event Action Clear;

        public void PrintCards()
        {
            Console.SetCursorPosition(10, 5);
            Console.Write("Крупье: ");
            Dealer.Print();
            Console.SetCursorPosition(10, 8);
            Console.Write("Игрок:  ");
            Player.Print();
        }

        public void StartGame()
        {
            while (!ExitGame)
            {
                StartParty();
                if (Player.IsBot)
                {
                    if (Player.CountParty == 40)
                    ExitGame = true;
                }        
                if (Player.Chips == 0)
                {
                    ExitGame = true;
                }
            }
        }

        public void StartParty()
        {
            Clear();  
            while (!Player.MakeBet())
            {
                Clear();
                Console.SetCursorPosition(10, 11);
                Console.Write("Ошибка! Попробуйте еще раз.");
            }
            Clear += () =>
            {
                if (!Player.IsBot)
                {
                    Console.SetCursorPosition(10, 12);
                    Console.Write("Ваша ставка: {0}", Player.Bet);
                }
            };
            Clear();
            Player.CountParty++;           
            Dealer.HitMe(Deck);
            Player.HitMe(Deck);
            Player.HitMe(Deck);
            Clear();            
            ProcessParty();
        }

        public void StepParty<U>(U player)
            where U : Human
        {
            while (true)
            {
                var next = player.IsNext();
                if (next == "Нет")
                {
                    Clear();
                    break;
                }
                else if (next == "Да")
                {
                    player.HitMe(Deck);
                    Clear();                   
                }
                else
                {
                    Clear();
                    Console.SetCursorPosition(10, 14);
                    Console.Write("Ошибка! Попробуйте еще раз.");
                }
                if (player.Sum > 21)
                {
                    break;
                }
            }
        }

        public void ProcessParty()
        {            
            if (Player.Sum == 21)
            {
                if (Dealer.Sum == 11)
                {
                    while (true)
                    {
                        var answer = Player.TakeProfit();
                        if (answer == "Да")
                        {
                            EndParty(true, 1);
                            return;
                        }
                        else if (answer == "Нет")
                        {
                            Clear();                            
                            break;
                        }
                        Clear();
                        Console.SetCursorPosition(10, 14);
                        Console.Write("Ошибка! Попробуйте еще раз.");
                    }
                }
                else if (Dealer.Sum != 10)
                {
                    EndParty(true, 1.5);
                    return;
                }
            }
            StepParty(Player);
            if (Player.Sum > 21)
            {
                EndParty(false, 0);
                return;
            }           
            StepParty(Dealer);           
            if (Dealer.Sum > 21)
            {
                EndParty(true, 1.5);
            }
            else if (Dealer.Sum < Player.Sum)
            {
                EndParty(true, 1.5);
            }
            else if (Dealer.Sum == Player.Sum)
            {
                EndParty(true, 0);
            }
            else
            {
                EndParty(false, 0);
            }

        }

        public void ClearHand<U>(U human)
            where U : Human
        {
            human.Bet = 0;
            human.HaveAce = false;
            human.Cards = new List<Card>();
        }

        public void EndParty(bool win, double k)
        {
            if (win == true)
            {
                Player.Chips += (int)Math.Round(k * Player.Bet);
                if (!Player.IsBot)
                {
                    Clear(); 
                    Console.SetCursorPosition(10, 16);
                    Console.Write("Вы выиграли!");
                }
            }
            else
            {
                Player.Chips -= Player.Bet;
                if (!Player.IsBot)
                {
                    Clear();
                    Console.SetCursorPosition(10, 16);
                    Console.Write("Вы проиграли!");
                }
            }
            if (!Player.IsBot)
            {
                Console.SetCursorPosition(10, 17);
                Console.Write("Нажмите любую клавишу для продолжения.");
                Console.ReadKey();
            }
            ClearHand(Player);
            ClearHand(Dealer);
            Clear();
        }
    }
}
