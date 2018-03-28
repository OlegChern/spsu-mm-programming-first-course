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

        public static bool GetIP(bool manual, string message, out IPAddress ip)
        {
            ip = null;

            if (manual)
            {
                string ipString;
                string[] splitted = message.Split(' ');

                if (splitted.Length < 2)
                {
                    Console.WriteLine("> Not enough arguments!");
                    return false;
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

                        return false;
                    }
                }

                if (dots != 3)
                {
                    Console.WriteLine("> IPv4 must have 4 32-bit numbers!");
                    return false;
                }

                IPAddress resultIp;
                if (!IPAddress.TryParse(temp, out resultIp))
                {
                    Console.WriteLine("> Wrong IPv4!");
                    return false;
                }

                ip = resultIp;
                return true;
            }
            else
            {
                string[] ipSplitted = message.Split('.');

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

                ip = new IPAddress(ipBytes);
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
