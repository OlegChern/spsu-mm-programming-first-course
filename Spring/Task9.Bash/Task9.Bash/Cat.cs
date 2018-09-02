using System;
using System.Collections.Generic;
using System.IO;

namespace Task9.Bash
{
    public class Cat : ICommand
    {
        public string Name { get; }

        public List<string> Arguments { get; set; }

        public List<string> Output { get; }

        public Cat(List<string> arguments)
        {
            Arguments = arguments;
            Name = "cat";
            foreach (var temp in arguments)
            {
                Name = Name + ' ' + temp;
            }
            Output = new List<string>();
        }

        public static void PrintInfo()
        {
            Console.WriteLine("cat [FILENAME] – display the contents of the file");
        }

        public void Execute()
        {
            if (Arguments.Count == 0)
            {
                throw new ArgumentException("Incorrect arguments in '" + Name + "'");
            }

            foreach(var tmp in Arguments)
            {
                string[] lines;
                try
                {
                    lines = File.ReadAllLines(tmp);
                }
                catch
                {
                    throw new ArgumentException("Incorrect path to file");
                }
                foreach (var temp in lines)
                {
                    Console.WriteLine(temp);
                }
                Console.WriteLine();
                Output.AddRange(lines);
            }        
        }
    }
}
