using System;
using System.Collections.Generic;
using System.Text;

using System.Threading;
using System.Net;
using System.Net.Sockets;

namespace Chat
{
	public class Peer
	{
		#region constants
		private const int MessageLength = 256;
		private const int port = 8151;
		#endregion

		#region private properties
		private string name;

		private Socket receiver;
		private Thread receivingThread;

		private List<IPEndPoint> connectedEp = new List<IPEndPoint>();
		#endregion

		#region public methods
		/// <summary>
		/// Creates new peer
		/// </summary>
		public Peer()
		{
			InitPeer();
		}
		#endregion

		#region initialization methods
		private void InitPeer()
		{
			ReadName();
			ReadIP();

			SendMessage(name + " connected.");

			InitReceiver();
			Send();
		}

		// connect to peer with given ip address
		private void Connect(string ipString)
		{
			IPAddress ip = IPAddress.Parse(ipString);
			IPEndPoint remoteEp = new IPEndPoint(ip, port);

			// make sure that there is no same endpoint
			bool same = false;
			foreach (IPEndPoint ep in connectedEp)
			{
				if (ep.ToString() == remoteEp.ToString())
				{
					same = true;
				}
			}

			if (!same)
			{
				// add to list of all endpoints in current space
				connectedEp.Add(remoteEp);
			}

			// to do: 
			// must receive all IPs from peer we are connecting to,
			// connect to them and add local peer to their lists
		}

		private void InitReceiver()
		{
			receiver = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

			// additional thread for receiving messages
			receivingThread = new Thread(new ThreadStart(Receive));
			receivingThread.IsBackground = true;
			receivingThread.Start();
		}
		#endregion

		#region receiving and sending
		private void Receive()
		{
			try
			{
				// get local end point
				IPHostEntry ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());

				// just init
				byte[] byteIp = { 192, 168, 0, 1 };
				IPEndPoint localEp = new IPEndPoint(new IPAddress(byteIp), port);

				// actual ip
				foreach (IPAddress ip in ipHostInfo.AddressList)
				{
					if (ip.AddressFamily == AddressFamily.InterNetwork)
					{
						localEp = new IPEndPoint(ip, port);
						break;
					}
				}

				receiver.Bind(localEp);
				receiver.Listen(16);

				// data array always has same length
				byte[] data = new byte[MessageLength];

				while (true)
				{
					// wait for incoming message
					Socket handler = receiver.Accept();

					string message = string.Empty;

					do
					{
						int length = handler.Receive(data, MessageLength, SocketFlags.None);
						message += Encoding.ASCII.GetString(data, 0, length);
					}
					while (handler.Available > 0);

					Console.WriteLine(message);

					handler.Close();
					handler.Shutdown(SocketShutdown.Both);
				}

			}
			catch (SocketException exception)
			{
				Console.WriteLine("> Receiver SocketException: " + exception.Message);
			}
			catch (Exception exception)
			{
				Console.WriteLine("> Exception: " + exception.Message);
				Console.ReadKey();
			}
		}

		private void Send()
		{
			// read message from console
			string message = Console.ReadLine();

			
			// exit code
			if (message == "/q" || message == "/quit")
			{
				Quit();
				message = string.Empty;
			}

			if (message.Length != 0)
			{
				// format message before sending
				message = name + ": " + message;

				// local print
				Console.WriteLine(message);

				// send to other peers
				SendMessage(message);
			}

			// sending loop
			Send();
		}

		private void SendMessage(string message)
		{
			try
			{
				// send data for each socket
				foreach (IPEndPoint ep in connectedEp)
				{
					using (Socket sender = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
					{
						// connect to endpoint
						sender.Connect(ep);

						// convert and send data to it
						byte[] data = Encoding.ASCII.GetBytes(message);
						sender.Send(data);

						sender.Shutdown(SocketShutdown.Both);
						sender.Close();
					}
				}

			}
			catch (SocketException exception)
			{
				Console.WriteLine("> Sender SocketException: " + exception.Message);
			}
			catch (Exception exception)
			{
				Console.WriteLine("> Exception: " + exception.Message);
				Console.ReadKey();
			}
		}
		#endregion

		#region additional
		private void ReadName()
		{
			while (true)
			{
				Console.Write("Enter username: ");
				name = string.Empty;

				string temp = Console.ReadLine();

				foreach (char c in temp)
				{
					if ((c < '0' || c > '9') && (c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
					{
						Console.WriteLine("Username must contain only symbols: a-z, A-Z, 0-9!");
						name = string.Empty;

						break;
					}

					name += c;
				}

				if (name.Length > 2)
				{
					break;
				}
				else
				{
					Console.WriteLine("Username must contain more than 2 symbols!");
				}
			}
		}

		private void ReadIP()
		{
			string ip = string.Empty;

			while (true)
			{
				Console.Write("Connect to exact IP? Y / N: ");
				string str = Console.ReadLine();

				if (str == "N" || str == "n")
				{
					return;
				}
				else if (str != "Y" && str != "y")
				{
					continue;
				}

				Console.Write("Enter IP to connect: ");

				string temp = Console.ReadLine();
				int dots = 0;

				foreach (char c in temp)
				{
					if (c >= '0' && c <= '9')
					{
						ip += c;
					}
					else if (c == '.' || c == ' ' || c == ',')
					{
						ip += '.';
						dots++;
					}
					else
					{
						Console.WriteLine("IP must contain only symbols: 0-9, ':', '.'!");
						dots = 0;

						break;
					}
				}

				if (dots != 3)
				{
					Console.WriteLine("IP must have 4 32-bit numbers!");
					continue;
				}

				IPAddress test;
				if (IPAddress.TryParse(ip, out test))
				{
					break;
				}
				else
				{
					Console.WriteLine("Wrong IP!");
					continue;
				}
			}

			Console.WriteLine();

			Connect(ip);
		}

		private void Quit()
		{
			while (true)
			{
				Console.Write("Do you want to quit? Y / N: ");
				string str = Console.ReadLine();

				if (str == "Y" || str == "y")
				{
					Free();
					break;
				}
				else if (str == "N" || str == "n")
				{
					return;
				}
			}
		}

		private void Free()
		{
			receiver.Shutdown(SocketShutdown.Both);
			receiver.Close();

			receiver.Dispose();
		}
		#endregion

		#region destructor
		~Peer()
		{
			Free();
		}
		#endregion
	}
}
