#include "errors.h"

#pragma once
class user
{
private:
	static string exitCommand;
	map <int, SOCKET>::iterator it;

	static string recieveClient(SOCKET socket);

	static string recieveClient(LPVOID client_socket);

	static int systemCommand(string s);

	static string convert(int a);

	/// <summary>
	/// Отделить ip и port
	/// </summary>
	/// <returns></returns>
	static pair<string, string> parser(string s);

	/// <summary>
	/// печатает сообщения  в консоли
	/// </summary>
	/// <param name="message"></param>
	static void logMessage(string message);

	/// <summary>
	/// Корректный выход
	/// </summary>
	static void exitCmd(SOCKET socket);

	static SOCKET tryConnect(string ipClient, int portClient);

public:
	static string ip;
	static int port;
	static bool exitFlag;
	static string name;
	static map <int, SOCKET> clients;
	static int lastPort;

	/// <summary>
	/// отправка сообщения
	/// </summary>
	/// <param name="socket"></param>
	/// <param name="message"></param>
	static void sendMessage(SOCKET socket, string message);

	/// <summary>
	/// Создает сокет
	/// </summary>
	/// <returns></returns>
	static SOCKET initSocket();

	static DWORD WINAPI getMessage(LPVOID clientSocket);

	/// <summary>
	/// обсуживает очередного подключившегося клиента независимо от остальных
	/// </summary>
	/// <param name="client_socket"></param>
	/// <returns></returns>
	static DWORD WINAPI workWithClient(LPVOID client_socket);
};

