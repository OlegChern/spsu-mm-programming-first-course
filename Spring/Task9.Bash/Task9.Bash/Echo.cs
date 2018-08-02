using System;
using System.Collections.Generic;

namespace Task9.Bash
{
    public class Echo : ICommand
    {
        public string Name { get; }

        public List<string> Arguments { get; set; }

        public List<string> Output { get; }

        public Echo(List<string> arguments)
        {
            Arguments = arguments;
            Name = "echo";
            foreach (var temp in arguments)
            {
                Name = Name + ' ' + temp;
            }
            Output = new List<string>();
        }

        public static void PrintInfo()
        {
            Console.WriteLine("echo – display the arguments");
        }

        public void Execute()
        {
            foreach(var temp in Arguments)
            {
                Console.Write("{0} ", temp);
                Output.Add(temp);
            }
            Console.WriteLine();
        }
    }
}
