using System;
using System.Collections.Generic;

namespace Task9.Bash
{
    public class Exit : ICommand
    {
        public string Name { get; }

        public List<string> Arguments { get; set; }

        public List<string> Output { get; }

        public Exit(List<string> arguments)
        {
            Arguments = arguments;
            Name = "exit";
            foreach(var temp in arguments)
            {
                Name = Name + ' ' + temp;
            }
            if (arguments.Count != 0)
            {
                throw new ArgumentException("Incorrect arguments in '" + Name + "'");
            }
        }

        public static void PrintInfo()
        {
            Console.WriteLine("exit – exit interpreter");
        }

        public void Execute()
        {
            Environment.Exit(0);
        }
    }
}
