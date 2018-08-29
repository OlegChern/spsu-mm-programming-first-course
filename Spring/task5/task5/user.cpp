#include "stdafx.h"
#include "user.h"

string user::ip = "127.0.0.1";
string user::exitCommand = "exit";
string user::incorrectAdress = "> Connect error: Incorrect address";
string user::usedAdress = "> Connect error: This adress is using now";
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

void user::LogMessage(string message)
{
	cout << message.c_str() << std::endl;
}

void user::Exit(SOCKET socket)
{
	closesocket(socket);
	WSACleanup();
}

void user::Send(SOCKET socket, string message)
{
	send(socket, message.c_str(), 512, 0);
}

SOCKET user::InitSocket()
{
	SOCKET _socket;
	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ShowError();
	return _socket;
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

void user::ShowError()
{
	printf("Error socket %d\n", WSAGetLastError());
	WSACleanup();
}
