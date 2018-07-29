using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Curves
{
    public abstract class ACurve
    {
        public string Name { get; protected set; }

        public string Equation { get; protected set; }

        public float StartPointX { get; protected set; }

        public float EndPointX { get; protected set; }

        public ACurve(float start, float end)
        {
            if (start > end)
            {
                StartPointX = -1000;
                EndPointX = 1000;
            }
            else
            {
                StartPointX = start;
                EndPointX = end;
            }
        }

        public abstract List<float> FindSolutions(float x);

        public override string ToString()
        {
            string str = Equation + " (" + Name + ")";
            return str;
        }

        public void ChangeInterval(float newStart, float newEnd)
        {
            if(newStart > newEnd)
            {
                return;
            }
            StartPointX = newStart;
            EndPointX = newEnd;
        }

        public List<PointF>[] GetPoints(int pointsInSegment)
        {
            List<PointF> resultNegative = new List<PointF>();
            List<PointF> resultPositive = new List<PointF>();

            if (StartPointX > EndPointX)
            {
                return null;
            }

            float step = (EndPointX - StartPointX) / pointsInSegment / 1000;
            for (float x = StartPointX; x < EndPointX; x += step)
            {
                List<float> resultY = FindSolutions(x / pointsInSegment);
                foreach(var y in resultY)
                {
                    float X = x;
                    float Y = y * pointsInSegment;
                    if(Math.Abs(Y) < 2f)
                    {
                        Y = 0;
                    }
                    if (Y <= 0)
                    {
                        resultNegative.Add(new PointF(X, Y));
                    }
                    if(Y >= 0)
                    {
                        resultPositive.Add(new PointF(X, Y));
                    }
                }
            }
            List<PointF>[] result = new List<PointF>[] { resultNegative, resultPositive };
            return result;
        }
    }
}
