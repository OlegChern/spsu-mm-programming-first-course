#include "stdafx.h"
#include "connection.h"
#include "errors.h"

string connection::ip = "127.0.0.1";
int connection::port = 0;
int connection::lastPort = 0;

SOCKET connection::initSocket()
{
	SOCKET _socket;
	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		errors::ShowError();
	return _socket;
}

void connection::sendMessage(SOCKET socket, string message)
{
	send(socket, message.c_str(), 512, 0);
}

SOCKET connection::tryConnect(string ipClient, int portClient)
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

string connection::recieveClient(SOCKET socket)
{
	char buff[512] = "";
	recv(socket, buff, sizeof(buff), 0);
	return string(buff);
}

string connection::recieveClient(LPVOID client_socket)
{
	return recieveClient(((SOCKET *)client_socket)[0]);
}
