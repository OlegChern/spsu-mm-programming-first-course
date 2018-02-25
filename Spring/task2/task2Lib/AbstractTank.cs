using static task2Lib.Util;

namespace task2Lib
{
    public abstract class AbstractTank
    {
        public string Name { get; }
        public string Manufacturer { get; }
        public double Mass { get; } // tons
        public double Width { get; } // meters
        public double Length { get; } // meters
        public double MainCaliber { get; } // mm
        public int MaxSpeed { get; } // km/h

        public AbstractTank(string name, string manufacturer, double mass, double width, double length, double mainCaliber, int maxSpeed)
        {
            Name = name;
            Manufacturer = manufacturer;
            Mass = mass;
            Width = width;
            Length = length;
            MainCaliber = mainCaliber;
            MaxSpeed = maxSpeed;
        }

        public virtual string GetFullInfo() => $"Name: {Name}{n}" +
            $"Manufacturer: {Manufacturer}{n}" +
            $"Mass: {Mass} tons{n}" +
            $"Width: {Width} m{n}" +
            $"Length: {Length} m{n}" +
            $"Main gun caliber: {MainCaliber} mm{n}" +
            $"Max speed: {MaxSpeed} km/h{n}";
    }
}
