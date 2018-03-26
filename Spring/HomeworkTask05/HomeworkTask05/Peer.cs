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
        #region enums
        public enum MessageType
        {
            Null = 0,
            Message = 1,
            IP = 2,
            IPRequest
        }
        #endregion

        #region constants
        private const int MessageLength = 256;
		private const int port = 8151;
		#endregion

		#region private fields
		private string name;
		private bool isRunning;

		private Thread receivingThread;

        private IPEndPoint localEp = null;
        private List<IPEndPoint> connectedEp = new List<IPEndPoint>();
		#endregion

		#region public methods
		/// <summary>
		/// Creates new peer
		/// </summary>
		public Peer()
		{
			ReadName();
		}

		public void Start()
		{
			isRunning = true;

            Send(name + " connected.", MessageType.Message);

			InitReceiver();
            InitSender();
		}
		#endregion

		#region main methods 
		private void InitReceiver()
		{
			// additional thread for receiving messages
			receivingThread = new Thread(new ThreadStart(ReceiveLoop));
			receivingThread.IsBackground = true;
			receivingThread.Start();
		}

        private void InitSender()
        {
            SendLoop();
        }

        #region receiving
        private void ReceiveLoop()
		{
			Socket receiver = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                // get local end point
                foreach (IPAddress ip in Dns.GetHostEntry(Dns.GetHostName()).AddressList)
                {
                    if (ip.AddressFamily == AddressFamily.InterNetwork)
                    {
                        localEp = new IPEndPoint(ip, port);
                        Console.WriteLine("Your IPv4: " + ip);

                        break;
                    }
                }

                if (localEp == null)
                {
                    byte[] byteIp = { 192, 168, 0, 1 };
                    localEp = new IPEndPoint(new IPAddress(byteIp), port);
                }

                receiver.Bind(localEp);
                receiver.Listen(16);

				// data array always has same length
				byte[] data = new byte[MessageLength];

				while (isRunning)
				{
					// wait for incoming message
					using (Socket handler = receiver.Accept())
					{
						string message = string.Empty;

                        do
						{
							int length = handler.Receive(data, MessageLength, SocketFlags.None);
							message += Encoding.ASCII.GetString(data, 0, length);
						}
						while (handler.Available > 0);

                        #region process message type
                        MessageType type = MessageType.Null;

                        if (message != string.Empty)
                        {
                            type = (MessageType)message[0];
                            message = message.Remove(0, 1);
                        }

                        switch (type)
                        {
                            case MessageType.Message:
                                {
                                    Console.WriteLine(message);
                                    break;
                                }
                            case MessageType.IPRequest:
                                {
                                    IPEndPoint remoteEp = (IPEndPoint)handler.RemoteEndPoint;
                                    IPAddress ip = remoteEp.Address;

                                    Connect(ip);

                                    // send all connected endpoints to all peers
                                    foreach (IPEndPoint ep in connectedEp)
                                    {
                                        Send(ep.Address.ToString(), MessageType.IP);
                                    }

                                    break;
                                }
                            case MessageType.IP:
                                {
                                    string[] ipSplitted = message.Split('.');

                                    if (ipSplitted.Length > 4)
                                    {
                                        // read ip
                                        byte[] ipBytes = new byte[4];

                                        for (int i = 0; i < 4; i++)
                                        {
                                            ipBytes[i] = byte.Parse(ipSplitted[i]);
                                        }

                                        IPAddress ip = new IPAddress(ipBytes);
                                        Connect(ip);
                                    }

                                    break;
                                }
                        }
                        #endregion

                        handler.Shutdown(SocketShutdown.Both);
						handler.Close();
					}
				}

				receiver.Shutdown(SocketShutdown.Both);
				receiver.Close();

				receiver.Dispose();
			}
			catch (SocketException exception)
			{
				Console.WriteLine("> Receiver SocketException: " + exception.Message);
				Console.ReadKey();
			}
			catch (Exception exception)
			{
				Console.WriteLine("> Receiver Exception: " + exception.Message);
				Console.ReadKey();
			}
			finally
			{
				if (receiver != null)
				{
					if (receiver.Connected)
					{
						receiver.Shutdown(SocketShutdown.Both);
						receiver.Close();
					}

					receiver.Dispose();
				}
			}
		}
        #endregion

        #region sending
        private void SendLoop()
		{
			while (isRunning)
			{
				string format = name + ": ";

                // local print
                // Console.Write(format);

                // read message from console
                string message = Console.ReadLine();

				if (message.Length > 1)
				{
					// commands
					if (message[0] == '/')
					{
						if (message[1] == 'q')
						{
							Quit();
						}
						else if (message[1] == 'c')
						{
							ProcessIP(message);
						}
                        else if (message[1] == 'd')
                        {
                            ProcessIP(message);
                        }
                    }
					else
					{
						// format message before sending
						message = format + message;

						// send to other peers
						Send(message, MessageType.Message);
					}
				}
			}
		}

		private void Send(string message, MessageType type)
		{
			try
			{
                // using first byte as message type
                byte[] temp = Encoding.ASCII.GetBytes(message);
                int tempLength = temp.Length;

                byte[] data = new byte[tempLength + 1];

                data[0] = (byte)type;
                Array.Copy(temp, 0, data, 1, tempLength);

                Send(data);
			}
			catch (SocketException exception)
			{
				Console.WriteLine("> Sender SocketException: " + exception.Message);
				Console.ReadKey();
			}
			catch (Exception exception)
			{
				Console.WriteLine("> Sender Exception: " + exception.Message);
				Console.ReadKey();
			}
        }

        private void Send(byte[] data)
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

                        sender.Send(data);

                        sender.Shutdown(SocketShutdown.Both);
                        sender.Close();
                    }
                }

            }
            catch (SocketException exception)
            {
                Console.WriteLine("> Sender SocketException: " + exception.Message);
                Console.ReadKey();
            }
            catch (Exception exception)
            {
                Console.WriteLine("> Sender Exception: " + exception.Message);
                Console.ReadKey();
            }
        }

        private void SendIPRequest()
        {
            try
            {
                byte[] data = { (byte)MessageType.IPRequest };
                Send(data);
            }
            catch (SocketException exception)
            {
                Console.WriteLine("> Sender SocketException: " + exception.Message);
                Console.ReadKey();
            }
            catch (Exception exception)
            {
                Console.WriteLine("> Sender Exception: " + exception.Message);
                Console.ReadKey();
            }
        }
        #endregion

        // connect to peer with given ip address
        private void Connect(IPAddress ip)
        {
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

            // request from all peers to send their IP's
            SendIPRequest();
        }
        #endregion

        #region additional
        private void ReadName()
		{
			while (true)
			{
				Console.Write("> Enter username: ");

				bool success = true;

				string temp = Console.ReadLine();
				name = string.Empty;

				foreach (char c in temp)
				{
					if ((c < '0' || c > '9') && (c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
					{
						Console.WriteLine("> Username must contain only symbols: a-z, A-Z, 0-9!");
						success = false;

						break;
					}

					name += c;
				}

				if (!success)
				{
					continue;
				}

				if (name.Length > 2)
				{
					break;
				}
				else
				{
					Console.WriteLine("> Username must contain more than 2 symbols!");
				}
			}
		}

        // process ip to connect to it
		private void ProcessIP(string rawMessage)
		{
			string ipString;
			string[] splitted = rawMessage.Split(' ');

			if (splitted.Length < 2)
			{
				Console.WriteLine("> Not enough arguments!");
				return;
			}

			// expecting ip after space
			ipString = splitted[1];

			string temp = string.Empty;
			int dots = 0;

			foreach (char c in ipString)
			{
				if (c >= '0' && c <= '9')
				{
					temp += c;
				}
				else if (c == '.' || c == ',')
				{
					temp += '.';
					dots++;
				}
				else
				{
					Console.WriteLine("> IPv4 must contain only symbols: 0-9, ':', '.'!");
					dots = 0;

					return;
				}
			}

			if (dots != 3)
			{
				Console.WriteLine("> IPv4 must have 4 32-bit numbers!");
				return;
			}

			IPAddress ip;
			if (!IPAddress.TryParse(temp, out ip))
			{
				Console.WriteLine("> Wrong IPv4!");
				return;
			}

			Console.WriteLine();
			Connect(ip);
		}

		private void Quit()
		{
			while (true)
			{
				Console.Write("> Do you want to quit? Y / N: ");
				ConsoleKeyInfo key = Console.ReadKey();

				if (key.Key == ConsoleKey.Y)
				{
					Free();
					break;
				}

                if (key.Key == ConsoleKey.N)
                {
                    return;
				}
			}
		}

		private void Free()
		{
			isRunning = false;
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
