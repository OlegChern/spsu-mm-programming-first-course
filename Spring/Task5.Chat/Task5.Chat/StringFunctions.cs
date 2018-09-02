using System;
using System.Collections.Generic;
using System.Net;

namespace Task5.Chat
{
    public static class StringFunctions
    {
        public static string ListOfClientsToString(Client client)
        {
            string result = "";
            foreach (var temp in client.GetConnectedClients())
            {
                result = result + temp.Value + "(" + temp.Key + "), ";
            }
            if (result.Length > 0)
            {
                return result.Remove(result.Length - 2);
            }
            return result;
        }

        public static KeyValuePair<IPEndPoint, string> StringToClient(string input)
        {
            string[] split = input.Split(new char[] { '(', ')' }, StringSplitOptions.RemoveEmptyEntries);
            if (split.Length != 2)
            {
                throw new Exception("incorrect input");
            }
            IPEndPoint iPEndPoint = StringFunctions.StringToIpEndPoint(split[1]);
            string nameOfClient = split[0];
            return new KeyValuePair<IPEndPoint, string>(iPEndPoint, nameOfClient);
        }

        public static void StringToListOfClients(string input, Client client)
        {
            string[] splitInput = input.Split(new char[] { ',', ' ' }, StringSplitOptions.RemoveEmptyEntries);
            foreach (var temp in splitInput)
            {
                KeyValuePair<IPEndPoint, string> newClient = StringToClient(temp);
                client.AddNewConnectedClients(newClient);
            }
        }

        public static IPEndPoint StringToIpEndPoint(string str)
        {
            string[] splitInput = str.Split(':');
            if (splitInput.Length != 2)
            {
                throw new Exception("incorrect input");
            }
            IPAddress ip;
            if (!IPAddress.TryParse(splitInput[0], out ip))
            {
                throw new Exception("incorrect ip-adress");
            }
            int port;
            if (!Int32.TryParse(splitInput[1], out port) || port < 1 || port > 65535)
            {
                throw new Exception("incorrect port");
            }
            return new IPEndPoint(ip, port);
        }
    }
}
