using System;
using Interfaces;

namespace SecondTestClassesLib
{
    public class FirstTestClassInSecondLib : ITest
    {
        public void PrintInfo()
        {
            Console.WriteLine("It works from second library too!");
        }
    }
}
