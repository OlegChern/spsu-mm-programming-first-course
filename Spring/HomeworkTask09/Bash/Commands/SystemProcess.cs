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
                Process.Start(argument);
            }
            catch
            {
                throw new Exception("Can't start process \"" + argument + "\"");
            }
        }
    }
}
