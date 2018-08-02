using System;
using System.Collections.Generic;
using System.IO;

namespace Task9.Bash
{
    public class Wc : ICommand
    {
        public string Name { get; }

        public List<string> Arguments { get; set; }

        public List<string> Output { get; }

        public Wc(List<string> arguments)
        {
            Arguments = arguments;
            Name = "wc";
            foreach (var temp in arguments)
            {
                Name = Name + ' ' + temp;
            }
            Output = new List<string>();
        }

        public static void PrintInfo()
        {
            Console.WriteLine("wc [FILENAME] – display the number of lines, words and bytes in the file");
        }

        public void Execute()
        {
            if (Arguments.Count != 1)
            {
                throw new ArgumentException("Incorrect arguments in '" + Name + "'");
            }

            int numberOfLines;
            int numberOfWords;
            int numberOfBytes;

            try
            {
                string[] lines = File.ReadAllLines(Arguments[0]);
                numberOfLines = lines.Length;

                numberOfWords = 0;
                foreach (var temp in lines)
                {
                    string[] words = temp.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    numberOfWords += words.Length;
                }

                byte[] bytes = File.ReadAllBytes(Arguments[0]);
                numberOfBytes = bytes.Length;
            }
            catch
            {
                throw new ArgumentException("Incorrect path to file");
            }

            Console.WriteLine("Number of lines: {0}", numberOfLines);
            Console.WriteLine("Number of words: {0}", numberOfWords);
            Console.WriteLine("Number of bytes: {0}", numberOfBytes);

            Output.Add(numberOfLines.ToString());
            Output.Add(numberOfWords.ToString());
            Output.Add(numberOfBytes.ToString());
        }
    }
}
