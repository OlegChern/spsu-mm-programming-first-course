using System;

namespace TestWork
{
    public class StringFormater: IFormater<string>
    {
        public FormatMode Mode { get; }

        public StringFormater(FormatMode mode)
        {
            if (!Enum.IsDefined(typeof(FormatMode), mode))
            {
                throw new ArgumentOutOfRangeException(nameof(mode));
            }

            Mode = mode;
        }
        
        public string Format(string arg)
        {
            switch (Mode)
            {
                case FormatMode.AddTwo:
                    return "++" + arg + "++";
                case FormatMode.AddFour:
                    return "++++" + arg + "++++";
                case FormatMode.AddSix:
                    return "++++++" + arg + "++++++";
                case FormatMode.SubstractSix:
                    return "------" + arg + "------";
                case FormatMode.SubstractFour:
                    return "----" + arg + "----";
                case FormatMode.SubstractTwo:
                    return "--" + arg + "--";
                case FormatMode.None:
                    return arg;
                default:
                    throw new ArgumentOutOfRangeException(nameof(arg));
            }
        }
    }
}
