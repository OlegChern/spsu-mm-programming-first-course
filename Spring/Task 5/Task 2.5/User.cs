using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace Chat
{
    public abstract class User 
    {
        public string Name { get; }

        public abstract bool IsConnect { get; protected set; }

        public ChatWindow Chat { get; }

        public abstract IPAddress IP { get; set; }

        public int Port { get; }

        public IPEndPoint IPEndPoint { get; set; }

        public Socket SocketServer { get; private set; }

        public User(string name, int port, ChatWindow chat)
        {
            Port = port;
            Name = name;
            Chat = chat;
            SocketServer = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        }

        public abstract void Send(string str);

        public abstract void Disconnect();
    }
}
