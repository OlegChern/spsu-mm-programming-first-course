using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash
{
    public class Wc : Command
    {
        public Wc(List<string> args)
        {
            Arguments = args;
        }

        public List<string> GetStrings()
        {
            if (Arguments.Count == 1)
            {
                try
                {
                    var list = new List<string>();
                    var lines = File.ReadAllLines(Arguments[0]);
                    list.Add("Количество строк - " + lines.Length);
                    var words = new List<string>();
                    foreach (var e in lines)
                    {
                        words = words.Concat(e.Split(' ')).ToList();
                    }
                    int index = 0;
                    while (index < words.Count)
                    {
                        while ((words[index].Length == 0) && (index < words.Count))
                        {
                            words.RemoveAt(index);
                        }
                        index++;
                    }
                    list.Add("Количество слов - " + words.Count);
                    var bytes = File.ReadAllBytes(Arguments[0]);
                    list.Add("Количество байтов - " + bytes.Length);
                    return list;
                }
                catch
                {
                    throw new Exception("Ошибка: Не удалось открыть файл ...");
                }
            }
            else
            {
                throw new Exception("Ошибка: Неверно указан аргумент ...");
            }
        }

        public override void Execute()
        {
            var list = GetStrings();
            foreach (var e in list)
            {
                Console.WriteLine(e);
            }
        }

        public override List<string> ExecutePipe()
        {
            return GetStrings();
        }
    }
}
