// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include "TestPlugin.h"
#include "OtherTestPlugin.h"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#define DLLEXPORT __declspec(dllexport)

extern "C" {
	struct IPlugin* getTestPlugin() {
		static TestPlugin instance;
		return &instance;
	}

	struct IPlugin* getOtherTestPlugin() {
		static OtherTestPlugin instance;
		return &instance;
	}

	DLLEXPORT PluginDetails exports = {
		{
			{ "TestPlugin", getTestPlugin },
	{ "OtherTestPlugin", getOtherTestPlugin }
		}
	};
}