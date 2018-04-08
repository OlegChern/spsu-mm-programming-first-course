using System;

namespace HomeworkTask01
{
	class Program
    {
        // Enter: 
        // [source path] [filter name] [target path]

        // Available filters:
        // - Gauss
		// - SobelX
		// - SobelY
		// - GrayScale
		// - Average

		private static void Main(string[] args)
		{
			try
			{
				if (args.Length < 3)
				{
					throw new ArgumentException("Not enough arguments!");
				}

				try
				{
					BMP bmp = new BMP();
                    bmp.Load(args[0]);

					BMPFilters.Type type;

					switch (args[1])
					{
						case "Gauss":
							{
								type = BMPFilters.Type.Gauss;
								break;
							}
						case "SobelX":
							{
								type = BMPFilters.Type.SobelX;
								break;
							}
						case "SobelY":
							{
								type = BMPFilters.Type.SobelY;
								break;
							}
						case "GrayScale":
							{
								type = BMPFilters.Type.GrayScale;
								break;
							}
						case "Average":
							{
								type = BMPFilters.Type.Average;
								break;
							}
						default:
							{
								throw new ArgumentException("Wrong filter name!");
							}
					}

					BMPFilters.ProcessBMP(bmp, type);

					bmp.Copy(args[2]);
				}
				catch (ArgumentException exception)
				{
					Console.WriteLine('\n' + exception.Message + '\n');
				}

			}
			catch (ArgumentException exception)
			{
				Console.WriteLine('\n' + exception.Message + '\n');
			}
		}
	}
}
