using System;
using System.Collections.Generic;

using HashTable;

namespace HomeworkTask04
{
	static class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine("Hash table test.");
			Console.WriteLine("Collision resolution: separate chaining with list head cells.");

			HashTable<int> table = new HashTable<int>(4,2);

			Console.WriteLine("\nAdding elements...");
			// adding test
			table.Add("WADX", 1248);
			table.Add("EDSF", 1250);
			table.Add("ZXC", 1252);
			table.Add("ASDX", 1248);
			table.Add("ZXCV", 1250);
			table.Add("ASDF", 1254);
			table.Add("ZXCV", 1256);
			table.Add("ASDFDS", 1258);
			table.Add("ASDFWD", 1258);
            table.Add("WADX", 1248);
            table.Add("WADX", 1248);
            table.Add("WADX", 1248);
            table.Add("WADX", 1248);
            table.Add("WADX", 1248);
            table.Add("WADX", 1248);
            table.Add("WADX", 1248);
            table.Add("WADX", 1248);
            table.Add("WADX", 1248);
            table.Add("WADX", 1248);

            table.Print();

			// rebalancing test
			Console.WriteLine("\nAdding and rebalancing elements...");

			table.Add("WASD", 1254);
			table.Add("WASD", 1256);
			table.Add("WASD", 1256);

			table.Print();

			// removing test
			Console.WriteLine("\nRemoving elements with keys \"ASDFDS\" and \"ASDFWD\"...");

			table.Remove("ASDFDS");
			table.Remove("ASDFWD");

			table.Print();

			// finding test
			string[] keys = { "ZXCV", "TEST" };

			foreach (string key in keys)
			{
				int value;

				if (table.Find(key, out value))
				{
					Console.WriteLine("Value of element with key \"" + key + "\": " + value);
				}
				else
				{
					Console.WriteLine("Value of element with key \"" + key + "\" not found");
				}
			}
		}
	}
}
