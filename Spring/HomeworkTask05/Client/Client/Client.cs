using System;
using System.Text;

using System.Threading;
using System.Net;
using System.Net.Sockets;

namespace Client
{
	class Client
	{
		private const int MessageLength = 128;

		private static byte[] IP = { 127, 0, 0, 1 };
		private static int Port = 8151;

		private string name;
		private Socket socket;

		public void Start()
		{
			ReadName();

			try
			{
				// send data about client
				Connect();
				SendString(name);
				socket.Shutdown(SocketShutdown.Both);
				socket.Close();

				// main loop
				while (true)
				{
					Connect();

					SendMessage();
					ReceiveMessage();

					socket.Shutdown(SocketShutdown.Both);
					socket.Close();
				}
			}
			catch (Exception exception)
			{
				Console.WriteLine("> Error: " + exception.Message);
				Console.ReadKey();
			}
			finally
			{
				Disconnect();
			}
		}

		private void ReadName()
		{
			while (true)
			{
				Console.Write("Enter username: ");
				name = "";

				string temp = Console.ReadLine();

				foreach (char c in temp)
				{
					if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
					{
						name += c;
					}
				}

				if (name.Length > 2)
				{
					break;
				}
				else
				{
					Console.WriteLine("Username must contain more than 2 symobls!");
				}
			}

			Console.WriteLine();
		}

		private void Connect()
		{
			IPAddress ip = new IPAddress(IP);
			IPEndPoint ep = new IPEndPoint(ip, Port);

			socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
			socket.Connect(ep);
		}

		// receive message from server
		private void ReceiveMessage()
		{
			Console.WriteLine(ReceiveString());
		}

		private string ReceiveString()
		{
			string message = "";
			byte[] data = new byte[MessageLength];

			do
			{
				int length = socket.Receive(data, MessageLength, SocketFlags.None);
				message += Encoding.ASCII.GetString(data, 0, length);
			}
			while (socket.Available > 0);

			return message;
		}

		// send message to server
		private void SendMessage()
		{
			string format = name + ": ";
			Console.Write(format);

			string message = Console.ReadLine();

			SendString(message);
		}

		private void SendString(string str)
		{
			byte[] data = Encoding.ASCII.GetBytes(str);
			socket.Send(data);
		}

		private void Disconnect()
		{
			socket.Shutdown(SocketShutdown.Both);
			socket.Close();
			socket = null;

			Console.WriteLine("Press any key to exit.");
			Console.ReadKey();
			Environment.Exit(0);
		}
	}
}
