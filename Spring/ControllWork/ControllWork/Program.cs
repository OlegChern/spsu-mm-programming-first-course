using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControllWork
{
    class Program
    {
        static void Main(string[] args)
        {
            var list = new List<int> { 1, 2, 3, 4, 5 };
            foreach (var e in list)
            {
                Console.Write(e.ToString() + " ");
            }
            Console.WriteLine();
            var inversion = new Inversion();
            var inversList = inversion.Permute(list);
            foreach (var e in inversList)
            {
                Console.Write(e.ToString() + " ");
            }
            Console.WriteLine();
            var shift = new ShiftRight();
            var shiftList = shift.Permute(list);
            foreach (var e in shiftList)
            {
                Console.Write(e.ToString() + " ");
            }
            Console.WriteLine();
        }
    }
}
