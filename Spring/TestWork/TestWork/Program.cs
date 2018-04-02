using System;
using System.Collections.Generic;
using static TestWork.FormatMode;

namespace TestWork
{
    static class Program
    {
        static void Main()
        {
            const int formatedInt = 42;
            
            var intFormaters = new List<IFormater<int>>
            {
                new IntFormater(AddTwo),
                new IntFormater(AddFour),
                new IntFormater(AddSix)
            };
            
            foreach (var formater in intFormaters)
            {
                Console.WriteLine(formater.Format(formatedInt));
            }
            
            Console.WriteLine();

            const string formatedString = "42";
            
            var stringFormaters = new List<IFormater<string>>
            {
                new StringFormater(AddTwo),
                new StringFormater(AddFour),
                new StringFormater(AddSix)
            };
            
            foreach (var formater in stringFormaters)
            {
                Console.WriteLine(formater.Format(formatedString));
            }

            // Error CS1503:
            // stringFormaters[0].Format(formatedInt);
        }
    }
}
