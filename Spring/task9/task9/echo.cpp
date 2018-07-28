#include "stdafx.h"
#include "command.cpp"
#include "LocalValue.cpp"
#pragma once

class echo : public command
{
public:
	LocalValue * values;
	void execude() {
		string dollarCmd = values->getValue(value);
		if (dollarCmd != "")
			value = dollarCmd;
		memory = value;
		if (value == "")
			cout << "No argument\n";
		else
			cout  << value << "\n";
	}

	echo(LocalValue *t, string s)
	{
		values = t;
		value = s;
	}
};