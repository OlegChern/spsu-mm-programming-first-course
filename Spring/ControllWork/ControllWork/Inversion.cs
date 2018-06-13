using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControllWork
{
    public class Inversion : Permutation
    {
        public override IEnumerable<T> Permute<T>(IEnumerable<T> collection)
        {
            var newCollection = collection.Reverse();
            return newCollection;
        }
    }
}
