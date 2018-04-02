using System;
using System.Collections.Generic;

namespace TestWork
{
    static class Program
    {
        static void Main()
        {
            const int formatedInt = 42;
            const string formatedString = "Kirill";

            IList<IFormater<int>> intFormaters = new List<IFormater<int>>();
            IList<IFormater<string>> stringFormaters = new List<IFormater<string>>();

            foreach (FormatMode mode in Enum.GetValues(typeof(FormatMode)))
            {
                intFormaters.Add(new IntFormater(mode));
                stringFormaters.Add(new StringFormater(mode));
            }
            
            // Note this custom formater!
            stringFormaters.Add(new CustomStringFormater(FormatMode.AddFour, CustomFormat));
            
            foreach (var formater in intFormaters)
            {
                Console.WriteLine($"{formater.Mode}: {formater.Format(formatedInt)}");
            }
            
            Console.WriteLine();
            
            foreach (var formater in stringFormaters)
            {
                Console.WriteLine($"{formater.Mode}: {formater.Format(formatedString)}");
            }

            // Error CS1503:
            // stringFormaters[0].Format(formatedInt);
        }

        static string CustomFormat(FormatMode mode)
        {
            switch (mode)
            {
                case FormatMode.AddTwo:
                    return "<<";
                case FormatMode.AddFour:
                    return "<<<<";
                case FormatMode.AddSix:
                    return "<<<<<<";
                case FormatMode.SubstractSix:
                    return ">>>>>>";
                case FormatMode.SubstractFour:
                    return ">>>>";
                case FormatMode.SubstractTwo:
                    return ">>";
                case FormatMode.None:
                    return string.Empty;
                default:
                    throw new ArgumentOutOfRangeException(nameof(mode));
            }
        }
    }
}
