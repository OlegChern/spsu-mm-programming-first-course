#pragma once
class connection
{
public:
	static string ip;
	static int port;
	static int lastPort;

	static string recieveClient(SOCKET socket);

	static string recieveClient(LPVOID client_socket);

	/// <summary>
	/// Создает сокет
	/// </summary>
	/// <returns></returns>
	static SOCKET initSocket();

	/// <summary>
	/// отправка сообщения
	/// </summary>
	/// <param name="socket"></param>
	/// <param name="message"></param>
	static void sendMessage(SOCKET socket, string message);

	static SOCKET tryConnect(string ipClient, int portClient);
};

