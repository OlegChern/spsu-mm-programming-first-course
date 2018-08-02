using System;
using System.Collections.Generic;
using System.IO;

namespace Task9.Bash
{
    public class Pwd : ICommand
    {
        public string Name { get; }

        public List<string> Arguments { get; set; }

        public List<string> Output { get; }

        public Pwd(List<string> arguments)
        {
            Arguments = arguments;
            Name = "pwd";
            foreach (var temp in arguments)
            {
                Name = Name + ' ' + temp;
            }
            Output = new List<string>();
        }

        public static void PrintInfo()
        {
            Console.WriteLine("pwd – display the current working directory");
        }

        public void Execute()
        {
            if (Arguments.Count != 0)
            {
                throw new ArgumentException("Incorrect arguments in '" + Name + "'");
            }

            string directory = Directory.GetCurrentDirectory();
            Console.WriteLine(directory);
            Output.Add(directory);

            string[] files = Directory.GetFiles(directory);
            foreach (var temp in files)
            {
                Console.WriteLine(temp);
                Output.Add(temp);
            }
        }
    }
}
