#include "stdafx.h"
#include "command.cpp"

class exitCmd : public command
{
public:

	void execude() {
		cout << "Bash stopped" << "\n";
		system("pause");
		exit(0);
	}
};