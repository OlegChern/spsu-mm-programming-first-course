#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <vector>
#pragma comment( lib, "ws2_32.lib" )
using namespace std;

class Message {
public:
	int size;
	string str;
	Message() {
		size = 0;
		str = "";
	}
	Message(int _size, string _str) {
		size = _size;
		str = _str;
	}
};

#pragma region Globals
vector<SOCKET> sockets;
/// <summary>
/// привествие
/// </summary>
string hello = "Hello, new member!";
/// <summary>
/// приветсвие сервера при включении
/// </summary>
string welcome = "TCP SERVER DEMO";
/// <summary>
/// Порт, который слушает сервер 
/// </summary>
int port = 600;
/// <summary>
/// общий буфер для записи сообщений от всех клиентов 
/// </summary>
Message message;

string prevStr;

string typeMessge = "type your message here";
/// <summary>
/// число пользователей
/// </summary>
int nclients = 0;
#pragma endregion

#pragma region Methods
/// <summary>
/// показывает сообщение об ошибке
/// Деиницилизация библиотеки Winsock 
/// </summary>
void ShowError() {
	printf("Error socket %d\n", WSAGetLastError());
	WSACleanup();
}

void ShowError(SOCKET _socket) {
	printf("Error bind %d\n", WSAGetLastError());
	// закрываем сокет!
	closesocket(_socket);
	WSACleanup();
}
/// <summary>
/// печать количества активных пользователей 
/// </summary>
void PrintUsers() {
	if (nclients > 0)
		printf("%d user on-line\n", nclients);
	else
		printf("No User on line\n");
}
/// <summary>
/// отправка сообщения
/// </summary>
/// <param name="socket"></param>
/// <param name="message"></param>
void Send(SOCKET socket, string message) {
	send(socket, message.c_str(), 512, 0);
}
/// <summary>
/// получение сообщения
/// </summary>
/// <param name="socket"></param>
/// <returns></returns>
Message Recieve(SOCKET socket) {
	char buff[512] = "";
	int size = recv(socket, buff, sizeof(buff), 0);
	return Message(size, string(buff));
}
/// <summary>
/// печатает сообщения  в консоли сервера
/// </summary>
/// <param name="message"></param>
void LogMessage(string message) {
	cout << message.c_str() << std::endl;
}
/// <summary>
/// обсуживает очередного подключившегося клиента независимо от остальных
/// </summary>
/// <param name="client_socket"></param>
/// <returns></returns>
DWORD WINAPI WorkWithClient(LPVOID client_socket)
{
	SOCKET socket = ((SOCKET *)client_socket)[0];
	Send(socket, hello);
	while (1)
	{
		message = Recieve(socket);
		if (message.size < 0)
			break;
		if (message.str != "")
		{
			for (int i = 0; i < sockets.size(); i++)
				if (socket != sockets[i])
					Send(sockets[i], message.str);
			message.str = "";
		}
	}
	nclients--;
	printf("-disconnect\n");
	PrintUsers();
	closesocket(socket);
	return 0;
}
/// <summary>
/// Инициализация Библиотеки Сокетов
/// </summary>
/// <returns>true- если все ок</returns>
bool Init() {
	char buff[1024];
	if (WSAStartup(0x0202, (WSADATA *)&buff[0]))
	{
		printf("Error WSAStartup %d\n", WSAGetLastError());
		return false;
	}
	return true;
}
/// <summary>
/// Создает сокет
/// </summary>
/// <returns></returns>
SOCKET InitSocket() {
	SOCKET _socket;
	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ShowError();
	return _socket;
}


#pragma endregion
int main(int argc, char* argv[])
{

	setlocale(LC_ALL, "rus");
	LogMessage(welcome);
	if (Init()) {
		// создание сокета
		SOCKET _socket = InitSocket();
		// связывание сокета с локальным адресом
		sockaddr_in local_addr;
		local_addr.sin_family = AF_INET;
		local_addr.sin_port = htons(port);
		local_addr.sin_addr.s_addr = 0;
		if (bind(_socket, (sockaddr *)&local_addr, sizeof(local_addr)))
			ShowError(_socket);
		// ожидание подключений
		if (listen(_socket, 20))
			ShowError(_socket);
		printf("Waiting for connection\n");
		/// <summary>
		/// сокет для клиента
		/// </summary>
		SOCKET clinetSocket;
		/// <summary>
		/// адрес клиента 
		/// </summary>
		sockaddr_in clinetAddres;
		int client_addr_size = sizeof(clinetAddres);

		while ((clinetSocket = accept(_socket, (sockaddr *)&clinetAddres, &client_addr_size)))
		{
			sockets.push_back(clinetSocket);
			// увеличиваем счетчик подключившихся клиентов
			nclients++;
			// пытаемся получить имя хоста
			HOSTENT *hst = gethostbyaddr((char *)&clinetAddres.sin_addr.s_addr, 4, AF_INET);

			// вывод сведений о клиенте
			printf("+%s [%s] new connect!\n", (hst) ? hst->h_name : "", inet_ntoa(clinetAddres.sin_addr));
			PrintUsers();

			DWORD thID;
			CreateThread(NULL, NULL, WorkWithClient, &clinetSocket, NULL, &thID);
		}
	}
	system("pause");
	return 0;
}