using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControllWork
{
    public class ShiftRight : Permutation
    {
        public override IEnumerable<T> Permute<T>(IEnumerable<T> collection)
        {
            var list = collection.ToList();
            var lastElement = list.Last();
            list.Remove(lastElement);
            var newList = new List<T>() { lastElement };
            foreach (var e in list)
            {
                newList.Add(e);
            }
            return newList;
        }
    }
}
