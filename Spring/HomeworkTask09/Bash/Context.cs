using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash
{
    class Context
    {
        private ICommand command;

        public Context() { }

        public void SetCommand(ICommand command)
        {
            this.command = command;
        }

        public void ExecuteCommand()
        {
            if (command == null)
            {
                return;
            }

            command.Execute();
        }
    }
}
