#include "PluginLog.h"

PluginCallback PluginDebugLog = 0;

void SetDebugLog(PluginCallback newFuncPtr)
{
	PluginDebugLog = newFuncPtr;
}

void DebugLog(const char *msg)
{
	if (PluginDebugLog)
	{
		PluginDebugLog(msg);
	}
}

void DEBUG_LOG(const char *msg)
{
	DebugLog(msg);
}
