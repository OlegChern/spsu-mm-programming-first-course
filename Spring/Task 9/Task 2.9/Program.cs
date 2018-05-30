using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash
{
    class Program
    {
        static void Main(string[] args)
        {
            var console = new ConsoleExecute();
            var bash = new Bash(console);
            bash.Start();
        }
    }
}
