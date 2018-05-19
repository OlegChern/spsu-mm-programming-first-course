using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash.Commands
{
    class Wc : ICommand
    {
        string path;

        public Wc(string path)
        {
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

            Console.WriteLine("Number of lines: " + lines.Length);
            Console.WriteLine("Number of words: " + wordsCount);
            Console.WriteLine("Number of bytes: " + bytesCount);
        }
    }
}
