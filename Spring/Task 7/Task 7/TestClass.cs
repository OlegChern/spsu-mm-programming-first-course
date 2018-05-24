using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Program
{
    public class TestClass
    {
        public int Value { get; set; }

        public TestClass(int value)
        {
            Value = value;
        }

        public override string ToString()
        {
            return Value.ToString() ;
        }
    }
}
