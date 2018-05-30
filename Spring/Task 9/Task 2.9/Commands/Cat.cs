using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash
{
    public class Cat : Command
    {
        public Cat(List<string> args)
        {
            Arguments = args;
        }

        private string[] GetString(List<string> args)
        {
            if (Arguments.Count == 1)
            {
                try
                {
                    var lines = File.ReadAllLines(Arguments[0]);
                    return lines;
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
            var lines = GetString(Arguments);
            foreach (var e in lines)
            {
                Console.WriteLine(e);
            }
        }

        public override List<string> ExecutePipe()
        {
            return GetString(Arguments).ToList();
        }
    }
}
