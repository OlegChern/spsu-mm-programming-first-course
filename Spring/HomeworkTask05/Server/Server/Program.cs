using System;
using System.Text;

using System.Threading;
using System.Net;
using System.Net.Sockets;

namespace Server
{
	public class Program
	{
		static Server server;
		static Thread thread;

		public static void Main()
		{
			try
			{
				server = new Server();
				thread = new Thread(new ThreadStart(server.StartReceiving));
				thread.Start();
			}
			catch (Exception exception)
			{
				server.Disconnect();
				Console.WriteLine(exception.Message);
			}
		}
	}
}