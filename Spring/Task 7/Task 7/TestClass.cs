using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Program
{
    public class TestClass
    {
        static Random random = new Random();

        public int Value { get; set; }

        public TestClass()
        {
            Value = random.Next() % 100;
        }

        public override string ToString()
        {
            return Value.ToString() ;
        }
    }
}
