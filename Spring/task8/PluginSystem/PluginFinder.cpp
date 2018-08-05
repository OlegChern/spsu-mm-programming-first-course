#include "stdafx.h"
#include "PluginFinder.h"
#include "..\IPlugin\IPlugin.h"

using namespace std;

PluginFinder::PluginFinder()
{
}

PluginFinder::~PluginFinder()
{
}

void PluginFinder::getPluginModules(std::vector<HINSTANCE>& modules)
{
	modules.clear();

	WCHAR dllPath[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, dllPath);

	wcout << "Try to find dlls in the current folder: " << dllPath << endl;


	WIN32_FIND_DATA fileData;
	HANDLE fileHandle = FindFirstFile(L"*.dll", &fileData);

	if (fileHandle == INVALID_HANDLE_VALUE) {

		wcout << "No dlls in the current folder" << endl;
		system("pause");
		exit(0);
	}

	do {
		wcout << "\tFound: " << fileData.cFileName << "...";
		HINSTANCE pluginDll = LoadLibrary((wstring(fileData.cFileName)).c_str());
		if (0 == pluginDll) {
			wcout << "can't load dll\n";
			continue;
		}
		wcout << "loaded\n";
		modules.push_back(pluginDll);
	} while (FindNextFile(fileHandle, &fileData));
	FindClose(fileHandle);
}

void PluginFinder::freePluginModules(const vector<HINSTANCE>& modules)
{
	for (auto module : modules)
	{
		FreeLibrary(module);
	}
}