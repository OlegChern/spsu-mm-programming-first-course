#include "stdafx.h"
#pragma once
#include "../IPlugin/IPlugin.h"

class TestPlugin : public IPlugin {

public:
	TestPlugin();
	virtual ~TestPlugin();

	virtual void ShowPluginInfo();
};