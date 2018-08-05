#include "stdafx.h"
#include "command.cpp"
#include "localValue.cpp"
#pragma once

class dollar : public command
{
public:
	localValue *values;
	bool flag = true;

	void execude() {
		for (int i = 0; i < value.size(); i++)
			if (value[i] == '=')
			{
				flag = values->insertValue(value);
				if (!flag)
					cout << "Command not recognized, try again\n";
				return;
			}
		string res;
		res = values->getValue(value);
		if (res == "")
			cout << "This variable is not defined\n";
		else
			cout << res << "\n";
	}
	
	dollar(localValue *t, string s)
	{
		values = t;
		value = s;
	}
};
