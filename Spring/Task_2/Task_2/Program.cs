using System;
using ATankLib;
using CustomTankLib;

namespace Task_2
{
    class Program
    {
        static void Main(string[] args)
        {
            BlitzenMTLS firstMyTank = new BlitzenMTLS();
            AMXChasseurDeChars secondMyTank = new AMXChasseurDeChars();
            PrintInfoAboutTank(firstMyTank);
            PrintInfoAboutTank(secondMyTank);
            Console.ReadKey();
        }

        static void PrintInfoAboutTank(ATank tank)
        {
            tank.GetInfo();
        }
    }
}
