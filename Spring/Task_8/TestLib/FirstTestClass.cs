using System;
using Interfaces;

namespace TestLib
{
    public class FirstTestClass : ITest
    {
        public void PrintInfo()
        {
            Console.WriteLine("It works for {0}", ToString());
        }
    }
}
