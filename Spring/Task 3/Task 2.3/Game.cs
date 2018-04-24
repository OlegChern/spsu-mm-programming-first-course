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
        }
               
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
                if (Player is Bot)
                {
                    if ((Player as Bot).CountParty == 40)
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
            Player.MakeBet();
            if (Player is Bot)
            {
                (Player as Bot).CountParty++;
            }
            else
            {
                (Player as Player).Clear += () => PrintCards();
            }            
            Player.HitMe(Deck);
            Player.HitMe(Deck);
            Dealer.HitMe(Deck);
            ProcessParty();
        }
        public void StepParty<U>(U player)
            where U : Human
        {
            while (true)
            {
                var next = player.IsNext(Deck);               
                if ((next == false) || (player.Sum > 21))
                {
                    break;
                }
            }
        }
        public void ProcessParty()
        {
            if (Player is Player)
            {
                (Player as Player).GetClear();
            }
            if (Player.Sum == 21)
            {
                if (Dealer.Sum == 11)
                {
                    if (Player.TakeProfit() == true)
                    {
                        EndParty(true, 1);
                        return;
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
            if (Player is Player)
            {
                (Player as Player).GetClear();
            }
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
                if (Player is Player)
                {
                    Console.SetCursorPosition(10, 16);
                    Console.Write("Вы выиграли!");
                }
            }
            else
            {
                Player.Chips -= Player.Bet;
                if (Player is Player)
                {
                    Console.SetCursorPosition(10, 16);
                    Console.Write("Вы проиграли!");
                }
            }
            ClearHand(Player);
            ClearHand(Dealer);
            if (Player is Player)
            {
                (Player as Player).Clear -= () =>
                {
                    Console.SetCursorPosition(10, 12);
                    Console.Write("Ваша ставка: {0}", Player.Bet);
                };
                Console.SetCursorPosition(10, 17);
                Console.Write("Нажмите любую клавишу для продолжения.");
                Console.ReadKey();
                (Player as Player).GetClear();

            }
        }
    }
}
