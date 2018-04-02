namespace Test1
{
    public class FormatString : AFormat<string>
    {
        public override string First { get; } = "++";

        public override string Second { get; } = "==";

        public FormatString(string value) : base(value)
        { }

        public override string Format(FormattingType formattingType)
        {
            if(formattingType == FormattingType.First)
            {
                string newStr1 = First + value + First;
                return newStr1;
            }
            string newStr2 = Second + value + Second;
            return newStr2;
        }
    }
}
