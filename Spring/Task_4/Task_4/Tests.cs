using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_4
{
    internal static class Tests
    {
        internal static bool TestInt()
        {
            HashTable<int> table = new HashTable<int>(10);
            Random myR = new Random();
            List<int> testKeysList = new List<int>();

            for (int i = 0; i < 100; ++i)
            {
                int temp = myR.Next(1000);
                testKeysList.Add(temp);
                table.AddElement(temp, temp);
            }

            bool checkContains = true;
            bool checkValueByKey = true;
            bool checkDelete = true;

            for (int i = 0; i < 100; ++i)
            {
                checkContains = checkContains && table.Contains(testKeysList[i]);
            }

            for (int i = 0; i < 25; ++i)
            {
                checkValueByKey = checkValueByKey && table.GetValueByKey(testKeysList[i]) == testKeysList[i];

            }

            for (int i = 0; i < 50; ++i)
            {
                table.DeleteElement(testKeysList[i]);
                checkDelete = checkDelete && !table.Contains(testKeysList[i]);
                testKeysList.RemoveAt(i);
            }

            table.DeleteTable();

            return (checkContains && checkDelete && checkValueByKey);
        }

        internal static bool TestDouble()
        {
            HashTable<double> table = new HashTable<double>(10);
            Random myR = new Random();
            List<int> testKeysList = new List<int>();

            for (int i = 0; i < 100; ++i)
            {
                int temp = myR.Next(1000);
                testKeysList.Add(temp);
                table.AddElement(temp + 0.5, temp);
            }

            bool checkContains = true;
            bool checkValueByKey = true;
            bool checkDelete = true;

            for (int i = 0; i < 100; ++i)
            {
                checkContains = checkContains && table.Contains(testKeysList[i]);
            }

            for (int i = 0; i < 25; ++i)
            {
                checkValueByKey = checkValueByKey && table.GetValueByKey(testKeysList[i]) == testKeysList[i] + 0.5;

            }

            for (int i = 0; i < 50; ++i)
            {
                table.DeleteElement(testKeysList[i]);
                checkDelete = checkDelete && !table.Contains(testKeysList[i]);
                testKeysList.RemoveAt(i);
            }

            table.DeleteTable();

            return (checkContains && checkValueByKey);
        }

        internal static bool TestString()
        {
            HashTable<string> tableString = new HashTable<string>(10);

            tableString.AddElement("мечтающую на размягченном мозгу", 22);
            tableString.AddElement("У меня в душе ни одного седого волоса,", 26);
            tableString.AddElement("Вашу мысль, ", 11);
            tableString.AddElement("на засаленной кушетке,", 3);
            tableString.AddElement("как выжиревший лакей", 13);
            tableString.AddElement("нахальный и едкий.", 15);
            tableString.AddElement("сердца лоскут;", 4);
            tableString.AddElement("и старческой нежности нет в ней!", 17);
            tableString.AddElement("буду дразнить об окровавленный", 24);
            tableString.AddElement("досыта изъиздеваюсь,", 5);

            tableString.DeleteElement(26);
            tableString.DeleteElement(17);

            bool checkDelete = !tableString.Contains(26) && !tableString.Contains(17);

            bool checkContains = (tableString.Contains(22) &&
                                  tableString.Contains(11) &&
                                  tableString.Contains(3) &&
                                  tableString.Contains(13) &&
                                  tableString.Contains(15) &&
                                  tableString.Contains(4) &&
                                  tableString.Contains(24) &&
                                  tableString.Contains(5));

            bool checkGetValueByKey = (tableString.GetValueByKey(15) == "нахальный и едкий.");

            tableString.DeleteTable();

            return (checkDelete && checkContains && checkGetValueByKey);
        }
        
    }
}
