using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace Task9.Bash
{
    public class ProcessStart : ICommand
    {
        public string Name { get; }

        public List<string> Arguments { get; set; }

        public List<string> Output { get; }

        public ProcessStart(List<string> arguments)
        {
            Arguments = arguments;
            Name = arguments[0];
        }

        public static void PrintInfo()
        {
            Console.WriteLine("Process.Start");
        }

        public void Execute()
        {
            try
            {
                var procInfo = new ProcessStartInfo(Name);
                procInfo.UseShellExecute = false;

                if (Arguments.Count > 1)
                {
                    var arg = Arguments[1];
                    if (Arguments.Count > 2)
                    {
                        for (int i = 2; i < Arguments.Count; i++)
                        {
                            arg += " " + Arguments[i];
                        }
                    }
                    procInfo.Arguments = arg;
                    Console.WriteLine(arg);
                }
                Process.Start(procInfo);
            }
            catch
            {
                throw new Exception("Ошибка: Не удалось запустить данную команду ...");
            }
        }
    }
}
