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
            Console.WriteLine("  /q      - to quit\n");
        }
        
        public static void ShowException(Exception exception, string from)
        {
            Console.WriteLine("> " + from + " " + exception.GetType().ToString() + ": " + exception.Message);
            Console.ReadKey();
        }

        public static void ShowException(Exception exception)
        {
            Console.WriteLine("> " + exception.GetType().ToString() + ": " + exception.Message);
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

        public static bool GetEndPoint(bool manual, string message, out IPEndPoint ep)
        {
            ep = null;

            if (manual)
            {
                string[] splitted = message.Split(' ');

                if (splitted.Length < 2)
                {
                    ShowMessage("> Not enough arguments!");
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
                        ShowMessage("> IPv4 must contain only symbols: 0-9, ':', '.'!");
                        return false;
                    }
                }

                IPAddress ip;
                if (!IPAddress.TryParse(ipString, out ip))
                {
                    ShowMessage("> Wrong IPv4!");
                    return false;
                }

                int port;
                if (!int.TryParse(portString, out port))
                {
                    ShowMessage("> Wrong port!");
                    return false;
                }

                ep = new IPEndPoint(ip, port);
                return true;
            }
            else
            {
                string[] ipSplitted = message.Split('.', ':');

                if (ipSplitted.Length < 5)
                {
                    return false;
                }

                // read ip
                byte[] ipBytes = new byte[4];

                for (int i = 0; i < 4; i++)
                {
                    ipBytes[i] = byte.Parse(ipSplitted[i]);
                }

                IPAddress ip = new IPAddress(ipBytes);
                int port = int.Parse(ipSplitted[4]);

                ep = new IPEndPoint(ip, port);
                return true;
            }
        }

        public static int GetPort()
        {
            while (true)
            {
                ShowMessage("> Enter port: ");

                string temp = GetMessage();
                string portStr = string.Empty;

                bool success = true;
                foreach (char c in temp)
                {
                    if (c < '0' || c > '9')
                    {
                        ShowMessage("> Port must contain only symbols: 0-9!");
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
                    ShowMessage("> Port must be in range 1024-65535!");
                    continue;
                }

                return port;
            }
        }

        public static string GetName()
        {
            while (true)
            {
                ShowMessage("> Enter username: ");

                string temp = GetMessage();
                string name = string.Empty;

                bool success = true;
                foreach (char c in temp)
                {
                    if ((c < '0' || c > '9') && (c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
                    {
                        ShowMessage("> Username must contain only symbols: a-z, A-Z, 0-9!");
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
                    ShowMessage("> Username must contain more than 2 symbols!");
                }
            }
        }

        public static bool ToQuit()
        {
            ShowMessage("> Press Y to quit: ");
            ConsoleKeyInfo key = GetKey();

            return key.Key == ConsoleKey.Y;
        }
    }
}
