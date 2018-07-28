#include "stdafx.h"
#include "command.cpp"
#include "LocalValue.cpp"
#pragma once

class SystemCmd : public command
{
public:
	LocalValue * values;
	void execude() {
		char* p = new char[value.size() + 1];
		strcpy(p, value.c_str());
		system(p);
	}

	SystemCmd(string s)
	{
		value = s;
	}
};