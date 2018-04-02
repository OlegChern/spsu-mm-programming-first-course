namespace Test1
{
    public class FormatHelper
    {
        public static string Format(object message, FormattingType formattingType)
        {
            if(message is string)
            {
                return new FormatString(message as string).Format(formattingType);
            }
            if (message is int)
            {
                return new FormatInt((int)message).Format(formattingType);
            }
            return null;
        }
    }
}
