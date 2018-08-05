#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#pragma comment( lib, "ws2_32.lib" )
using namespace std;

#pragma region Globals
/// <summary>
/// Порт, который слушает сервер 
/// </summary>
int port = 600;
/// <summary>
/// IP адрес сервера
/// </summary>
string serverIp = "127.0.0.1";
/// <summary>
/// привествие
/// </summary>
string hello = "Hello, new member!";
/// <summary>
/// приветсвие сервера при включении
/// </summary>
string welcome = "TCP DEMO CLIENT";
/// <summary>
/// команда выхода из приложения
/// </summary>
string exitCommand = "exit";
SOCKET _socket;
string name = "";
bool exitFlag = false;
#pragma endregion

#pragma region Methods
/// <summary>
/// получение сообщения
/// </summary>
/// <param name="socket"></param>
/// <returns></returns>
string Recieve(SOCKET socket) {
	char buff[512] = "";
	recv(socket, buff, sizeof(buff), 0);
	return string(buff);
}
string Recieve(LPVOID client_socket) {
	return Recieve(((SOCKET *)client_socket)[0]);
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
/// Корректный выход
/// </summary>
void Exit(SOCKET socket) {
	printf("Exit...");
	closesocket(socket);
	WSACleanup();
}

DWORD WINAPI GetNewMessage(LPVOID clientSocket)
{
	string message = "";
	while ((message = Recieve(clientSocket)) != "") {
		printf("\n->:%s\n", message.c_str());
		printf("<-");
		if (exitFlag)
			break;
	}
	return 0;
}

DWORD WINAPI SendNewMessage(LPVOID serverSocket) {
	SOCKET _serverSocket = ((SOCKET *)serverSocket)[0];
	string message = "";
	while (message != exitCommand)
	{
		printf("<-");
		getline(cin, message);
		if (message == exitCommand) {
			exitFlag = true;
			Exit(_serverSocket);
			break;
		}
		else {
			message = name + ":" + message;
			Send(_serverSocket, message);
		}
	}
	return 0;
}
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
/// печатает сообщения  в консоли сервера
/// </summary>
/// <param name="message"></param>
void LogMessage(string message) {
	cout << message.c_str() << std::endl;
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

BOOL WINAPI ConsoleHandler(DWORD dwType)
{
	switch (dwType) {
	case CTRL_CLOSE_EVENT:
		Exit(_socket);
		return TRUE;
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:

		return TRUE;
	default:
		break;
	}
	return FALSE;
}
/// <summary>
/// устанавливает соединение
/// </summary>
/// <param name="socket"></param>
/// <param name="destAddr"></param>
/// <returns></returns>
bool Connect(SOCKET socket, sockaddr_in *destAddr) {
	// адрес сервера получен – пытаемся установить соединение 
	if (connect(socket, (sockaddr *)destAddr, sizeof(*destAddr)))
	{
		ShowError();
		return false;
	}
	return true;
}

void StartThreads() {
	DWORD thID;
	HANDLE recieveThread = CreateThread(NULL, NULL, GetNewMessage, &_socket, NULL, &thID);
	HANDLE sendThread = CreateThread(NULL, NULL, SendNewMessage, &_socket, NULL, &thID);
	WaitForSingleObject(recieveThread, INFINITE);
	WaitForSingleObject(sendThread, INFINITE);
}
#pragma endregion

int main(int argc, char* argv[])
{
	BOOL ret = SetConsoleCtrlHandler(ConsoleHandler, TRUE);
	setlocale(LC_ALL, "rus");
	char buff[1024];
	LogMessage(welcome);

	if (Init())
	{
		// создание сокета
		_socket = InitSocket();
		sockaddr_in dest_addr;
		dest_addr.sin_family = AF_INET;
		dest_addr.sin_port = htons(port);
		HOSTENT *hst;

		// преобразование IP адреса из символьного в сетевой формат
		if (inet_addr(serverIp.c_str()) != INADDR_NONE)
			dest_addr.sin_addr.s_addr = inet_addr(serverIp.c_str());
		else
			if (hst = gethostbyname(serverIp.c_str()))
				((unsigned long *)&dest_addr.sin_addr)[0] =
				((unsigned long **)hst->h_addr_list)[0][0];
			else
			{
				printf("Invalid address %s\n", serverIp.c_str());
				closesocket(_socket);
				WSACleanup();
				return -1;
			}
		if (connect(_socket, (sockaddr *)&dest_addr, sizeof(dest_addr)))
		{
			printf("Connect error %d\n", WSAGetLastError());
			return -1;
		}
		else
		{
			printf("Connect with %s success\nType '%s' for quit\n", serverIp.c_str(), exitCommand.c_str());
			printf("Enter your name:");
			getline(cin, name);
			StartThreads();
		}
	}
	std::system("pause");
	return 1;
}