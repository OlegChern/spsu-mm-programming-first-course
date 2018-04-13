using System;

namespace Task_2
{
    class Program
    {
        static void Main(string[] args)
        {
            BlitzenMTLS firstMyTank = new BlitzenMTLS();
            firstMyTank.GetInfo();
            AMXChasseurDeChars secondMyTank = new AMXChasseurDeChars();
            secondMyTank.GetInfo(); 
            Console.ReadKey();
        }
    }
}
