using System;
using Bash;

namespace Program
{
    public class ConsoleUserInterface : IPrinter, IReader
    {
        public void Print(string message)
        {
            Console.WriteLine(message);
        }

        public string Read()
        {
            return Console.ReadLine();
        }
    }
}
