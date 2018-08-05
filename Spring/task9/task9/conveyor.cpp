#include "stdafx.h"
#include "command.cpp"
#pragma once

class conveyor : public command
{
public:

	void execude() {
		if (value == "error")
			cout << "Command not recognized, try again\n";
	}

	conveyor(string s)
	{
		value = s;
	}
};
