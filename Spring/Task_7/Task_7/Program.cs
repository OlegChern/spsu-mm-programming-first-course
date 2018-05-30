using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Task_7
{
    class Program
    {
        static void Main(string[] args)
        {
            Tests tests = new Tests();
            if (tests.FirstTest())
            {
                Console.WriteLine("Program works correctly");
            }
            else
            {
                Console.WriteLine("The program does not work correctly");
            }

        }
    }
}
