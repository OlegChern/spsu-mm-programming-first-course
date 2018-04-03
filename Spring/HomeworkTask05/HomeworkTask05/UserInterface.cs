using System;
using System.Text;

using System.Threading;
using System.Net;
using System.Net.Sockets;

namespace Chat
{
    static class UserInterface
    {
        public static void ShowTutorial()
        {
            Console.WriteLine("Peer-to-peer chat\n");
            Console.WriteLine("Main commands:");
            Console.WriteLine("  /c <ip> - to connect to peer with IP <ip>");
            Console.WriteLine("  /s      - to show all connceted IP's");
            Console.WriteLine("  /d      - to disconnect");
            Console.WriteLine("  /q      - to exit\n");
        }
        
        public static void ShowException(Exception exception, string from)
        {
            Console.WriteLine(">> " + from + " " + exception.GetType().ToString() + ": " + exception.Message);
            Console.ReadKey();
        }

        public static void ShowException(Exception exception)
        {
            Console.WriteLine(">> " + exception.GetType().ToString() + ": " + exception.Message);
            Console.ReadKey();
        }

        public static void ShowSpecification(string message)
        {
            Console.WriteLine("> " + message);
            Console.ReadKey();
        }

        public static void ShowMessage(string message)
        {
            Console.WriteLine(message);
        }

        public static string GetMessage()
        {
            return Console.ReadLine();
        }

        public static ConsoleKeyInfo GetKey()
        {
            return Console.ReadKey();
        }

        public static bool GetEndPoint(string message, out IPEndPoint ep)
        {
            ep = null;

            string[] splitted = message.Split(' ');

            if (splitted.Length < 2)
            {
                ShowSpecification("Not enough arguments!");
                return false;
            }

            string ipString = string.Empty;

            bool readPort = false;
            string portString = string.Empty;

            // expecting ip after space
            foreach (char c in splitted[1])
            {
                if (c >= '0' && c <= '9')
                {
                    if (readPort)
                    {
                        portString += c;
                    }
                    else
                    {
                        ipString += c;
                    }
                }
                else if ((c == '.' || c == ',') && !readPort)
                {
                    ipString += '.';
                }
                else if (c == ':')
                {
                    readPort = true;
                }
                else
                {
                    ShowSpecification("IPv4 must contain only symbols: 0-9, ':', '.'!");
                    return false;
                }
            }

            IPAddress ip;
            if (!IPAddress.TryParse(ipString, out ip))
            {
                ShowSpecification("Wrong IPv4!");
                return false;
            }

            int port;
            if (!int.TryParse(portString, out port))
            {
                ShowSpecification("Wrong port!");
                return false;
            }

            ep = new IPEndPoint(ip, port);
            return true;
        }

        public static int GetPort()
        {
            while (true)
            {
                ShowSpecification("Enter port: ");

                string temp = GetMessage();
                string portStr = string.Empty;

                bool success = true;
                foreach (char c in temp)
                {
                    if (c < '0' || c > '9')
                    {
                        ShowSpecification("Port must contain only symbols: 0-9!");
                        success = false;

                        break;
                    }

                    portStr += c;
                }

                if (!success)
                {
                    continue;
                }

                int port = int.Parse(portStr);

                if (port < 1024 || port > 65535)
                {
                    ShowSpecification("Port must be in range 1024-65535!");
                    continue;
                }

                return port;
            }
        }

        public static string GetName()
        {
            while (true)
            {
                ShowSpecification("Enter username: ");

                string temp = GetMessage();
                string name = string.Empty;

                bool success = true;
                foreach (char c in temp)
                {
                    if ((c < '0' || c > '9') && (c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
                    {
                        ShowSpecification("Username must contain only symbols: a-z, A-Z, 0-9!");
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
                    return name;
                }
                else
                {
                    ShowSpecification("Username must contain more than 2 symbols!");
                }
            }
        }

        public static bool RequestExit()
        {
            ShowSpecification("Press Y to exit: ");
            ConsoleKeyInfo key = GetKey();

            return key.Key == ConsoleKey.Y;
        }
    }
}
