using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash
{
    public class SystemCommand : Command
    {
        public string Name { get; }

        public SystemCommand(string name, List<string> args)
        {
            Arguments = args;
            Name = name;
        }

        public override void Execute()
        {
            try
            {
                var procInfo = new ProcessStartInfo(Name);

                if (Arguments.Count != 0)
                {
                    var arg = Arguments[0];
                    if (Arguments.Count > 1)
                    {
                        for (int i = 1; i < Arguments.Count; i++)
                        {
                            arg += " " + Arguments[i];
                        }
                    }
                    procInfo.Arguments = arg;
                }
                Process.Start(procInfo);
            }
            catch
            {
                throw new Exception("Ошибка: Не удалось запустить данную команду ...");
            }
        }

        public override List<string> ExecutePipe()
        {
            Execute();
            return new List<string>();
        }
    }
}
