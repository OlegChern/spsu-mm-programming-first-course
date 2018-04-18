using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    internal class RightCyclicPermutationShift<T> : SequencePermutation<T>
    {
        public override List<T> Permute(List<T> inList)
        {
            var outList = new List<T>();
            
            outList.Add(inList.Last());

            for (var i = 1; i < inList.Count ; ++i)
            {
                outList.Add(inList[i - 1]);
            }

            return outList;
        }
    }
}
