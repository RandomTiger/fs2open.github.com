#include "PluginData.h"

static std::string s_UnityStreamingAssetsPath;

std::string GetData_AssetPath()
{
	return s_UnityStreamingAssetsPath;
}

void SetData_AssetPath(std::string path)
{
	s_UnityStreamingAssetsPath = path;
}