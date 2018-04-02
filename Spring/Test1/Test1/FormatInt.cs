namespace Test1
{
    public class FormatInt : AFormat<int>
    {
        public override int First { get; } = 2;

        public override int Second { get; } = 10;

        public FormatInt(int value) : base(value)
        { }

        public override string Format(FormattingType formattingType)
        {
            if (formattingType == FormattingType.First)
            {
                string newStr1 = (value + First).ToString();
                return newStr1;
            }
            string newStr2 = (value + Second).ToString();
            return newStr2;
        }
    }
}
