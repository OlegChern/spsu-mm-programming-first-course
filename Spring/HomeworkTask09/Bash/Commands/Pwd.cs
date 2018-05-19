using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Bash.Commands
{
    class Pwd : ICommand
    {
        public void Execute()
        {
            string directory = Directory.GetCurrentDirectory();

            Console.WriteLine(directory);

            foreach (string fileName in Directory.GetFiles(directory))
            {
                Console.WriteLine("  " + fileName);
            }
        }
    }
}
