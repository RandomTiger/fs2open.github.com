#pragma once

typedef void(__stdcall *PluginCallback)(const char* msg);
extern PluginCallback PluginDebugLog;

void DebugLog(const char *msg);
void SetDebugLog(PluginCallback newFuncPtr);
