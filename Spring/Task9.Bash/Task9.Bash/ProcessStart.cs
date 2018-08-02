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
                var process = new Process();
                process.StartInfo = new ProcessStartInfo(Arguments[0]);
                process.StartInfo.UseShellExecute = false;
                process.Start();
            }
            catch(Exception)
            {
                throw new ArgumentException("incorrect '" + Name + "'");
            }
        }
    }
}
