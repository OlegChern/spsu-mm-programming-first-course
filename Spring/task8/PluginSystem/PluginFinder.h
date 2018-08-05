#include "stdafx.h"
#pragma once

class PluginFinder
{
public:
	PluginFinder();
	~PluginFinder();

	void getPluginModules(std::vector<HINSTANCE>&);
	void freePluginModules(const std::vector<HINSTANCE>&);
};

