using System;
using System.Linq;
using System.Net;

namespace Task5.Chat
{
    public static class UserInterface
    {
        public static int ReadPort()
        {
            int port = 0;
            string input = Console.ReadLine();
            if (Exit(input))
            {
                Environment.Exit(0);
            }
            bool correct = Int32.TryParse(input, out port);
            while (!correct || port < 1 || port > 65535)
            {
                Console.WriteLine("incorrect port");
                correct = Int32.TryParse(Console.ReadLine(), out port);
            }
            return port;
        }

        public static string ReadName()
        {
            string name = null;
            bool correct = false;
            while (!correct)
            {
                try
                {
                    name = Console.ReadLine();
                    if (Exit(name))
                    {
                        Environment.Exit(0);
                    }
                    if ((name == string.Empty) || (name.Contains(' ')) || (name.Contains('(')) || (name.Contains(')')))
                    {
                        throw new Exception();
                    }
                    correct = true;
                }
                catch
                {
                    Console.WriteLine("incorrect name");
                }
            }
            return name;
        }

        public static IPEndPoint ReadIpEndPoint()
        {
            bool correct = false;
            string input = null;
            IPEndPoint iPEndPoint = null;
            while (!correct)
            {
                try
                {
                    input = Console.ReadLine();
                    if(Exit(input))
                    {
                        Environment.Exit(0);
                    }
                    iPEndPoint = StringFunctions.StringToIpEndPoint(input);
                    correct = true;
                }
                catch (Exception exception)
                {
                    Console.WriteLine(exception.Message);
                }
            }
            return iPEndPoint;
        }

        public static Action ReadAction(out string input) 
        {
            input = Console.ReadLine();
            switch (input)
            {
                case "connect":
                    {
                        return Action.Connect;
                    }
                case "disconnect":
                    {
                        return Action.Disconnect;
                    }
                case "clients":
                    {
                        return Action.Clients;
                    }
                case "exit":
                    {
                        return Action.Exit;
                    }
                default:
                    {
                        return Action.Message;
                    }
            }
        }

        public static bool Exit(string input)
        {
            if(input.Equals("exit"))
            {
                return true;
            }
            return false;
        }

        public static void ShowInformation()
        {
            Console.WriteLine("connect - to connect to client");
            Console.WriteLine("disconnect - to disconnect");
            Console.WriteLine("clients - to show connected clients");
            Console.WriteLine("exit - to exit from chat");
        }

        public static void ShowConnectedClients(Client client)
        {
            Console.WriteLine("Connected clients:");
            Console.WriteLine(StringFunctions.ListOfClientsToString(client));
        }

        public static void Disconnect(string name)
        {
            Console.WriteLine("- {0}", name);
        }

        public static void LeaveThisChat(Client client)
        {
            Console.WriteLine("- {0}", StringFunctions.ListOfClientsToString(client));
        }

        public static void Connect(string name)
        {
            Console.WriteLine("+ {0}", name);
        }

        public static void Message(string name, string message)
        {
            Console.WriteLine("{0}: {1}", name, message);
        }

        public static void Message(string message)
        {
            Console.WriteLine(message);
        }
    }
}
