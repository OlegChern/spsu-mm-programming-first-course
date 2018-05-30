using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash
{
    public class Echo : Command
    {
        public Echo(List<string> args, Bash interpretator) : base(interpretator)
        {
            Arguments = args;
        }

        public override void Execute()
        {
            foreach (var e in Arguments)
            {
                Console.Write(e + " ");
            }
            Console.WriteLine();
        }

        public override List<string> ExecutePipe()
        {
            return Arguments;
        }
    }
}
