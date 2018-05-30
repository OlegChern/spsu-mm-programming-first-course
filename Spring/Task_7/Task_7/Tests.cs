using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Task_7
{
    public class Tests
    {
        public bool FirstTest()
        {
            WeakHashTable<int, string> table = new WeakHashTable<int, string>(1500);
            table.Add(22,"мечтающую на размягченном мозгу");
            table.Add(26,"У меня в душе ни одного седого волоса,");
            table.Add(11,"Вашу мысль, ");
            table.Add(3,"на засаленной кушетке,");
            table.Add(13,"как выжиревший лакей");
            table.Add(15,"нахальный и едкий.");
            table.Add(4,"сердца лоскут;");
            table.Add(17,"и старческой нежности нет в ней!");
            table.Add(24,"буду дразнить об окровавленный");
            table.Add(5,"досыта изъиздеваюсь,");

            table.Remove(26);
            table.Remove(17);

            bool isCorrectRemove = !table.Contains(26) && !table.Contains(17);

            bool isCorrectContains = (table.Contains(22) &&
                                  table.Contains(11) &&
                                  table.Contains(3) &&
                                  table.Contains(13) &&
                                  table.Contains(15) &&
                                  table.Contains(4) &&
                                  table.Contains(24) &&
                                  table.Contains(5));

            bool isCorrectGetValue = (table.GetValue(15) == "нахальный и едкий.");

            Thread.Sleep(2000);
            GC.Collect();
            bool isCorrectStore = !(table.Contains(22) ||
                                      table.Contains(11) ||
                                      table.Contains(3) ||
                                      table.Contains(13) ||
                                      table.Contains(15) ||
                                      table.Contains(4) ||
                                      table.Contains(24) ||
                                      table.Contains(5));

            return isCorrectStore && isCorrectContains && isCorrectGetValue && isCorrectRemove;
        }


    }
}
