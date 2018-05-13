using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Interface;

namespace TestLib
{
    public class TestClass : IPrintable
    {
        public void Print()
        {
            Console.WriteLine("Обьект типа {0} реализует интерфейс IPrintable", typeof(TestClass).Name);
        }
    }
}
