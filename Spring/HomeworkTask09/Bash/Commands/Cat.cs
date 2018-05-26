using System;
using System.IO;

namespace Bash.Commands
{
    /// <summary>
    /// Shows file content
    /// </summary>
    class Cat : ICommand
    {
        string path;

        public Cat(string path)
        {
            if (path.Length == 0)
            {
                throw new ArgumentException("No arguments!");
            }

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
                Bash.Instance.Printer.Print(line);
            }
        }
    }
}
