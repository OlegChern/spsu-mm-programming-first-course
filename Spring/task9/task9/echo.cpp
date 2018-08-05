#include "stdafx.h"
#include "command.cpp"
#include "localValue.cpp"
#pragma once

class echo : public command
{
public:
	localValue * values;

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

	echo(localValue *t, string s)
	{
		values = t;
		value = s;
	}
};