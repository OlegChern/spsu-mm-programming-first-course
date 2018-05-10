using System;
using Interfaces;

namespace TestLib
{
    class SecondTestClass : ITest
    {
        public void PrintInfo()
        {
            Console.WriteLine("It works for {0}", ToString());
        }
    }
}
