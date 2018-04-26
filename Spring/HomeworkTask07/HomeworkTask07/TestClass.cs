using System;

namespace HomeworkTask07
{
    class TestClass
    {
        float x;
        float y;

        public TestClass()
        {
            Random random = new Random();
            x = (float)random.NextDouble();
            y = (float)random.NextDouble();
        }

        public override string ToString()
        {
            return x.ToString("F") + " " + y.ToString("F");
        }
    }
}
