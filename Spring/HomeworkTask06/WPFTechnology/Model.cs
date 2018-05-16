using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Collections.ObjectModel;

using AlgebraicCurveLibrary;
using AlgebraicCurveLibrary.Exapmles;

namespace WPFTechnology
{
    public class Model
    {
        public delegate void Enable(bool enabled);

        public event Enable EnableScaleUpBtn;
        public event Enable EnableScaleDownBtn;

        const float ScaleMultiplier = 1.25f;
        const int MaxScalePower = 10;
        const int MinScalePower = -10;

        private List<CurveBase> curves;
        private CurveBase selected;

        private int ScalePower;

        public CurveBase[] CurvesArray
        {
            get
            {
                return curves.ToArray();
            }
        }
        
        public CurveBase SelectedCurve
        {
            get
            {
                return selected;
            }
            set
            {
                selected = value;
            }
        }

        public Model()
        {
            curves = new List<CurveBase>();

            curves.Add(new Line());
            curves.Add(new Circle());
            curves.Add(new Ellipse());
            curves.Add(new Parabola());
            curves.Add(new Hyperbola());
        }

        #region scaling
        /// <summary>
        /// Scaling up event
        /// </summary>
        public void ScaleUp(object sender, EventArgs e)
        {
            if (ScalePower <= MinScalePower)
            {
                EnableScaleDownBtn(true);
            }

            ScalePower++;
            ScaleCurves(ScaleMultiplier);

            if (ScalePower >= MaxScalePower)
            {
                EnableScaleUpBtn(false);
            }
        }

        /// <summary>
        /// Scaling down event
        /// </summary>
        public void ScaleDown(object sender, EventArgs e)
        {
            if (ScalePower >= MaxScalePower)
            {
                EnableScaleUpBtn(true);
            }

            ScalePower--;
            ScaleCurves(1 / ScaleMultiplier);

            if (ScalePower <= MinScalePower)
            {
                EnableScaleDownBtn(false);
            }
        }

        private void ScaleCurves(float scale)
        {
            /*this.scale *= scale;

            Matrix newTransform = originalTransform.Clone();
            newTransform.Scale(this.scale, this.scale);

            graphics.Transform = newTransform;
            SetPenWidth(1 / this.scale);

            Draw();*/
        }
        #endregion
    }
}
