using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControlWork
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Example #1");

            IntClass example = new IntClass(3);
            Console.WriteLine(example.Format(2));

            Console.WriteLine("\nExample #2");

            StringClass strExample = new StringClass("StringExample");
            Console.WriteLine(strExample.Format("FormatTest"));

            Console.WriteLine("\nExample #3");

            BoolClass boolExample = new BoolClass(true);
            Console.WriteLine(boolExample.Format(true));
        }
    }
}
