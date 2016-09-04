#include "RenderingPlugin.h"

void DEBUG_LOG(const char *msg)
{
	if (PluginDebugLog)
	{
		PluginDebugLog(msg);
	}
}