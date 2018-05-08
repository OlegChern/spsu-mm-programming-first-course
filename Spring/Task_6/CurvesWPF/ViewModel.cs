using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CurvesMath;
using CurvesMath.Curves;

namespace CurvesWPF
{
    public class ViewModel
    {
        public static List<ACurve> CurvesList { get; private set; }

        public static ACurve ChoosenCurve { get; set; }


        public ViewModel()
        {
            CurvesList = new List<ACurve> { new EllipseCurve(9, 4), new HyperbolaCurve(3, 2), new ParabolaCurve(2) };
        }

    }
}
