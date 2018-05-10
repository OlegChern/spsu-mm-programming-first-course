using System;
using Interfaces;

namespace TestLib
{
    class ThirdTestClass : ITest
    {
        public void PrintInfo()
        {
            Console.WriteLine("It works for {0}",ToString());
        }
    }
}
