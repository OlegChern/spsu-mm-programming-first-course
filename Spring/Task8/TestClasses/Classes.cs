using System;
using Interface;

namespace TestClasses
{
    public class ClassA : TempInterface
    {
        public ClassA()
        { }
    
        public void DoSomething()
        {
            Console.WriteLine("Class A");
        }
    }

    public class ClassB : TempInterface
    {
        public void DoSomething()
        {
            Console.WriteLine("Class B");
        }
    }

    public class ClassC
    {
        public void DoSomething()
        {
            Console.WriteLine("Class C");
        }
    }
}
