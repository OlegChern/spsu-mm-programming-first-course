// TestPlugin.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"


#include "stdafx.h"
#include "TestPlugin.h"

TestPlugin::TestPlugin()
{
}

TestPlugin::~TestPlugin()
{
}

void TestPlugin::ShowPluginInfo() {
	wcout << "TestPlugin::ShowPluginInfo\n";
}