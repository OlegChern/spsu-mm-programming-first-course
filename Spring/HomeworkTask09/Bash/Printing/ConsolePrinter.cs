using System;

namespace Bash.Printing
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
