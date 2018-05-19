using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Bash.Commands
{
    class Cat : ICommand
    {
        string path;

        public Cat(string path)
        {
            this.path = path;
        }

        public void Execute()
        {
            string[] lines;

            try
            {
                lines = File.ReadAllLines(path);
            }
            catch
            {
                throw new Exception("Can't open file \"" + path + "\"");
            }

            foreach (string line in lines)
            {
                Console.WriteLine(line);
            }
        }
    }
}
