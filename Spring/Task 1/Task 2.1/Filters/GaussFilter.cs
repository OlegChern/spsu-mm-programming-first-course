using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Filter
{
    public class GaussFilter : Filter
    {
        public override double[,] Parametr
        {
            get
            {
                return new double[3, 3] {{ 1.0 / 16, 2.0 / 16, 1.0 / 16},
                                         { 2.0 / 16, 4.0 / 16, 2.0 / 16},
                                         { 1.0 / 16, 2.0 / 16, 1.0 / 16}};
            }
        }
    }
}
