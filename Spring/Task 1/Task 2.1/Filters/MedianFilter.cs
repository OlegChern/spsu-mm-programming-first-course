using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Filter
{
    public class MedianFilter : Filter
    {
        public override double[,] Parametr
        {
            get
            {
                return new double[3, 3]{ {1.0 / 9, 1.0 / 9, 1.0 / 9},
                                         {1.0 / 9, 1.0 / 9, 1.0 / 9},
                                         {1.0 / 9, 1.0 / 9, 1.0 / 9} };
            }
        }
    }
}
