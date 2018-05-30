using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash
{
    public class Exit : Command
    {
        public Exit(List<string> args, Bash interpretator) : base(interpretator)
        {
            Arguments = args;
        }

        public override void Execute()
        {
            if (Arguments.Count == 0)
            {
                Interpretator.Stop();
            }
            else
            {
                throw new Exception("Ошибка: У данной команды не должно быть аргументов ...");
            }
        }

        public override List<string> ExecutePipe()
        {
            return new List<string>();
        }
    }
}
