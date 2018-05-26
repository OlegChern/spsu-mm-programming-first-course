using System;
using System.Diagnostics;

namespace Bash.Commands
{
    class SystemProcess : ICommand
    {
        string argument;

        public SystemProcess(string argument)
        {
            this.argument = argument;
        }

        public void Execute()
        {
            try
            {
                var process = new Process();

                process.StartInfo = new ProcessStartInfo(argument);
                process.StartInfo.UseShellExecute = false;

                process.Start();
            }
            catch
            {
                throw new Exception("Can't start process \"" + argument + "\"");
            }
        }
    }
}
