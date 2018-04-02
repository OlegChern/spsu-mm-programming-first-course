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

            #region int
            IntClass intExample = new IntClass(3);

            Console.WriteLine("Int Example #1");
            Console.WriteLine(intExample.Format(3));

            Console.WriteLine("\nInt Example #2");
            Console.WriteLine(intExample.Format(-4));
            #endregion

            #region string
            StringClass strExample = new StringClass("StringExample");

            Console.WriteLine("\nSting Example #1");
            Console.WriteLine(strExample.Format("FormatTest"));

            Console.WriteLine("\nSting Example #2");
            Console.WriteLine(strExample.Format("VS"));
            #endregion

            #region bool
            BoolClass boolExample = new BoolClass(true);

            Console.WriteLine("\nBool Example #1");
            Console.WriteLine(boolExample.Format(true));
            #endregion
        }
    }
}
