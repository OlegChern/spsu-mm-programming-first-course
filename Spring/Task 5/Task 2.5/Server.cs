using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace Chat
{
    public class Server : User
    {
        public List<Socket> Sockets { get; private set; }

        public override IPAddress IP { get; set; }
        public override bool IsConnect { get; protected set; }

        public Server(string name, int port, ChatWindow chat) : base(name, port, chat)
        {
            Sockets = new List<Socket>();
            IP = Chat.IP;
            IPEndPoint = new IPEndPoint(IP, Port);
            StartListening();
        }       

        public override void Send(string str)
        {
            try
            {
                if (IsConnect)
                {
                    var data = Encoding.Unicode.GetBytes(str);

                    foreach (var e in Sockets)
                    {
                        e.Send(data);
                    }

                    Chat.PrintMessage(str);
                }
            }
            catch (Exception ex)
            {
                Chat.PrintException(ex.Message);
            }
        }

        public void StartListening()
        {
            try
            {
                SocketServer.Bind(IPEndPoint);
                SocketServer.Listen(16);
                SocketServer.BeginAccept(new AsyncCallback(NewClient), null);
                IsConnect = true;
            }
            catch (Exception ex)
            {
                IsConnect = false;
                Chat.PrintException(ex.Message);
            }
        }

        public void StartReceiving(Socket socket)
        {
            try
            {
                var recInfo = new ReceiveInfo(socket);          
                socket.BeginReceive(recInfo.Buff, 0, recInfo.Buff.Length, SocketFlags.None, new AsyncCallback(Receiving), recInfo);
            }
            catch (Exception ex)
            {
                Chat.PrintException(ex.Message);
            }                      
        }

        public void Receiving(IAsyncResult async)
        {
            var recInfo = (ReceiveInfo)async.AsyncState;
            try
            {
                if (IsConnect)
                {
                    var read = recInfo.Socket.EndReceive(async);
                    if (read > 0)
                    {
                        var str = Encoding.Unicode.GetString(recInfo.Buff, 0, read);
                        Chat.PrintMessage(str);
                        recInfo.Buff = Encoding.Unicode.GetBytes(str);
                        foreach (var e in Sockets)
                        {
                            e.Send(recInfo.Buff);
                        }
                    }
                    recInfo.Socket.BeginReceive(recInfo.Buff, 0, recInfo.Buff.Length, SocketFlags.None, new AsyncCallback(Receiving), recInfo);
                }
            }
            catch (SocketException ex)
            {
                if (ex.ErrorCode == 10053)
                {
                    Sockets.Remove(recInfo.Socket);
                    recInfo.Socket.Shutdown(SocketShutdown.Both);
                    recInfo.Socket.Close();
                }
                else
                {
                    Chat.PrintException(ex.Message);
                }
            }
        }

        public void NewClient(IAsyncResult async)
        {
            try
            {
                if (IsConnect)
                {
                    Sockets.Add(SocketServer.EndAccept(async));
                    StartReceiving(Sockets[Sockets.Count - 1]);
                    SocketServer.BeginAccept(new AsyncCallback(NewClient), null);
                }
            }
            catch (Exception ex)
            {
                Chat.PrintException(ex.Message);
            }
        }

        public override void Disconnect()
        {
            IsConnect = false;
            foreach (var e in Sockets)
            {
                e.Shutdown(SocketShutdown.Both);
                e.Close();
            }
            SocketServer.Close();
            Sockets.Clear();
        }
    }
}
