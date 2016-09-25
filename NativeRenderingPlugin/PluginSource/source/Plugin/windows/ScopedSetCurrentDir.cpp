#include "ScopedSetCurrentDir.h"

// Project change: General->Character set->Not set
ScopedSetCurrentDir::ScopedSetCurrentDir(const char* path)
{
	GetCurrentDirectory(MAX_PATH, m_prevPath);
	SetCurrentDirectory(path);
	GetCurrentDirectory(MAX_PATH, m_currentPath);
}
ScopedSetCurrentDir::~ScopedSetCurrentDir()
{
	SetCurrentDirectory(m_prevPath);
}
