using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class InvertingPermutation<T> : SequencePermutation<T>
    {
        public override List<T> Permute(List<T> inList)
        {
            var outList = new List<T>();

            foreach (var i in inList)
            {
                outList.Add(i);
            }

            outList.Reverse();
            return outList;
        }
    }
}
