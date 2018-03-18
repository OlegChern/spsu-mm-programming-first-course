using System;
using System.Text;
using System.Collections.Generic;

using System.Threading;
using System.Net;
using System.Net.Sockets;

namespace Server
{
	public class Server
	{
		public static byte[] IP = { 127, 0, 0, 1 };
		public static int Port = 8151;

		public static int MessageLength = 128;

		private Socket socket;
		private List<Client> clients = new List<Client>();

		public int ClientsCount
		{
			get
			{
				return clients.Count;
			}
		}

		public void StartReceiving()
		{
			try
			{
				socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

				IPAddress ip = new IPAddress(IP);
				IPEndPoint ep = new IPEndPoint(ip, Port);

				socket.Bind(ep);
				socket.Listen(16);

				Console.WriteLine("Server started.");

				while (true)
				{
					Socket clientSocket = socket.Accept();
					Client client = new Client(this, clientSocket);

					Thread clientThread = new Thread(new ThreadStart(client.StartReceiving));
					clientThread.Start();
				}
			}
			catch (Exception exception)
			{
				Console.WriteLine("> Error: " + exception.Message);
				Console.ReadKey();
			}
		}

		public void AddClient(Client client)
		{
			if (client != null)
			{
				clients.Add(client);
			}
		}

		public void RemoveClient(Client client)
		{
			if (client != null)
			{
				client.Close();
				clients.Remove(client);
			}
		}

		// send to all clients
		public void SendMessageToAll(string message, int id)
		{
			Console.WriteLine(message);

			byte[] data = Encoding.ASCII.GetBytes(message);

			foreach (Client client in clients)
			{
				if (client.ID != id +1)
				{
					client.SendMessage(message);
				}
			}
		}

		public void Disconnect()
		{
			socket.Shutdown(SocketShutdown.Both);
			socket.Close();

			foreach (Client client in clients)
			{
				client.Close();
			}

			Console.WriteLine("Press any key to exit.");
			Console.ReadKey();
			Environment.Exit(0);
		}
	}
}