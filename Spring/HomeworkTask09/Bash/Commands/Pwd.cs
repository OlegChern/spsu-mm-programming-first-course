using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Bash.Commands
{
    /// <summary>
    /// Shows current directory
    /// </summary>
    class Pwd : ICommand
    {
        public void Execute()
        {
            string directory = Directory.GetCurrentDirectory();

            Bash.Instance.Printer.Print(directory);

            foreach (string fileName in Directory.GetFiles(directory))
            {
                Bash.Instance.Printer.Print("  " + fileName);
            }
        }
    }
}
