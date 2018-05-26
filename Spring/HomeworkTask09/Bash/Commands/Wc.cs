using System;
using System.IO;

namespace Bash.Commands
{
    /// <summary>
    /// Shows number of strings, words and bytes
    /// </summary>
    class Wc : ICommand
    {
        string path;

        public Wc(string path)
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
            int wordsCount = 0;
            long bytesCount = 0;

            try
            {
                lines = File.ReadAllLines(path);
                bytesCount = new FileInfo(path).Length;
            }
            catch
            {
                throw new Exception("Can't open file \"" + path + "\"");
            }

            foreach (string line in lines)
            {
                wordsCount += (line.Split(' ')).Length;
            }

            Bash.Instance.Printer.Print("Number of lines: " + lines.Length);
            Bash.Instance.Printer.Print("Number of words: " + wordsCount);
            Bash.Instance.Printer.Print("Number of bytes: " + bytesCount);
        }
    }
}
