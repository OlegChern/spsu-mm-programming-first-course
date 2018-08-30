#include "stdafx.h"
#include "errors.h"

string errors::incorrectAdress = "> Connect error: Incorrect address";
string errors::usedAdress = "> Connect error: This adress is using now";

void errors::ShowError()
{
	printf("Error socket %d\n", WSAGetLastError());
	WSACleanup();
}

void errors::ShowError(SOCKET _socket)
{
	printf("Error bind %d\n", WSAGetLastError());
	// закрываем сокет!
	closesocket(_socket);
	WSACleanup();
}

bool errors::checkAdress(string inputAdress)
{
	bool syntax = true;
	bool symbols = true;
	for (int i = 0; i < inputAdress.size(); i++)
	{
		if (i == 3 || i == 5 || i == 7 || i == 9)
		{
			if (i == 9)
				syntax = inputAdress[i] == ':' ? true : false;
			else
				syntax = inputAdress[i] == '.' ? true : false;

		}
		else
			symbols = (inputAdress[i] >= '0') && (inputAdress[i] <= '9') ? true : false;
		if (!syntax || !symbols)
			return false;
	}
	return true;
}