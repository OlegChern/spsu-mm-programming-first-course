/*
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace TestOne
{
    class FormatValue
    {

        public string Format(double InValue)
        {
            if (InValue>=0)
            {
                return ((InValue + 25).ToString());
            }

            return ((InValue - 4.5).ToString());
            
        }

        public string Format(string InString)
        {
            if (InString.Length % 2 == 0)
            {
                return ("))0)"+InString+"))0)");
            }

            return ("((9(" + InString + "((9(");

        }

    }
}
*/