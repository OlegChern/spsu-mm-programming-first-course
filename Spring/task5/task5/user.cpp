#include "stdafx.h"
#include "user.h"
#include "connection.h"

string user::exitCommand = "exit";
bool user::exitFlag = 0;
string user::name = "";
map <int, SOCKET> user::clients = {};

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

DWORD user::getMessage(LPVOID clientSocket)
{
	map <int, SOCKET>::iterator it;
	while (!exitFlag) {
		string message = "";
		message = connection::recieveClient(clientSocket);
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
					if ((int)message.size() != i + 1)
						printf("> Connected %s:%s\n", connection::ip.c_str(), out.c_str());
					break;
				}
				out += message[i];
			}
			int portClient = atoi(out.c_str());
			if (flag)
				connection::lastPort = portClient;
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
				SOCKET _socket = connection::tryConnect(connection::ip, portClient);
				if (_socket != -1)
				{
					clients[atoi(out.c_str())] = _socket;
					connection::sendMessage(_socket, "/c " + convert(connection::port) + "p");
					connection::sendMessage(_socket, "> Connected " + connection::ip + ":" + convert(connection::port));
					DWORD thID;
					CreateThread(NULL, NULL, getMessage, &clients[atoi(out.c_str())], NULL, &thID);
					printf("> Connected %s:%s\n", connection::ip.c_str(), out.c_str());
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
				if (ipPort.first == connection::ip && atoi(ipPort.second.c_str()) == it->first)
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
			SOCKET _socket = connection::tryConnect(ipPort.first, atoi(ipPort.second.c_str()));
			if (_socket != -1)
			{
				connection::sendMessage(_socket, "/c " + convert(connection::port) + "pn");
				cout << "> Connect with " << ipPort.first << ":" << ipPort.second << " success\n";
				clients[atoi(ipPort.second.c_str())] = _socket;
				DWORD thID;
				CreateThread(NULL, NULL, getMessage, &clients[atoi(ipPort.second.c_str())], NULL, &thID);
				Sleep(200);
				for (it = clients.begin(); it != clients.end(); ++it)
				{
					if (it->second == clients[atoi(ipPort.second.c_str())])
						continue;
					connection::sendMessage(it->second, "/c " + ipPort.second);
				}
			}
			break;
		}
		case 1:
		{
			printf("> Exit...\n");
			for (it = clients.begin(); it != clients.end(); ++it)
				connection::sendMessage(it->second, "/e " + name + ":" + convert(connection::port));
			exitFlag = true;
			for (it = clients.begin(); it != clients.end(); ++it)
				exitCmd(it->second);
			break;
		}
		default:
		{
			for (it = clients.begin(); it != clients.end(); ++it)
				connection::sendMessage(it->second, name + ":" + cmd);
			break;
		}
		}
	}
	return 0;
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
