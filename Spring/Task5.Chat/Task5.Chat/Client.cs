using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace Task5.Chat
{
    public class Client
    {
        private string name;
        private IPEndPoint localIpEndPoint;
        private Socket socket;
        private Dictionary<IPEndPoint, string> connectedClients;

        public Client(string name, IPEndPoint iPEndPoint, Socket socket,  Dictionary<IPEndPoint, string> connectedClients)
        {
            this.name = name;
            this.localIpEndPoint = iPEndPoint;
            this.socket = socket;
            this.connectedClients = connectedClients;
        }

        public Dictionary<IPEndPoint, string> GetConnectedClients()
        {
            return connectedClients;
        }

        public string GetName()
        {
            return name;
        }

        private bool Connected(IPEndPoint iPEndPoint)
        {
            return connectedClients.ContainsKey(iPEndPoint);
        }

        public void AddNewConnectedClients(KeyValuePair<IPEndPoint, string> client)
        {
            if ((!Connected(client.Key)) && (!client.Key.Equals(localIpEndPoint)))
            {
                connectedClients.Add(client.Key, client.Value);
            }
        }

        public void DeleteConnectedClients(IPEndPoint iPEndPoint)
        {
            connectedClients.Remove(iPEndPoint);
        }

        private void SendIPsToConnectedClients(string stringIPs)
        {
            string message = String.Concat('+', stringIPs);
            byte[] data = Encoding.Unicode.GetBytes(message);
            foreach (var temp in connectedClients)
            {
                socket.SendTo(data, temp.Key);
            }
        }

        private void SendListOfClients(IPEndPoint iPEndPoint)
        {
            string message;
            if (connectedClients.Count == 0)
            {
                message = String.Concat('#', name);
            }
            else
            {
                message = String.Concat('#', name, ", ", StringFunctions.ListOfClientsToString(this));
            }
            byte[] data = Encoding.Unicode.GetBytes(message);
            socket.SendTo(data, iPEndPoint);
        }

        public void SendMessageToConnectedClients(string message)
        {
            string newMessage = String.Concat('=', name, ": ", message);
            byte[] data = Encoding.Unicode.GetBytes(newMessage);
            foreach (var temp in connectedClients)
            {
                socket.SendTo(data, temp.Key);
            }
        }

        public void Connect()
        {
            Console.Write("Input IP:port ");
            bool correct = false;
            while (!correct)
            {
                IPEndPoint iPEndPoint = UserInterface.ReadIpEndPoint();
                if (iPEndPoint.Equals(localIpEndPoint) )
                {
                    Console.WriteLine("it is your IP:port");
                    return;
                }
                if (Connected(iPEndPoint))
                {
                    Console.WriteLine("you are already connected to this client");
                    return;
                }
                string message;
                if (connectedClients.Count == 0)
                {
                    message = String.Concat('*', name);
                }
                else
                {
                    message = String.Concat('*', name, ", ", StringFunctions.ListOfClientsToString(this));
                }

                byte[] data = Encoding.Unicode.GetBytes(message);
                try
                {
                    socket.SendTo(data, iPEndPoint);
                    correct = true;
                }
                catch
                {
                    Console.WriteLine("incorrect input");
                }
            }
        }

        public void Disconnect()
        {
            if (connectedClients.Count > 0)
            {
                string message = String.Concat("-", name);
                byte[] data = Encoding.Unicode.GetBytes(message);
                foreach (var temp in connectedClients)
                {
                    socket.SendTo(data, temp.Key);
                }
                connectedClients.Clear();
            }
        }

        public void SocketClose()
        {
            socket.Shutdown(SocketShutdown.Both);
            socket.Close();
        }

        public void ReceiveMessage(string input, IPEndPoint sender)
        {
            try
            {
                if (input.Length > 0)
                {
                    char first = input[0];
                    string message = input.Remove(0, 1);
                    switch (first)
                    {
                        case '-':
                            {
                                IPEndPoint iPEndPoint = StringFunctions.StringToClient(message).Key;
                                UserInterface.Disconnect(message);
                                DeleteConnectedClients(iPEndPoint);
                                break;
                            }
                        case '+':
                            {
                                StringFunctions.StringToListOfClients(message, this);
                                UserInterface.Connect(message);
                                break;
                            }
                        case '=':
                            {
                                UserInterface.Message(message);
                                break;
                            }
                        case '#':
                            {
                                SendIPsToConnectedClients(message);
                                StringFunctions.StringToListOfClients(message, this);
                                UserInterface.Connect(message);
                                break;
                            }
                        case '*':
                            {
                                SendListOfClients(sender);
                                SendIPsToConnectedClients(message);
                                StringFunctions.StringToListOfClients(message, this);
                                UserInterface.Connect(message);
                                break;
                            }
                    }
                }
            }
            catch
            {
                return;
            }
        }

        private void WaitMessage()
        {
            while (true)
            {
                string inputMessage = "";
                byte[] data = new byte[1024];
                EndPoint temp = new IPEndPoint(IPAddress.Any, 0);
                int bytes = 0;

                do
                {
                    bytes = socket.ReceiveFrom(data, ref temp);
                    inputMessage = inputMessage + Encoding.Unicode.GetString(data, 0, bytes);
                } while (socket.Available > 0);

                IPEndPoint senderIP = temp as IPEndPoint;
                ReceiveMessage(inputMessage.ToString(), senderIP);
            }
        }

        public void StartWaitingMessage()
        {
            Task waiting = new Task(WaitMessage);
            waiting.Start();
        }
    }
}
