#include "stdafx.h"
#pragma once

class LocalValue
{
public:
	map<string, string> localValues;
	LocalValue() {}

	bool insertValue(string s)
	{
		string variable = "";
		string value = "";
		int it = 1;
		for (it = 1; it < s.size() && s[it] != '='; it++)
			variable += s[it];
		if (it != s.size())
		{
			it++;
			for (int i = it; i < s.size(); i++)
				value += s[i];
		}
		if (variable == "" || value == "")
			return false;
		else
			localValues[variable] = value;
		return true;
	}

	string getValue(string s)
	{
		string variable = "";
		for (int i = 1; i < s.size(); i++)
			variable += s[i];
		if (localValues.find(variable) != localValues.end())
			return localValues[variable];
		return "";
	}
};
