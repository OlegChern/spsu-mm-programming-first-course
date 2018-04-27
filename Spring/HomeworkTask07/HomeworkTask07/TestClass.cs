using System;

namespace HomeworkTask07
{
    class TestClass
    {
        static Random random = new Random();

        float x;
        float y;

        public TestClass()
        {
            x = (float)random.NextDouble();
            y = (float)random.NextDouble();
        }

        public override string ToString()
        {
            return x.ToString("F") + " " + y.ToString("F");
        }
    }
}
