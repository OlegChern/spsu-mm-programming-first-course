using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_4
{
    class Program
    {
        static void Main(string[] args)
        {
            if (Tests.TestInt() && Tests.TestDouble() && Tests.TestString())
            {
                Console.WriteLine("Tests completed!");
            }
            else
            {
                Console.WriteLine("Look for errors!");
            }
        }
    }
}
