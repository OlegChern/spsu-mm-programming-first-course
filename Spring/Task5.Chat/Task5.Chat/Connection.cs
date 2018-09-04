using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;

namespace Task5.Chat
{
    public static class Connection
    {
        public static Client CreateClient()
        {
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            IPEndPoint localIpEndPoint = null;
            bool correctStart = false;
            while (!correctStart)
            {
                Console.Write("Input your port ");
                int port = UserInterface.ReadPort();
                try
                {
                    foreach (IPAddress temp in Dns.GetHostEntry(Dns.GetHostName()).AddressList)
                    {
                        if (temp.AddressFamily == AddressFamily.InterNetwork)
                        {
                            localIpEndPoint = new IPEndPoint(temp, port);
                            break;
                        }
                    }
                    socket.Bind(localIpEndPoint);
                }
                catch
                {
                    Console.WriteLine("This port is already in use");
                    continue;
                }
                correctStart = true;
            }
            Console.Write("Input your name ");
            String name = UserInterface.ReadName() + "(" + localIpEndPoint.ToString() + ")";

            Console.WriteLine();
            Console.WriteLine(name);
            Console.WriteLine();
            UserInterface.ShowInformation();
            Console.WriteLine();

            return new Client(name, localIpEndPoint, socket, new Dictionary<IPEndPoint, string>());
        }

        public static void Chat(Client client)
        {
            client.StartWaitingMessage();

            string input = "";
            while (true)
            {
                try
                {
                    Action action = UserInterface.ReadAction(out input);
                    switch (action)
                    {
                        case Action.Connect:
                            {
                                client.Connect();
                                break;
                            }
                        case Action.Disconnect:
                            {
                                UserInterface.LeaveThisChat(client);
                                client.Disconnect();
                                break;
                            }
                        case Action.Clients:
                            {
                                UserInterface.ShowConnectedClients(client);
                                break;
                            }
                        case Action.Message:
                            {
                                client.SendMessageToConnectedClients(input);
                                UserInterface.Message(client.GetName(), input);
                                break;
                            }
                        case Action.Exit:
                            {
                                if (client.GetConnectedClients().Count > 0)
                                {
                                    client.Disconnect();
                                }
                                client.SocketClose();
                                Environment.Exit(0);
                                break;
                            }
                    }
                }
                catch (Exception exception)
                {
                    Console.WriteLine(exception.Message);
                    continue;
                }
            }
        }
    }
}
