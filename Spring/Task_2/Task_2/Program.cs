using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_2
{
    class Program
    {
        static void Main(string[] args)
        {
            BlitzenMTLS FirstMyTank = new BlitzenMTLS();
            FirstMyTank.GetInfo();
            AMXChasseurDeChars SecondMyTank = new AMXChasseurDeChars();
            SecondMyTank.GetInfo(); 
            Console.ReadKey();
        }
    }
}
