#include "stdafx.h"
#pragma once
#include "../IPlugin/IPlugin.h"

class OtherTestPlugin : public IPlugin
{
public:
	OtherTestPlugin();
	virtual ~OtherTestPlugin();

	virtual void ShowPluginInfo();
};

