using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestOne
{
    class NewFormatValue : IFormattable
    {
        private string _str;
        private double _value;

        public string ToString(string format, IFormatProvider provider)
        {
            if (provider == null) provider = CultureInfo.CurrentCulture;
            switch (format.ToUpperInvariant())
            {
                case "0": return ("((9(" +_str+ "))0)");
                case "1": return ("###" + _str + "###");
                case "2": return ("+2+" + _str + "+2+");
                case "3": return ("<3<3<3<3" + _str + "<3<3<3<3<3");
                case "4": return ("<<<<" + _str + ">>>>");
                case "5": return ("^^ " + _str + " -_-");


                case "+": return ((_value + 234.423).ToString());
                case "-": return ((_value - 324.534).ToString());
                default:
                    throw new FormatException(String.Format("The {0} format string is not supported.", format));
            }
        }
     
        public string Format(string InStr)
        {
            _str = InStr;
            return ToString((_str.Length%6).ToString(),null);
        }

        public string Format(double InVal)
        {
            _value = InVal;
            string sign = _value >= 0 ? "+" : "-";
            return ToString(sign,null);
        }



    }
}
