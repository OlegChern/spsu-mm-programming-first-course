using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WeakHashtable
{
    public class Element<T>
        where T : class 
    {
        public string Key { get; private set; }

        public WeakReference<T> RefValue { get; private set; }

        public Element(string key, T value)
        {
            Key = key;
            RefValue = new WeakReference<T>(value);
        }

    }
}
