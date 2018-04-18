using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Program
    {
        static void PrintPermutedList(List<int> myList, SequencePermutation<int> kindOfPermute)
        {
            foreach (var i in kindOfPermute.Permute(myList))
            {
                Console.Write("{0} ", i);
            }
            Console.WriteLine();
        }

        
        static void Main(string[] args)
        {
            var myList = new List<int>{1,2,3,4,5};

            Console.WriteLine("It is list after inverting permutaton:");
            PrintPermutedList(myList, new InvertingPermutation<int>());

            Console.WriteLine("It is list after right cyclic permutaton:");
            PrintPermutedList(myList, new RightCyclicPermutationShift<int>());
        }
    }
}
