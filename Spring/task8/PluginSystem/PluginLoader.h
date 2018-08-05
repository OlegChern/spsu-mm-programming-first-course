#include "stdafx.h"
#include "../IPlugin/IPlugin.h"

class PluginLoader
{
public:
	PluginLoader();
	~PluginLoader();

	void loadPlugins(const std::vector<HINSTANCE>&, std::vector<IPlugin*>&);

private:
	bool loadExport(HINSTANCE, const char*, void**);
};

