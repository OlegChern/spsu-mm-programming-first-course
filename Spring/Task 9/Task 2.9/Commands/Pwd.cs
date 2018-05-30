using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash
{
    public class Pwd : Command
    {
        private List<string> GetStrings()
        {
            var list = new List<string>();
            list.Add(Directory.GetCurrentDirectory());
            var files = Directory.GetFiles(list[0]);
            list = list.Concat(files).ToList();
            return list;
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
