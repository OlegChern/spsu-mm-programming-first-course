using System;

namespace task4.HashTable
{
    class Program
    {
        private static bool TestInt()
        {
            HashTable<int> table = new HashTable<int>(10);

            table.AddElement(3, 3);
            table.AddElement(14, 14);
            table.AddElement(23, 23);
            table.AddElement(133, 133);
            table.AddElement(15, 15);
            table.AddElement(24, 24);
            table.AddElement(444, 444);
            table.AddElement(1, 1);
            bool temp1 = (table.Contains(3) && table.Contains(14) && table.Contains(23)
                && table.Contains(133) && table.Contains(15) && table.Contains(24)
                && table.Contains(444) && table.Contains(1));

            table.DeleteElement(15);
            table.DeleteElement(23);
            table.DeleteElement(77);
            bool temp2 = (!table.Contains(15) && !table.Contains(23));

            bool temp3 = (table.GetValueByKey(24) == 24);

            bool temp4 = (table.Contains(3) && table.Contains(14)
                && table.Contains(133) && table.Contains(24)
                && table.Contains(444) && table.Contains(1));

            table.DeleteTable();

            return (temp1 && temp2 && temp3 && temp4);
        }

        private static bool TestDouble()
        {
            HashTable<double> tableDouble = new HashTable<double>(10);

            tableDouble.AddElement(3.1, 3);
            tableDouble.AddElement(14.1, 4);
            tableDouble.AddElement(23.1, 23);
            tableDouble.AddElement(133.1, 133);

            tableDouble.DeleteElement(23);

            bool temp1 = (tableDouble.Contains(3) && tableDouble.Contains(4) 
                && tableDouble.Contains(133) && !tableDouble.Contains(23));

            bool temp2 = (tableDouble.GetValueByKey(133) == 133.1);

            tableDouble.DeleteTable();

            return (temp1 && temp2);
        }

        private static bool TestString()
        {
            HashTable<string> tableString = new HashTable<string>(10);

            tableString.AddElement("abc", 1);
            tableString.AddElement("a", 2);
            tableString.AddElement("qwerty", 3);
            tableString.AddElement("Abc", 4);

            tableString.DeleteElement(2);

            bool temp1 = (tableString.Contains(3) && tableString.Contains(4)
                && tableString.Contains(1) && !tableString.Contains(2));

            bool temp2 = (tableString.GetValueByKey(3) == "qwerty");

            tableString.DeleteTable();

            return (temp1 && temp2);
        }

        static void Main(string[] args)
        {
            if(TestInt() && TestDouble() && TestString())
            {
                Console.WriteLine("Program works correctly");
            }
            else
            {
                Console.WriteLine("Program doesn't work correctly :(");
            }
        }
    }
}
