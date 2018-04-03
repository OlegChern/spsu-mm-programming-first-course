using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestOne
{
    class Program
    {
        static void Main(string[] args)
        {

            NewFormatValue NewVal = new NewFormatValue();
            while (true)
            {
                var TmpStr = Console.ReadLine();
                if (TmpStr == "0")
                {
                    break;
                }
                Console.WriteLine(NewVal.Format(TmpStr));
            }


            
        }
    }
}
