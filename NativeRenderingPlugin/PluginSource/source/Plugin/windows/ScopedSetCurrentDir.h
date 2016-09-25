#pragma once

#include <windows.h>

class ScopedSetCurrentDir
{
public:
	ScopedSetCurrentDir(const char* path);
	~ScopedSetCurrentDir();
	
private:
	char m_prevPath[MAX_PATH];
	char m_currentPath[MAX_PATH];
};
