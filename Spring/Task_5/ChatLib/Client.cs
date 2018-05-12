using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using Exception = System.Exception;

namespace ChatLib
{
    public class Client
    {
        #region fields
        private readonly IPEndPoint listeningIPEndPoint;
        private readonly List<IPEndPoint> connectedClientsIP;
        private readonly Socket listeningSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
        private bool IsLeave { get; set; }
        private IPEndPoint LastConnect { get; set; }
        #endregion
        
        public Client()
        {
            IsLeave = false;
            connectedClientsIP = new List<IPEndPoint>();
            string host = Dns.GetHostName();
            IPAddress tmpIP = Dns.GetHostEntry(host).AddressList.Last();
            bool isInitCorrect = false;
            while (!isInitCorrect)
            {
                try
                {
                    Console.Write("Input your port: ");
                    int tmpPortVal = Int32.Parse(Console.ReadLine());
                    if (tmpPortVal >= 1 && tmpPortVal <= 65535)
                    {
                        listeningIPEndPoint = new IPEndPoint(tmpIP, tmpPortVal);
                        isInitCorrect = true;
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine("Incorrect input port value, try again!");
                }
            }
        }

        public void StartChating()
        {
            ShowHelp();

            Task waitingTask = new Task(Wait);
            waitingTask.Start();

            while (!IsLeave)
            {
                try
                {
                    string message = Console.ReadLine();

                    if (message == "")
                    {
                        throw new IOException();
                    }

                    if (message[0] == '*' || message[0] == '+' || message[0] == '-')
                    {
                        throw new ArgumentException();
                    }

                    switch (message)
                    {
                        case "Exit":
                        {
                            IsLeave = true;
                            break;
                        }
                        case "Connect":
                        {
                            LastConnect = GetIPEndPoint();
                            if (!connectedClientsIP.Contains(LastConnect))
                            {
                                connectedClientsIP.Add(LastConnect);
                                SendIPs(LastConnect);
                            }
                            break;
                        }

                        case "Disconnect":
                        {
                            Disconnect();
                            break;
                        }
                        case "Clients":
                        {
                            Console.WriteLine("Clients list");
                            foreach (var ip in connectedClientsIP)
                            {
                                Console.WriteLine(ip.ToString());
                            }

                            break;
                        }
                        case "Help":
                        {
                            ShowHelp();
                            break;
                        }
                        default:
                        {
                            SendMessage(message);
                            break;
                        }
                    }
                }
                catch (IOException e)
                {
                    Console.WriteLine("Incorrect input");
                }
                catch (ArgumentException e)
                {
                    Console.WriteLine("Incorrect input, don't use + * - at the begining of the message");
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.Message);
                }
            }

            LeaveChat();
        }

        private void ShowHelp()
        {
            Console.WriteLine("\n" +
                              "Connect  -  to connect to other clients\n" +
                              "Disconnect  -  to disconnect from this lobby\n" +
                              "Clients  -  to show who is in this lobby now\n" +
                              "Exit  -  to exit from chat\n" +
                              "Help  -  to show this help window\n");
        }

        private void SendIPs(IPEndPoint ip)
        {
            StringBuilder ipList = new StringBuilder("*");
            ipList.Append(listeningIPEndPoint.Address.ToString());
            ipList.Append(':');
            ipList.Append(listeningIPEndPoint.Port.ToString());
            ipList.Append(" ");
            foreach (IPEndPoint tmpIP in connectedClientsIP)
            {
                ipList.Append(tmpIP.Address.ToString());
                ipList.Append(':');
                ipList.Append(tmpIP.Port.ToString());
                ipList.Append(" ");
            }

            byte[] data = Encoding.Unicode.GetBytes(ipList.ToString());

            listeningSocket.SendTo(data, ip);
        }

        private void SendMessage(string message)
        {

            Byte[] data = Encoding.Unicode.GetBytes(message);

            foreach (IPEndPoint tmpClientIP in connectedClientsIP)
            {
                listeningSocket.SendTo(data, tmpClientIP);
            }
        }

        private void Disconnect()
        {
            SendMessage('-' + listeningIPEndPoint.ToString());
            connectedClientsIP.Clear();
        }


        private void Wait()
        {
            try
            {
                listeningSocket.Bind(listeningIPEndPoint);
                while (true)
                {
                    StringBuilder builder = new StringBuilder();
                    int bytes = 0;
                    byte[] data = new byte[256];
                    EndPoint tmpIP = new IPEndPoint(IPAddress.Any, 0);

                    do
                    {
                        bytes = listeningSocket.ReceiveFrom(data, ref tmpIP);
                        builder.Append(Encoding.Unicode.GetString(data, 0, bytes));
                    } while (listeningSocket.Available > 0);

                    IPEndPoint senderIP = tmpIP as IPEndPoint;

                    if (builder[0] == '*')
                    {
                        foreach (IPEndPoint ip in GetListOfIPs(builder))
                        {
                            if (!connectedClientsIP.Contains(ip))
                            {
                                connectedClientsIP.Add(ip);
                            }
                        }

                        connectedClientsIP.Remove(listeningIPEndPoint);

                        Console.Write("Now these people are in the lobby: ");
                        foreach (IPEndPoint clientIP in connectedClientsIP)
                        {
                            Console.Write(clientIP.ToString() + " ");
                            List<IPEndPoint> tmpList = new List<IPEndPoint>();
                            tmpList.AddRange(connectedClientsIP);
                            tmpList.Remove(clientIP);
                            tmpList.Add(listeningIPEndPoint);
                            StringBuilder ipStrList = new StringBuilder("+");

                            foreach (IPEndPoint ip in tmpList)
                            {
                                ipStrList.Append(ip.Address.ToString());
                                ipStrList.Append(':');
                                ipStrList.Append(ip.Port.ToString());
                                ipStrList.Append(" ");
                            }

                            byte[] ipdata = Encoding.Unicode.GetBytes(ipStrList.ToString());
                            listeningSocket.SendTo(ipdata, clientIP);
                        }

                        Console.WriteLine();
                    }


                    if (builder[0] == '+')
                    {
                        Console.Write("Now these people are in the lobby: ");
                        foreach (IPEndPoint ip in GetListOfIPs(builder))
                        {
                            if (!connectedClientsIP.Contains(ip))
                            {
                                connectedClientsIP.Add(ip);
                            }

                            Console.Write(ip.ToString() + " ");
                        }


                        Console.WriteLine();
                    }

                    if (builder[0] == '-')
                    {
                        string tmpStrIP = builder.ToString(1, builder.Length - 1);
                        connectedClientsIP.Remove(ConvertToIP(tmpStrIP));
                        Console.WriteLine("{0} disconnected", tmpStrIP);
                    }

                    if (builder[0] != '*' && builder[0] != '+' && builder[0] != '-')
                    {
                        Console.WriteLine("[{0}:{1}] - {2}", senderIP.Address.ToString(),
                            senderIP.Port, builder.ToString());
                    }

                }
            }
            catch (SocketException e)
            {
                Disconnect();
                IsLeave = true;
                Console.WriteLine(e.Message);
            }

        }

        private List<IPEndPoint> GetListOfIPs(StringBuilder builder)
        {
            List<IPEndPoint> result = new List<IPEndPoint>();
            int i = 1;
            string tmpIP = "";
            while (builder.Length > i)
            {
                if (builder[i] == ' ')
                {
                    int ipAddressLength = tmpIP.LastIndexOf(':');
                    result.Add(new IPEndPoint(
                        IPAddress.Parse(tmpIP.Substring(0, ipAddressLength)),
                        Convert.ToInt32(tmpIP.Substring(ipAddressLength + 1))));
                    tmpIP = "";
                    i++;
                }
                else
                {
                    tmpIP += builder[i];
                    i++;
                }
            }

            return result;
        }

        private IPEndPoint GetIPEndPoint()
        {
            bool isCorrectInput = false;
            while (!isCorrectInput)
            {
                try
                {
                    Console.Write("Input IP:port ");
                    string inStr = Console.ReadLine();
                    IsCorrectFormatIPAndPort(inStr);
                    return ConvertToIP(inStr);
                }
                catch (Exception e)
                {
                    Console.WriteLine("Input IP & port in this format: X.X.X.X:Y");
                }

            }

            return new IPEndPoint(IPAddress.None, 0);
        }

        private void IsCorrectFormatIPAndPort(string inIPAndPort)
        {
            try
            {
                int i = 0;
                for (int j = 0; j < 4; ++j)
                {
                    string temp = "";
                    while (inIPAndPort[i] != '.' && inIPAndPort[i] != ':')
                    {
                        temp += inIPAndPort[i];
                        i++;
                    }

                    try
                    {
                        if (Convert.ToInt32(temp) < 0 || Convert.ToInt32(temp) > 255)
                        {
                            throw new FormatException();
                        }
                    }
                    catch (Exception e)
                    {
                        throw new FormatException();
                    }

                    i++;
                }

                String tmpPort = "";
                while (i < inIPAndPort.Length)
                {
                    tmpPort += inIPAndPort[i];
                    i++;
                }

                try
                {
                    Convert.ToInt32(tmpPort);
                }
                catch (Exception e)
                {
                    throw new FormatException();
                }
            }
            catch (Exception e)
            {
                throw new FormatException();
            }
        }

        private IPEndPoint ConvertToIP(string inStr)
        {
            try
            {
                int colonInd = inStr.LastIndexOf(':');
                return new IPEndPoint(
                    IPAddress.Parse(inStr.Substring(0, colonInd)),
                    Convert.ToInt32(inStr.Substring(colonInd + 1)));
            }
            catch (Exception e)
            {
                Console.WriteLine("Error format of IP");
                throw new ArgumentException();
            }
        }

        private void LeaveChat()
        {
            if (listeningSocket != null)
            {
                listeningSocket.Shutdown(SocketShutdown.Both);
                listeningSocket.Close();
            }
        }
    }
}



