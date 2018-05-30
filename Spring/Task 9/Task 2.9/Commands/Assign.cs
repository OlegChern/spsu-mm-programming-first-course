using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash
{
    public class Assign : Command
    {
        public string Name { get; }
        public Assign(string name, List<string> args)
        {
            Name = name;
            Arguments = args;
        }

        public override void Execute()
        {
            if (Arguments.Count != 1)
            {
                throw new Exception("Ошибка: Не удалось присвоить данное значение ...");
            }
            if (!Bash.BashObject.Variables.Select((z) => z.Name).Contains(Name))
            {
                Bash.BashObject.Variables.Add(new Variable(Name, Arguments[0]));
            }
            else
            {
                throw new Exception($"Ошибка: Переменной {Name} уже присвоено значение ...");
            }
        }

        public override List<string> ExecutePipe()
        {
            Execute();
            return new List<string>();
        }
    }
}
