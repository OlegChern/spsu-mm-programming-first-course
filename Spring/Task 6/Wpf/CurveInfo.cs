using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MathInfo;

namespace Wpf
{
    public class CurveInfo

    {
        public static Curve BoxCurve { get; set; }

        public List<Curve> ListCurves { get; set; }

        public CurveInfo()
        {
            ListCurves = new List<Curve>() { new Ellips(), new Hyperbola(), new Parabola() };
        }
    }
}
