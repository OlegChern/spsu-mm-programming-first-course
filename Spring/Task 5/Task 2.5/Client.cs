using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace Chat
{
    public class Client : User
    {
        public override IPAddress IP { get; set; }

        public override bool IsConnect { get; protected set; }

        public Client(string name, int port, IPAddress ip, ChatWindow chat) : base(name, port, chat)
        {
            IP = ip;
            IPEndPoint = new IPEndPoint(IP, Port);
            Connecting();
        }

        public override void Send(string str)
        {
            try
            {
                byte[] data = new byte[200];
                data = Encoding.Unicode.GetBytes(str);
                SocketServer.Send(data);
            }
            catch (Exception ex)
            {
                Chat.PrintException(ex.Message);
            }
        }      

        public void Connecting()
        {
            try
            {
                SocketServer.Connect(IPEndPoint);
                var recInfo = new ReceiveInfo(SocketServer);
                SocketServer.BeginReceive(recInfo.Buff, 0, recInfo.Buff.Length, SocketFlags.None, new AsyncCallback(Receiving), recInfo);
                IsConnect = true;
            }
            catch (Exception ex)
            {
                Chat.PrintException(ex.Message);
                IsConnect = false;
            }
        }

        public void Receiving(IAsyncResult async)
        {
            var recInfo = (ReceiveInfo)async.AsyncState;
            try
            {              
                if (IsConnect)
                {
                    var read = SocketServer.EndReceive(async);
                    if (read > 0)
                    {
                        var str = Encoding.Unicode.GetString(recInfo.Buff, 0, read);
                        Chat.PrintMessage(str);
                    }
                    recInfo = new ReceiveInfo(SocketServer);
                    SocketServer.BeginReceive(recInfo.Buff, 0, recInfo.Buff.Length, SocketFlags.None, new AsyncCallback(Receiving), recInfo);
                }
            }
            catch (SocketException ex)
            {
                if (ex.ErrorCode == 10053)
                {
                    Chat.PrintException("Сервер отключился");
                    Chat.DisconnectChat();
                }
                else
                {
                    Chat.PrintException(ex.Message);
                }
            }
        }

        public override void Disconnect()
        {
            IsConnect = false;
            SocketServer.Shutdown(SocketShutdown.Both);
            SocketServer.Close();
        }
    }
}
