using System;
using System.Text;
using System.Collections.Generic;

using System.Threading;
using System.Net;
using System.Net.Sockets;

namespace Server
{
	public class Client
	{
		private int id;
		private string name;
		private Socket socket;
		private Server server;

		public int ID
		{
			get
			{
				return id;
			}
		}

		public Client(Server _server, Socket _socket)
		{
			server = _server;
			socket = _socket;
			id = server.ClientsCount;
			server.AddClient(this);
		}

		public void StartReceiving()
		{
			try
			{
				// first message is name
				name = ReceiveMessage();
				server.SendMessageToAll(name + " connected.", id);

				// receive messages from client
				while (true)
				{
					Thread.Sleep(1000);

					try
					{
						string message = name + ": " + ReceiveMessage();
						server.SendMessageToAll(message, id);
					}
					catch
					{
						// if there is any exception then client is disconnected

						string message = name + " disconnected.";
						server.SendMessageToAll(message, id);

						break;
					}
				}
			}
			catch (Exception exception)
			{
				Console.WriteLine("> Error: " + exception.Message);
				// Console.ReadKey();
			}
			finally
			{
				server.RemoveClient(this);
				Close();
			}
		}

		// receive message from client
		public string ReceiveMessage()
		{
			string message = "";
			byte[] data = new byte[Server.MessageLength];

			do
			{
				int length = socket.Receive(data, Server.MessageLength, SocketFlags.None);
				message += Encoding.ASCII.GetString(data, 0, length);

			} while (socket.Available > 0);

			return message;
		}

		// send message to client
		public void SendMessage(string message)
		{
			byte[] data = Encoding.ASCII.GetBytes(message);
			socket.Send(data);
		}

		public void Close()
		{
			socket.Shutdown(SocketShutdown.Both);
			socket.Close();
			socket = null;
		}
	}
}
