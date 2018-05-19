using System;

namespace Bash.Commands
{
    class Echo : ICommand
    {
        string argument;

        public Echo(string argument)
        {
            this.argument = argument;
        }

        public void Execute()
        {
            Console.WriteLine(argument);
        }
    }
}
