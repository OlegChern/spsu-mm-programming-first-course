using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ControllWork
{
    public abstract class Permutation
    {
        public abstract IEnumerable<T> Permute<T>(IEnumerable<T> collection);
    }
}
