#include "stdafx.h"
#pragma once

struct  IPlugin
{
	IPlugin() {}
	virtual ~IPlugin() {}
	virtual void ShowPluginInfo() = 0;
};

typedef IPlugin* (*GetCreateInstanceFunc)();

struct PluginDetail
{
	const char* pluginName;
	GetCreateInstanceFunc createInstanceFunc;
};

struct PluginDetails
{
	vector<PluginDetail> plugins;
};