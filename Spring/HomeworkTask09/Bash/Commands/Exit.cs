using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash.Commands
{
    /// <summary>
    /// Stops Bash
    /// </summary>
    class Exit : ICommand
    {
        public void Execute()
        {
            Bash.Instance.Stop();
        }
    }
}
