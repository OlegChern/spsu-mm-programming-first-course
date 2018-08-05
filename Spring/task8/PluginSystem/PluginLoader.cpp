#include "stdafx.h"
#include "PluginLoader.h"

PluginLoader::PluginLoader()
{
}

PluginLoader::~PluginLoader()
{
}

void PluginLoader::loadPlugins(const vector<HINSTANCE>& modules, vector<IPlugin*>& plugins) {

	plugins.clear();

	wcout << "Try to load plugins from dlls" << endl;

	for (auto module : modules)
	{
		WCHAR   dllPath[MAX_PATH] = { 0 };
		GetModuleFileName((HINSTANCE)module, dllPath, MAX_PATH);

		wcout << "\tGet plugins from dll: " << dllPath << endl;

		PluginDetails* info;
		if (loadExport(module, "exports", reinterpret_cast<void**>(&info))) {
			wcout << "\t\tFound " << info->plugins.size() << " plugin(s):" << endl;
			for (auto &pluginDetail : info->plugins)
			{
				cout << "\t\t\tPlugin Name: " << pluginDetail.pluginName << endl;
				IPlugin* plugin = reinterpret_cast<IPlugin*>(pluginDetail.createInstanceFunc());
				plugins.push_back(plugin);
			}
		}
		else
		{
			wcout << "\t\tNo plugins in dll" << endl;
		}
	}
}

bool PluginLoader::loadExport(HINSTANCE plugin, const char* name, void** ptr)
{
	*ptr = (void*)GetProcAddress(plugin, name);
	return *ptr != NULL;
}