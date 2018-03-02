using System;

namespace HomeworkTask01
{
	class Program
	{
		private static void Main(string[] args)
		{
			try
			{
				if (args.Length < 4)
				{
					throw new ArgumentException("Not enough arguments!");
				}

				try
				{
					BMP bmp = new BMP(args[1]);
					BMPFilters.Type type;

					switch (args[2])
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

					bmp.Create(args[3]);
				}
				catch (ArgumentException exception)
				{
					Console.WriteLine('\n' + exception.Message + '\n');
					TryAgain();
				}

			}
			catch (ArgumentException exception)
			{
				Console.WriteLine('\n' + exception.Message + '\n');
				TryAgain();
			}
		}

		private static void TryAgain()
		{
			Console.WriteLine("Please enter: [source path] [filter name] [target path]");
			Console.WriteLine("Available filters:");
			Console.WriteLine("- Gauss");
			Console.WriteLine("- SobelX");
			Console.WriteLine("- SobelY");
			Console.WriteLine("- GrayScale");
			Console.WriteLine("- Average");

			string str = " " + Console.ReadLine();
			string[] words = str.Split(' ');

			Main(words);
		}
	}
}
