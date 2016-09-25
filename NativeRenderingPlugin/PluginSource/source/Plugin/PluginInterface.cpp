#include <string>
#include "..\RenderAPI.h"
#include "PluginLog.h"
#include "PluginData.h"

extern "C" UNITY_INTERFACE_EXPORT void Plugin_SetupDebug(PluginCallback PluginDebugLogFunc)
{
	PluginDebugLog = PluginDebugLogFunc;
	if (PluginDebugLog)
	{
		PluginDebugLog("Debug from plugin setup");
	}
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API Plugin_Init(const char* path)
{
	SetData_AssetPath(path);
	PluginDebugLog(path);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API Plugin_Deinit()
{
	PluginDebugLog("Plugin_Deinit");
}

