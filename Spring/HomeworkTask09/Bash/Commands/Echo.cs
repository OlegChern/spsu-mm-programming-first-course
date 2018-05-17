using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
