using System;


namespace Test1
{
    class Program
    {
        public static bool TestFormatHelper()
        {
            string str1 = FormatHelper.Format("abc", FormattingType.First);
            string str2 = FormatHelper.Format("abc", FormattingType.Second);
            string str3 = FormatHelper.Format(3, FormattingType.First);
            string str4 = FormatHelper.Format(-10, FormattingType.Second);
            string str5 = FormatHelper.Format(2.3, FormattingType.Second);

            return ((str1 == "++abc++") && (str2 == "==abc==") &&
                (str3 == "5") && (str4 == "0") && (str5 == null));
        }

        static void Main(string[] args)
        {
            if(TestFormatHelper())
            {
                Console.WriteLine("Program works correctly");
            }
            else
            {
                Console.WriteLine("Program doesn't work correctly");
            }
        }
    }
}
