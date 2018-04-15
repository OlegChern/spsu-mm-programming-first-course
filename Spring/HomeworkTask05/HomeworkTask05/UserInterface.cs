using System;
using System.Net;

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
        }

        public static void ShowException(Exception exception)
        {
            Console.WriteLine(">> " + exception.GetType().ToString() + ": " + exception.Message);
        }

        public static void ShowSpecification(string message)
        {
            Console.WriteLine("> " + message);
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

            string[] splitted = message.Split(' ', ':');

            IPAddress ip;
            if (splitted.Length < 3)
            {
                ShowSpecification("Not enough arguments!");
                return false;
            }
            else if (splitted.Length == 3)
            {
                // ipv4
                if (!IPAddress.TryParse(splitted[1], out ip))
                {
                    ShowSpecification("Wrong IP address!");
                    return false;
                }
            }
            else
            {
                // ipv6
                if (!IPAddress.TryParse(string.Join(":", splitted, 1, splitted.Length - 2), out ip))
                {
                    ShowSpecification("Wrong IP address!");
                    return false;
                }
            }

            int port;
            if (!int.TryParse(splitted[splitted.Length - 1], out port))
            {
                ShowSpecification("Wrong IP address!");
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