using task2Lib;

namespace task2LibImpl
{
    public class CustomTank : AbstractTank
    {
        public CustomTank(string name, string manufacturer, double mass, double width, double length, double mainCaliber, int maxSpeed)
            : base(name, manufacturer, mass, width, length, mainCaliber, maxSpeed)
        {
        }
    }
}
