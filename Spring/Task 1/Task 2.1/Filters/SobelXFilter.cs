using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Filter
{
    public class SobelXFilter : Filter
    {
        public override double[,] Parametr
        {
            get
            {
                return new double[3, 3] {{ -1.0, 0, 1.0},
                                         { -2.0, 0, 2.0},
                                         { -1.0, 0, 1.0}};
            }
        }
    }
}
