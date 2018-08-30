#include "stdafx.h"
#include "user.h"

string user::ip = "127.0.0.1";
string user::exitCommand = "exit";
int user::port = 0;
bool user::exitFlag = 0;
string user::name = "";
map <int, SOCKET> user::clients = {};
int user::lastPort = 0;

string user::convert(int a)
{
	stringstream out;
	out << a;
	return out.str();
}

pair<string, string> user::parser(string s)
{
	pair<string, string> res = { "","" };
	bool flag = false;
	for (int i = 3; i < s.size(); i++)
	{
		if (s[i] == ':')
		{
			if (flag)
				return { "","" };
			flag = true;
			continue;
		}
		if (!flag)
			res.first += s[i];
		else
			res.second += s[i];
	}
	return res;
}

void user::logMessage(string message)
{
	cout << message.c_str() << std::endl;
}

void user::exitCmd(SOCKET socket)
{
	closesocket(socket);
	WSACleanup();
}

SOCKET user::tryConnect(string ipClient, int portClient)
{
	if (ipClient != ip)
	{
		printf("> Connect error\n");
		return -1;
	}
	SOCKET _socket;
	_socket = initSocket();

	sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(portClient);
	HOSTENT *hst;
	// преобразование IP адреса из символьного в сетевой формат
	if (inet_addr(ipClient.c_str()) != INADDR_NONE)
		dest_addr.sin_addr.s_addr = inet_addr(ipClient.c_str());
	else
		if (hst = gethostbyname(ipClient.c_str()))
			((unsigned long *)&dest_addr.sin_addr)[0] =
			((unsigned long **)hst->h_addr_list)[0][0];
		else
			printf("> Invalid address %s:%s\n", ipClient.c_str(), portClient);

	if (connect(_socket, (sockaddr *)&dest_addr, sizeof(dest_addr)))
	{
		printf("> Connect error %d\n", WSAGetLastError());
		return -1;
	}
	return _socket;
}

void user::sendMessage(SOCKET socket, string message)
{
	send(socket, message.c_str(), 512, 0);
}

SOCKET user::initSocket()
{
	SOCKET _socket;
	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		errors::ShowError();
	return _socket;
}

DWORD user::getMessage(LPVOID clientSocket)
{
	map <int, SOCKET>::iterator it;
	while (!exitFlag) {
		string message = "";
		message = recieveClient(clientSocket);
		int check = systemCommand(message);
		switch (check)
		{
		case -1:
		{
			printf("%s\n", message.c_str());
			break;
		}
		case 0:
		{
			string out = "";
			bool flag = false;
			for (int i = 3; i < message.size(); i++)
			{
				if (message[i] == 'p')
				{
					flag = true;
					break;
				}
				out += message[i];
			}
			int portClient = atoi(out.c_str());
			if (flag)
				lastPort = portClient;
			else
			{
				bool flag = false;
				for (it = clients.begin(); it != clients.end(); ++it)
					if (portClient == it->first)
					{
						flag = true;
						break;
					}
				if (flag)
					break;
				SOCKET _socket = tryConnect(ip, portClient);
				if (_socket != -1)
				{
					sendMessage(_socket, "/c " + convert(port) + "p");
					sendMessage(_socket, "> Connected " + ip + ":" + convert(port));
					clients[atoi(out.c_str())] = _socket;
					DWORD thID;
					CreateThread(NULL, NULL, getMessage, &clients[atoi(out.c_str())], NULL, &thID);
					printf("> Connected new user %s:%s\n", ip.c_str(), out.c_str());
				}
			}
			break;
		}
		case 1:
		{
			pair <string, string> infClient = parser(message);
			clients.erase(atoi(infClient.second.c_str()));
			printf("> %s disconnected\n", infClient.first.c_str());
			return 0;
		}
		default:
			break;
		}
	}
	return 0;
}

DWORD user::workWithClient(LPVOID client_socket)
{
	while (!exitFlag)
	{
		string cmd;
		getline(cin, cmd);
		map <int, SOCKET>::iterator it;
		switch (systemCommand(cmd))
		{
		case 0:
		{
			pair<string, string> ipPort = parser(cmd);
			bool flag = false;
			for (it = clients.begin(); it != clients.end(); ++it)
				if (ipPort.first == ip && atoi(ipPort.second.c_str()) == it->first)
				{
					logMessage(errors::usedAdress);
					flag = true;
					break;
				}
			if (flag)
				break;
			if (!errors::checkAdress(ipPort.first + ":" + ipPort.second))
			{
				logMessage(errors::incorrectAdress);
				break;
			}
			SOCKET _socket = tryConnect(ipPort.first, atoi(ipPort.second.c_str()));
			if (_socket != -1)
			{
				sendMessage(_socket, "/c " + convert(port) + "p");
				cout << "> Connect with " << ipPort.first << ":" << ipPort.second << " success\n";
				clients[atoi(ipPort.second.c_str())] = _socket;
				DWORD thID;
				CreateThread(NULL, NULL, getMessage, &clients[atoi(ipPort.second.c_str())], NULL, &thID);
				for (it = clients.begin(); it != clients.end(); ++it)
					sendMessage(it->second, "> Connected new user " + ipPort.first + ":" + convert(port));
			}
			break;
		}
		case 1:
		{
			printf("> Exit...\n");
			exitFlag = true;
			for (it = clients.begin(); it != clients.end(); ++it)
				sendMessage(it->second, "/e " + name + ":" + convert(port));
			for (it = clients.begin(); it != clients.end(); ++it)
				exitCmd(it->second);
			break;
		}
		default:
		{
			for (it = clients.begin(); it != clients.end(); ++it)
				sendMessage(it->second, name + ":" + cmd);
			break;
		}
		}
	}
	return 0;
}

string user::recieveClient(SOCKET socket)
{
	char buff[512] = "";
	recv(socket, buff, sizeof(buff), 0);
	return string(buff);
}

string user::recieveClient(LPVOID client_socket)
{
	return recieveClient(((SOCKET *)client_socket)[0]);
}

int user::systemCommand(string s)
{
	if (s[0] == '/')
	{
		if (s.size() > 2 && s[1] == 'c' && s[2] == ' ')
		{
			return 0;
		}
		else
			if (s[1] == 'e')
				return 1;
	}
	return -1;
}
