#include "stdafx.h"
#include "PluginFinder.h"
#include "PluginLoader.h"
#include "../IPlugin/IPlugin.h"

int main()
{
	cout << "Input path to the library with plugins: ";
	TCHAR buffer[MAX_PATH];
	wcin >> buffer;
	SetCurrentDirectory(buffer);

	vector<HINSTANCE> pluginModelues;

	PluginFinder finder;
	finder.getPluginModules(pluginModelues);

	vector<IPlugin*> plugins;

	PluginLoader loader;
	loader.loadPlugins(pluginModelues, plugins);

	wcout << "Invoke plugin method for each plugin" << endl;
	for (auto plugin : plugins)
	{
		plugin->ShowPluginInfo();
	}

	finder.freePluginModules(pluginModelues);
	system("pause");
	return 0;
}

