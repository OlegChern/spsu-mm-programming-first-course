#include "stdafx.h"
#include "command.cpp"
#include "localValue.cpp"
#pragma once

class systemCmd : public command
{
public:
	localValue * values;

	void execude() {
		char* p = new char[value.size() + 1];
		strcpy(p, value.c_str());
		system(p);
	}

	systemCmd(string s)
	{
		value = s;
	}
};